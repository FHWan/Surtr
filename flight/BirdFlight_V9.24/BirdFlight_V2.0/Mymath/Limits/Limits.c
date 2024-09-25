/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :Limits.c
 * 描述   :数据限幅函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "Limits.h"
/*限幅函数*/
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
/*赋零函数*/
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


