/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Timer5_Timing.c
 * ����   :��ȡϵͳʱ�亯��
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Timer5_Timing.h"

void Timer5_Timinginit(void)
{
  RCC->APB1ENR |= 0x0008;	
	TIM5->CR1 = 0x0080;
	TIM5->CR2 = 0x0000;
	TIM5->CNT = 0x0000;
	TIM5->ARR = 0xFFFFFFFF;
	TIM5->PSC = 84 - 1;	
	TIM5->EGR = 0x0001;
	TIM5->CR1 |= 0x0001;       
}

uint32_t micros(void)
{
 	uint32_t temp=0 ;
 	temp = TIM5->CNT;
 	return temp;
}


