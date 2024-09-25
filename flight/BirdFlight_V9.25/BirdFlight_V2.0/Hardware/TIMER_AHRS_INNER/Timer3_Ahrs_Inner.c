/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Timer3_Ahrs_Inner.c
 * 描述   :用于解算和内环控制的定时器
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Timer3_Ahrs_Inner.h"
void Timer3_Ahrsinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  					//使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 1999; 									//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 83;  								//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);						//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 											//允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); 																				//使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 								//定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 			//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 							//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

void Timer4_ImuInnerinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  					//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = 3999; 									//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 83;  								//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);						//初始化TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 											//允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); 																				//使能定时器4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 								//定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 			//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; 							//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}


//定时器三中断
void TIM3_IRQHandler(void)
{
	OS_ERR err;
	OSIntEnter();	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清中断
		OSSemPost(&IMU_proc,OS_OPT_POST_1,&err);
	}
	OSIntExit();
}
//定时器四中断
void TIM4_IRQHandler(void)
{
	OS_ERR err;
	OSIntEnter();
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清中断
		OSSemPost(&Attitude_proc,OS_OPT_POST_1,&err);
	}
	OSIntExit();
}



