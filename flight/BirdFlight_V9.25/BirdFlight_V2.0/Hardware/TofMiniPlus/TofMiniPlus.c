#include "TofMiniPlus.h"
FPS_TimeOfFly FPSTimeOfFly; 
float TOFHeightLpf,TOFHeightLpfLast;
float TOFHeightVel;
/**********************************************************************************************************
*函 数 名: TOF_DataDeal
*功能说明: TOF传感器数据处理
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void TOF_DataDeal(_Data_Rx rx){
	if(rx.buf[0]==0x59 && rx.buf[1]==0x59){
		uint16_t Distance = (((uint16_t)rx.buf[3]) << 8) + rx.buf[2];
		uint16_t Strength = (((uint16_t)rx.buf[5]) << 8) + rx.buf[4];
		//根据数据手册强度在这个范围内有效
		if(Strength>150 && Strength<60000){
			Sensor_Info.TofHeight = ((float)Distance) * 0.01f;   // 米制单位
		}
	}
	else if(rx.len==8 && rx.buf[0]==0x5A && rx.buf[1]==0x5A)
	{
		Sensor_Info.TofHeight = (float)(rx.buf[4]<<8 | rx.buf[5])/100  * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);   
	}	
}
