#include "XYPositionCombine.h"

//预测参数
//static float x_vision=8.0f;
//static float x_acc_bias=0.8f;
//static float y_vision=8.0f;
//static float y_acc_bias=0.8f;

//float x_est[2] = {0.0f,0.0f};//x轴的位置和速度
//float y_est[2] = {0.0f,0.0f};//y轴的位置和速度
//float Accel_ned[3] = {0.0f,0.0f,0.0f};//地理坐标系下的加速度数据
//float Accel_bias[3] = {0.0f,0.0f,0.0f};//机体坐标系下的加速度偏移量

//float corr_x_vision = 0.0f;
//float corr_y_vision = 0.0f;

///*****************************************
//*accel:机体坐标系X,Y,Z加速度
//X_postion:X轴数据
//Y_postion:Y轴数据
//******************************************/

//void XY_Position(float X_postion,float Y_postion,float *accel)
//{
//	float Accel_bias_corr[3] = { 0.0f, 0.0f, 0.0f };
//	float Accel_now[3] = {0.0f,0.0f,0.0f};
//	unsigned int i,j;
//	static unsigned int tPre=0;
//	unsigned int t;
//	static float xyposition_dt;
//	t=micros();
//  xyposition_dt = (tPre>0)?((t-tPre)/1000000.0f):1;
//  tPre=t;
//	//X位置校准
//  corr_x_vision = 0 - X_postion - x_est[0];
//	corr_y_vision = 0 - Y_postion - y_est[0];
//	
//}



