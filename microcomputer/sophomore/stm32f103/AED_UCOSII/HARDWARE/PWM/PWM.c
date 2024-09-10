#include "stm32f10x.h"                  // Device header
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
	
	/* PA1:�����������	*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStruct );
	
	/* ��ʼ��TIM2 �������� */
	TIM_DeInit( TIM2 );
	TIM_TimeBaseInitStruct.TIM_Period = arr;//arr���Զ���װֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//psc��ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct );	
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽ1
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//������ԡ����߼���
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	TIM_OCInitStruct.TIM_Pulse = 199;//�Ƚ�ֵCCR�����Բ������ã���Ϊ���ڿ϶�Ҫ��
	
	TIM_OC2Init( TIM2, &TIM_OCInitStruct );//PA1
	
	/* ʹ��Ԥװ�ؼĴ��� */
	TIM_OC2PreloadConfig( TIM2, TIM_OCPreload_Enable );
	
	/* ʹ���Զ�װ�ص�Ԥװ�ؼĴ��� */
	TIM_ARRPreloadConfig( TIM2, ENABLE );
	/* ʹ��TIM2,TIM3 */
	TIM_Cmd( TIM2, ENABLE );

}

