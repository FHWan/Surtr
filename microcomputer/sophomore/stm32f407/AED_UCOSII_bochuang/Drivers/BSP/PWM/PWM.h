#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32429������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:201/1/6
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
extern TIM_HandleTypeDef TIM4_Handler;      //��ʱ��4PWM��� 
extern TIM_OC_InitTypeDef TIM4_CH4Handler;  //��ʱ��4ͨ��4���

void TIM4_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM4Compare4(u32 compare);
#endif


