#include "PWM.h"

//TIM_HandleTypeDef TIM4_Handler;         //��ʱ��4PWM��� 
TIM_OC_InitTypeDef TIM4_CH4Handler;	    //��ʱ��4ͨ��1���

//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u16 arr,u16 psc)
{ 
    TIM4_Handler.Instance=TIM4;            //��ʱ��4
    TIM4_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM4_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM4_Handler);       //��ʼ��PWM
    
    TIM4_CH4Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM4_CH4Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM4_CH4Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler,&TIM4_CH4Handler,TIM_CHANNEL_4);//����TIM4ͨ��1
	
    HAL_TIM_PWM_Start(&TIM4_Handler,TIM_CHANNEL_4);//����PWMͨ��1
}


//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM4_CLK_ENABLE();			//ʹ�ܶ�ʱ��2
    __HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_9;           	//PB9
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	GPIO_Initure.Alternate= GPIO_AF2_TIM4;	//PB9����ΪTIM4_CH4
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}


//����TIMͨ��4��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM4Compare4(u32 compare)
{
	TIM4->CCR4=compare; 
}
	
	