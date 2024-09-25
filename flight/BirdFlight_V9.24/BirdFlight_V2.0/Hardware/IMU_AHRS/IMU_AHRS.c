/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :IMU_AHRS.c
 * 描述   :IMU原始数据读取及数据融合
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "IMU_AHRS.h"
#include "MPU6500.h"
#include "LSM303D.h"
#include "explore_systick.h"
#include "arm_math.h"
#include "digital_filter.h"
#include <math.h>
#include "Task.h"

Butter_Parameter Accel_Parameter;
Butter_Parameter Gyro_Parameter;
Butter_Parameter Flow_Parameter;
Butter_BufferData  accel_filter_buf[3];
Butter_BufferData  gyro_filter_buf[3];
Butter_BufferData  flow_filter_buf[3];

// asin函数
float safe_asin(float v)
{
	if (isnan(v)) {
		return 0.0f;
	}
	if (v >= 1.0f) {
		return PI/2;
	}
	if (v <= -1.0f) {
		return -PI/2;
	}
	return asin(v);
}

void IMU_HardwareInit()
{
	LSM303_Initial();           	//lsm303寄存器配置
	delay_ms(100);
	MPU6500_initialize();					//mpu6500寄存器配置
	delay_ms(100);
	MPU6500_Init_Offset();    		//6500初始化校准（平均滤波）
	delay_ms(100);	
	Set_Cutoff_Frequency(500.0f, 20.0f,&Accel_Parameter);//加计巴特沃斯参数初始化
	delay_ms(100);
	Set_Cutoff_Frequency(500.0f, 41.0f,&Gyro_Parameter);//陀螺仪巴特沃斯参数初始化
	delay_ms(100);
}

