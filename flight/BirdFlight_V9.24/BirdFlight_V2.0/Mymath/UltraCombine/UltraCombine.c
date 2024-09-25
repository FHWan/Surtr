#include "UltraCombine.h"
//预测参数
static float w_z_ultra=8.0f;
static float w_acc_bias=0.8f;

float z_est[2] = {0.0f,0.0f};//Z轴的高度和速度
float accel_ned[3] = {0.0f,0.0f,0.0f};//地理坐标系下的加速度数据
float accel_bias[3] = {0.0f,0.0f,0.0f};//机体坐标系下的加速度偏移量

float corr_Ultra = 0.0f;
/*****************************************
*accel:机体坐标系X,Y,Z加速度
Ultra:高度数据
******************************************/
void Altitude_Ultrasonic(float Ultra,float *accel)
{
	CPU_SR_ALLOC();
	float accel_bias_corr[3] = { 0.0f, 0.0f, 0.0f };
	float accel_now[3] = {0.0f,0.0f,0.0f};
  unsigned int i,j;
	static unsigned int tPre=0;
	unsigned int t;
	static float Ultra_dt;
	t=micros();
  Ultra_dt = (tPre>0)?((t-tPre)/1000000.0f):1;
  tPre=t;
	OS_CRITICAL_ENTER();										
	accel_now[0] = accel[0];
	accel_now[1] = accel[1];
	accel_now[2] = accel[2];
	OS_CRITICAL_EXIT();
	//超声波数据 计算超声波的校准
  corr_Ultra = 0 - Ultra - z_est[0];
  //加速度除去偏移量
  accel_now[0] -= accel_bias[0];
  accel_now[1] -= accel_bias[1];
  accel_now[2] -= accel_bias[2];
  //转化为NED坐标系
  for(i=0; i<3; i++)
  {
		accel_ned[i]=0.0f;
		for(j=0; j<3; j++)
		{
			accel_ned[i] += RDrone_R[i][j]* accel_now[j];
		}
  }
  accel_ned[2] += CONSTANTS_ONE_G;
  //正确的加速度偏移向量
  accel_bias_corr[2] -= corr_Ultra * w_z_ultra * w_z_ultra;
  //转化为机体坐标系
  for (i = 0; i < 3; i++)
  {
		float c = 0.0f;
		for (j = 0; j < 3; j++)
		{
			c += RDrone_R[j][i] * accel_bias_corr[j];
		}
		accel_bias[i] += c * w_acc_bias * Ultra_dt;
  }
  inertial_filter_predict(Ultra_dt, z_est, accel_ned[2]);
  inertial_filter_correct(corr_Ultra, Ultra_dt, z_est, 0, w_z_ultra);
	
	RT_Info.US100_Alt = -z_est[0];
	RT_Info.US100_Alt_V = -z_est[1];
}

