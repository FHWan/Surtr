#include "XYPositionCombine.h"

//Ԥ�����
//static float x_vision=8.0f;
//static float x_acc_bias=0.8f;
//static float y_vision=8.0f;
//static float y_acc_bias=0.8f;

//float x_est[2] = {0.0f,0.0f};//x���λ�ú��ٶ�
//float y_est[2] = {0.0f,0.0f};//y���λ�ú��ٶ�
//float Accel_ned[3] = {0.0f,0.0f,0.0f};//��������ϵ�µļ��ٶ�����
//float Accel_bias[3] = {0.0f,0.0f,0.0f};//��������ϵ�µļ��ٶ�ƫ����

//float corr_x_vision = 0.0f;
//float corr_y_vision = 0.0f;

///*****************************************
//*accel:��������ϵX,Y,Z���ٶ�
//X_postion:X������
//Y_postion:Y������
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
//	//Xλ��У׼
//  corr_x_vision = 0 - X_postion - x_est[0];
//	corr_y_vision = 0 - Y_postion - y_est[0];
//	
//}



