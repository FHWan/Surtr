#ifndef __ADC_H
#define __ADC_H	
#include "debug.h"
////////////////////////////////////////////////////////////////////////////////// 	 

void ADC_Function_Init(void);               //ADCͨ����ʼ��
u16 Get_ADC_Val1(u8 ch);                 //���ĳ��ͨ��ֵ
u16 Get_ADC_Val2(u8 ch);                 //���ĳ��ͨ��ֵ
u16 Get_ConversionVal1(s16 val);//�õ�ĳ��ͨ����������������ƽ��ֵ
u16 Get_ConversionVal2(s16 val);//�õ�ĳ��ͨ����������������ƽ��ֵ
#endif 




