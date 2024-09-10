#include "hc.h"
#include "delay.h"
#include "sys.h"


//��һ��������Ӳ���ӿڶ���
#define HCSR041_PORT     GPIOA
#define HCSR041_CLK      RCC_AHB1Periph_GPIOA
#define HCSR041_TRIG     GPIO_Pin_0
#define HCSR041_ECHO     GPIO_Pin_1

u16 msHcCount = 0;
//��ʱ��4����
void hcsr04_NVIC()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
	NVIC_Init(&NVIC_InitStructure);
}

//IO�ڳ�ʼ�� ��������ʼ��
void Hcsr041Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   // ���嶨ʱ���ṹ�����
    GPIO_InitTypeDef GPIO_InitStructure;              // ����GPIO�ṹ�����
    RCC_AHB1PeriphClockCmd(HCSR041_CLK, ENABLE);      // ʹ��GPIOAʱ��
   
    GPIO_InitStructure.GPIO_Pin = HCSR041_TRIG;       // ����TRIG����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����IO���ٶ�Ϊ50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     // ����IO��ģʽΪ���
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);     // ��ʼ��GPIOA��TRIG����
    GPIO_ResetBits(HCSR041_PORT, HCSR041_TRIG);       // ��TRIG�����õ�
     
    GPIO_InitStructure.GPIO_Pin = HCSR041_ECHO;       // ����ECHO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      // ����IO��ģʽΪ����
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);     // ��ʼ��GPIOA��ECHO����
    GPIO_ResetBits(HCSR041_PORT, HCSR041_ECHO);       // ��ECHO�����õ�
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   // ʹ�ܶ�ʱ��4ʱ��
     
    TIM_DeInit(TIM2);                                 // ��λ��ʱ��2��ȷ�����øɾ�
    TIM_TimeBaseStructure.TIM_Period = (1000-1);      // ���ü���������Ϊ999
    TIM_TimeBaseStructure.TIM_Prescaler = (72-1);      // ����Ԥ��Ƶ��Ϊ71���õ�1MHz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);     // ��ʼ����ʱ��4�Ļ�������
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);           // �����ʱ��4�ĸ��±�־λ
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);      // ʹ�ܶ�ʱ��4�ĸ����ж�
    hcsr04_NVIC();                                  // ���ö�ʱ��4���ж����ȼ���ʹ���ж�
    TIM_Cmd(TIM4, DISABLE);                         // �رն�ʱ��4     
}

//�򿪶�ʱ��4
static void OpenTimerForHc()  
{
   TIM_SetCounter(TIM4,0);
   msHcCount = 0;
   TIM_Cmd(TIM4, ENABLE); 
}

//�رն�ʱ��4
static void CloseTimerForHc()    
{
   TIM_Cmd(TIM4, DISABLE); 
}

//��ʱ��4���ж�
void TIM4_IRQHandler(void)
{
   // ��鶨ʱ��4�����¼����жϱ�־λ�Ƿ�����
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
   {
       // �����ʱ��4�����¼����жϹ���λ
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
       
       // ����msHcCount������ֵ
       msHcCount++;
   }
} 

//��ȡ��ʱ��4������ֵ
u32 GetEchoTimer(void)
{
   u32 t = 0;
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM4);
   TIM4->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//ͨ����ʱ��4������ֵ�������
float Hcsr041GetLength(void)
{
    u32 t = 0;                 // ���岢��ʼ����ʱ��ֵ����t
    int i = 0;                 // ���岢��ʼ��ѭ��������i
    float lengthTemp1 = 0;     // ���岢��ʼ����ʱ�������lengthTemp1
    float sum = 0;             // ���岢��ʼ�������ܺͱ���sum

    while (i != 5)             // ѭ��ִ��5��
    {
        TRIG1_Send = 1;            // ����TRIG����Ϊ�ߵ�ƽ
        delay_us(20);              // ��ʱ20΢��
        TRIG1_Send = 0;            // ����TRIG����Ϊ�͵�ƽ

        while (ECHO1_Reci == 0);   // �ȴ�ECHO���ŵĸߵ�ƽ�ź�
        
        OpenTimerForHc();          // �����ڳ��������Ķ�ʱ��
        i++;                       // ��������1����ʾ�����һ�β��
        
        while (ECHO1_Reci == 1);   // �ȴ�ECHO���ŵĵ͵�ƽ�ź�
        
        CloseTimerForHc();         // �ر����ڳ��������Ķ�ʱ��
        t = GetEchoTimer();        // ��ȡ��ʱ���ļ���ֵ
        
        lengthTemp1 = ((float)t / 58.0);  // ������ֵת��Ϊ���루��λ��cm��
        sum = lengthTemp1 + sum;          // �����β�����ۼӵ��ܺ���
    }

    lengthTemp1 = sum / 5.0;    // ����ƽ������
    return lengthTemp1;         // ����ƽ������ֵ
}