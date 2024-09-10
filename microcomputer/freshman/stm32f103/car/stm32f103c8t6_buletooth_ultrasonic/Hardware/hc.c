#include "stm32f10x.h"
#include "Delay.h"


#define Echo GPIO_Pin_11		//HC-SR04ģ���Echo�Ž�GPIOB6
#define Trig GPIO_Pin_10		//HC-SR04ģ���Trig�Ž�GPIOB5

uint64_t time=0;			//����������������ʱ
uint64_t time_end=0;		//�����������洢�ز��ź�ʱ��

void HC_SR04_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//����GPIOB������ʱ��	
	GPIO_InitTypeDef GPIO_InitStructure;					//����ṹ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//����GPIO��Ϊ�������
	GPIO_InitStructure.GPIO_Pin = Trig;						//����GPIO��5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����GPIO���ٶ�50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStructure);					//��ʼ��GPIOB
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			//����GPIO��Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = Echo;						//����GPIO��6
	GPIO_Init(GPIOB,&GPIO_InitStructure);					//��ʼ��GPIOB
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,0);						//����͵�ƽ
	Delay_us(15);											//��ʱ15΢��
}

int16_t sonar_mm(void)									//��ಢ���ص�λΪ���׵ľ�����
{
	uint32_t Distance,Distance_mm = 0;
	GPIO_WriteBit(GPIOB,Trig,1);						//����ߵ�ƽ
	Delay_us(15);										//��ʱ15΢��
	GPIO_WriteBit(GPIOB,Trig,0);						//����͵�ƽ
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);		//�ȴ��͵�ƽ����
	time=0;												//��ʱ����
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);		//�ȴ��ߵ�ƽ����
	time_end=time;										//��¼����ʱ��ʱ��
	if(time_end/100<38)									//�ж��Ƿ�С��38���룬����38����ľ��ǳ�ʱ��ֱ�ӵ������淵��0
	{
		Distance=(time_end*346)/2;						//������룬25��C�����е�����Ϊ346m/s
		Distance_mm=Distance/100;						//��Ϊ�����time_end�ĵ�λ��10΢�룬����Ҫ�ó���λΪ���׵ľ����������ó���100
	}
	return Distance_mm;									//���ز����
}

float sonar(void)										//��ಢ���ص�λΪ�׵ľ�����
{
	uint32_t Distance,Distance_mm = 0;
	float Distance_m=0;
	GPIO_WriteBit(GPIOB,Trig,1);					//����ߵ�ƽ
	Delay_us(15);
	GPIO_WriteBit(GPIOB,Trig,0);					//����͵�ƽ
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);
	time=0;
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);
	time_end=time;
	if(time_end/100<38)
	{
		Distance=(time_end*346)/2;
		Distance_mm=Distance/100;
		Distance_m=Distance_mm/1000;
	}
	return Distance_m;
}

void TIM3_IRQHandler(void)			//�����жϺ�����������ʱ��ÿ10΢�����time��1
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//��ȡTIM3��ʱ���ĸ����жϱ�־λ
	{
		time++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//��������жϱ�־λ
	}
}

