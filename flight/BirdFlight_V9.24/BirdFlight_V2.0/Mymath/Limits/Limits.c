/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * ���� 	:Xiluna Tech
 * �ļ��� :Limits.c
 * ����   :�����޷�����
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
******************************************************************************/
#include "Limits.h"
/*�޷�����*/
float Limits_data(float LimitsData,float LimitsUp,float LimitsDown)
{
	if(LimitsData > LimitsUp)
	{
		LimitsData = LimitsUp;
	}
	if(LimitsData < LimitsDown)
	{
		LimitsData = LimitsDown;
	}
	return LimitsData;
}
/*���㺯��*/
float Limits_zero(float LimitsData,float LimitsUp,float LimitsDown)
{
	if(LimitsData	< LimitsUp && LimitsData > LimitsDown)
	{
		LimitsData = 0;
	}
	else
	{
		LimitsData = LimitsData;
	}
	return LimitsData;
}


