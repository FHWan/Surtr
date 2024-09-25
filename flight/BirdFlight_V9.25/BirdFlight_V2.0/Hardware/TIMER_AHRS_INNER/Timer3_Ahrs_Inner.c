/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Timer3_Ahrs_Inner.c
 * ����   :���ڽ�����ڻ����ƵĶ�ʱ��
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Timer3_Ahrs_Inner.h"
void Timer3_Ahrsinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  					//ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = 1999; 									//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 83;  								//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);						//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 											//����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); 																				//ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 								//��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 			//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 							//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

void Timer4_ImuInnerinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  					//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = 3999; 									//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 83;  								//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);						//��ʼ��TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 											//����ʱ��4�����ж�
	TIM_Cmd(TIM4,ENABLE); 																				//ʹ�ܶ�ʱ��4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 								//��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 			//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; 							//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}


//��ʱ�����ж�
void TIM3_IRQHandler(void)
{
	OS_ERR err;
	OSIntEnter();	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //���ж�
		OSSemPost(&IMU_proc,OS_OPT_POST_1,&err);
	}
	OSIntExit();
}
//��ʱ�����ж�
void TIM4_IRQHandler(void)
{
	OS_ERR err;
	OSIntEnter();
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //���ж�
		OSSemPost(&Attitude_proc,OS_OPT_POST_1,&err);
	}
	OSIntExit();
}



