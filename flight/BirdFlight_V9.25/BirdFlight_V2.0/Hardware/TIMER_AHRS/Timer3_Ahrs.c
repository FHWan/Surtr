#include "Timer3_Ahrs.h"
#include "Task.h"

void Timer_Ahrsinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 399; 							//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 419;  				//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);			//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 								//允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); 																	//使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 					//定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 				//子优先级0
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