void IMU_getValues(float * values) 
{  
	int16_t accgyroval[9];
	static float AccData[3],GyroData[3];
	//读取磁力计的原始值
	LSM303_readMag(&accgyroval[6]);	
	//读取加速度计和陀螺仪的原始值
	MPU6500_readGyro_Acc(&accgyroval[3],&accgyroval[0]);

	 //陀螺仪单位转化
    GyroData[0] = ((float) accgyroval[3]) / 16.384f  ;//(量程/分辨率): 4000/65536 = 1/16.384 °/s
    GyroData[1] = ((float) accgyroval[4]) / 16.384f  ;//(量程/分辨率): 4000/65536 = 1/16.384 °/s
    GyroData[2] = ((float) accgyroval[5]) / 16.384f  ;//(量程/分辨率): 4000/65536 = 1/16.384 °/s
	
		//原始角速度数据
		RT_Info.GyroX = GyroData[1] ;
		RT_Info.GyroY = GyroData[0] ;
		RT_Info.GyroZ = GyroData[2] ;

    values[3]=  LPButterworth(GyroData[0],&gyro_filter_buf[0],&Gyro_Parameter);
    values[4]=  LPButterworth(GyroData[1],&gyro_filter_buf[1],&Gyro_Parameter);
    values[5]=  LPButterworth(GyroData[2],&gyro_filter_buf[2],&Gyro_Parameter);
//  values[3] = ((float) accgyroval[3]) / 16.384f;//(量程/分辨率): 4000/65536 = 1/16.384 °/s
//	values[4] = ((float) accgyroval[4]) / 16.384f;//(量程/分辨率): 4000/65536 = 1/16.384 °/s
//	values[5] = ((float) accgyroval[5]) / 16.384f;//(量程/分辨率): 4000/65536 = 1/16.384 °/s

	//加速度数据单位转换 (量程/分辨率): 4/65536 = 1/16384 g  转换为m/s^2
	AccData[0] = (((float) accgyroval[0]) / 4096.0f * GRAVITY_MSS ) * OffsetData.AccXScale - OffsetData.AccX; 
	AccData[1] = (((float) accgyroval[1]) / 4096.0f * GRAVITY_MSS ) * OffsetData.AccYScale - OffsetData.AccY;	
	AccData[2] = (((float) accgyroval[2]) / 4096.0f * GRAVITY_MSS ) * OffsetData.AccZScale - OffsetData.AccZ;
	
	
	values[0]=LPButterworth(AccData[0],&accel_filter_buf[0],&Accel_Parameter);
  values[1]=LPButterworth(AccData[1],&accel_filter_buf[1],&Accel_Parameter);
  values[2]=LPButterworth(AccData[2],&accel_filter_buf[2],&Accel_Parameter);
	
//  //加速度数据单位转换 (量程/分辨率): 4/65536 = 1/16384 g  转换为m/s^2
//	values[0] = (((float) accgyroval[0]) / 16384.0f * GRAVITY_MSS ) * OffsetData.AccXScale - OffsetData.AccX; 
//	values[1] = (((float) accgyroval[1]) / 16384.0f * GRAVITY_MSS ) * OffsetData.AccYScale - OffsetData.AccY;	
//	values[2] = (((float) accgyroval[2]) / 16384.0f * GRAVITY_MSS ) * OffsetData.AccZScale - OffsetData.AccZ;
	
	values[6] = (float)accgyroval[6]/32768 *4;
	values[7] = (float)accgyroval[7]/32768 *4;
	values[8] = (float)accgyroval[8]/32768 *4;
}
volatile float RDrone_R[3][3];
float Accel[3];
void IMU_getInfo(void){
	static float q[4];
	static float getValue[9];
	static float q0q0,q0q1,q0q2,q0q3,q1q1,q1q2,q1q3,q2q2,q2q3,q3q3;
	IMU_getValues(getValue);										//获取原始数据
	MahonyAHRSupdate(getValue[3] * PI/180, getValue[4] * PI/180, getValue[5] * PI/180,
																		getValue[0], getValue[1], getValue[2],0,0,0);	
//	MahonyAHRSupdate(getValue[3] * PI/180, getValue[4] * PI/180, getValue[5] * PI/180,
//																		getValue[0], getValue[1], getValue[2],getValue[6],getValue[7],getValue[8]);	
	
//	EKF_AHRSupdate(getValue[3] * PI/180, getValue[4] * PI/180, getValue[5] * PI/180,
//			getValue[0], getValue[1], getValue[2],0, 0, 0,q);
	
//	MadgwickAHRSupdateIMU(getValue[3] * PI/180, getValue[4] * PI/180, getValue[5] * PI/180,
//																		getValue[0], getValue[1], getValue[2],q);
	
	
	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
	
	
	//使用矩阵的时候可以快速使用
	q0q0 = q[0]*q[0];
	q0q1 = q[0]*q[1];
	q0q2 = q[0]*q[2];
	q0q3 = q[0]*q[3];
	q1q1 = q[1]*q[1];
	q1q2 = q[1]*q[2];
	q1q3 = q[1]*q[3];
	q2q2 = q[2]*q[2];
	q2q3 = q[2]*q[3];
	q3q3 = q[3]*q[3]; 
	
	RDrone_R[0][0] = q0q0 + q1q1 - q2q2 - q3q3;
	RDrone_R[0][1] = 2.f * (q1q2 + q0q3);
	RDrone_R[0][2] = 2.f * (q1q3 - q0q2);
	RDrone_R[1][0] = 2.f * (q1q2 - q0q3);		
	RDrone_R[1][1] = q0q0 - q1q1 + q2q2 - q3q3;
	RDrone_R[1][2] = 2.f * (q2q3 + q0q1);
	RDrone_R[2][0] = 2.f * (q1q3 + q0q2);
	RDrone_R[2][1] = 2.f * (q2q3 - q0q1);
	RDrone_R[2][2] = q0q0 - q1q1 - q2q2 + q3q3;
	
	//地理坐标系下的加速度
	RT_Info.accXaxis = ((q0q0 + q1q1 - q2q2 - q3q3)*getValue[0] + (2.f * (q1q2 - q0q3))*getValue[1]  +   (2.f * (q1q3 + q0q2))*getValue[2])  ;
	RT_Info.accYaxis = ((2.f * (q1q2 + q0q3))*getValue[0]  + (q0q0 - q1q1 + q2q2 - q3q3)*getValue[1] +   (2.f * (q2q3 - q0q1))*getValue[2]);
	RT_Info.accZaxis =  ((2.f * (q1q3 - q0q2))*getValue[0]   + (2.f * (q2q3 + q0q1))*getValue[1]    +   (q0q0 - q1q1 - q2q2 + q3q3)*getValue[2] - GRAVITY_MSS);//减去重力加速度

	//去除重力加速度1g后的载体加速度数据
	RT_Info.AccX = (q0q0 + q1q1 - q2q2 - q3q3)* RT_Info.accXaxis + (2.f * (q1q2 + q0q3))* RT_Info.accYaxis  +   (2.f * (q1q3 - q0q2))*RT_Info.accZaxis  ;
	RT_Info.AccY = 2.f * (q1q2 - q0q3)* RT_Info.accXaxis + (q0q0 - q1q1 + q2q2 - q3q3)* RT_Info.accYaxis  +   (2.f * (q2q3 + q0q1))*RT_Info.accZaxis ;
	RT_Info.AccZ = 2.f * (q1q3 + q0q2)* RT_Info.accXaxis + (2.f * (q2q3 - q0q1))* RT_Info.accYaxis  +   (q0q0 - q1q1 - q2q2 + q3q3)*RT_Info.accZaxis  ;

	
	//角速度数据
	RT_Info.rateRoll=getValue[3] /57.3f;
	RT_Info.ratePitch=getValue[4] /57.3f;
	RT_Info.rateYaw=getValue[5] /57.3f;
	

  //原始磁力计数据
	RT_Info.MagX = getValue[6]  ;
	RT_Info.MagY = getValue[7]  ;
	RT_Info.MagZ = getValue[8]  ;
	
	//角度数据
	RT_Info.Roll = (atan2(2.0f*(q0q1 + q2q3),
										 1 - 2.0f*(q1q1 + q2q2)))* 180/PI;
	RT_Info.Pitch = -safe_asin(2.0f*(q0q2 - q1q3))* 180/PI;

	RT_Info.Yaw = atan2(2.0f*q1q2 + 2.0f*q0q3, -2.0f*q2q2 - 2.0f*q3q3 + 1) * 180/PI; // yaw
}




