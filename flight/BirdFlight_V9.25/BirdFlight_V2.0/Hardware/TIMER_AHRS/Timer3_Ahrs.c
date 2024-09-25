#include "Timer3_Ahrs.h"
#include "Task.h"

void Timer_Ahrsinit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = 399; 							//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 419;  				//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);			//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 								//����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); 																	//ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 					//��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 				//�����ȼ�0
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


