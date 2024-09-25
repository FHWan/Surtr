#include "UltraCombine.h"
//Ԥ�����
static float w_z_ultra=8.0f;
static float w_acc_bias=0.8f;

float z_est[2] = {0.0f,0.0f};//Z��ĸ߶Ⱥ��ٶ�
float accel_ned[3] = {0.0f,0.0f,0.0f};//��������ϵ�µļ��ٶ�����
float accel_bias[3] = {0.0f,0.0f,0.0f};//��������ϵ�µļ��ٶ�ƫ����

float corr_Ultra = 0.0f;
/*****************************************
*accel:��������ϵX,Y,Z���ٶ�
Ultra:�߶�����
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
	//���������� ���㳬������У׼
  corr_Ultra = 0 - Ultra - z_est[0];
  //���ٶȳ�ȥƫ����
  accel_now[0] -= accel_bias[0];
  accel_now[1] -= accel_bias[1];
  accel_now[2] -= accel_bias[2];
  //ת��ΪNED����ϵ
  for(i=0; i<3; i++)
  {
		accel_ned[i]=0.0f;
		for(j=0; j<3; j++)
		{
			accel_ned[i] += RDrone_R[i][j]* accel_now[j];
		}
  }
  accel_ned[2] += CONSTANTS_ONE_G;
  //��ȷ�ļ��ٶ�ƫ������
  accel_bias_corr[2] -= corr_Ultra * w_z_ultra * w_z_ultra;
  //ת��Ϊ��������ϵ
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

