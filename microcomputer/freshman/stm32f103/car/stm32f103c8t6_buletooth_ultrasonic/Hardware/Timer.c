#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		//����TIM3ʱ��

	TIM_InternalClockConfig(TIM3);								//����TIM3ʹ���ڲ�ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;			//����ṹ�壬���ö�ʱ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//����1��Ƶ������Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ü���ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			//����������ֵ���ﵽ���ֵ���������¼�����Ϊ��0��ʼ���������Լ���10����10-1,ÿ10΢�봥��һ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//����ʱ��Ԥ��Ƶ��72-1����ÿ ʱ��Ƶ��(72Mhz)/72=1000000 ��ʱ�����ڼ�������1,ÿ1΢��+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//�ظ����������߼���ʱ�����У���������0��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);			//��ʼ��TIM3��ʱ��
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);			//��������жϱ�־λ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//���������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//�����ж����ȼ�����
	
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�壬�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				//ָ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�ж�ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//������Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);								// https://blog.zeruns.tech
	
	TIM_Cmd(TIM3, ENABLE);							//������ʱ��
}

/*
void TIM3_IRQHandler(void)			//�����жϺ���
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//��ȡTIM3��ʱ���ĸ����жϱ�־λ
	{
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//��������жϱ�־λ
	}
}*/
