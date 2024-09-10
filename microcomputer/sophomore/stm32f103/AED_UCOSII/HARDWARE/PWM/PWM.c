#include "stm32f10x.h"                  // Device header
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
	
	/* PA1:复用推挽输出	*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStruct );
	
	/* 初始化TIM2 基本配置 */
	TIM_DeInit( TIM2 );
	TIM_TimeBaseInitStruct.TIM_Period = arr;//arr：自动重装值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//psc：时钟预分频数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct );	
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性——高极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OCInitStruct.TIM_Pulse = 199;//比较值CCR，可以不用配置，因为后期肯定要改
	
	TIM_OC2Init( TIM2, &TIM_OCInitStruct );//PA1
	
	/* 使能预装载寄存器 */
	TIM_OC2PreloadConfig( TIM2, TIM_OCPreload_Enable );
	
	/* 使能自动装载的预装载寄存器 */
	TIM_ARRPreloadConfig( TIM2, ENABLE );
	/* 使能TIM2,TIM3 */
	TIM_Cmd( TIM2, ENABLE );

}

