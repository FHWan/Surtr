#ifndef __ADC_H
#define __ADC_H	
#include "./SYSTEM/sys/sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

void ADC_Function_Init(void);               //ADC通道初始化
u16 Get_ADC_Val1(u8 ch);                 //获得某个通道值
u16 Get_ConversionVal1(s16 val);//得到某个通道给定次数采样的平均值
#endif 




