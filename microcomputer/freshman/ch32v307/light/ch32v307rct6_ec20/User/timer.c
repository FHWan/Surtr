/*
 * timer.c
 *
 *  Created on: 2022��6��12��
 *      Author: hett
 */


#include "timer.h"
#include "gpio.h"
#include "debug.h"

void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

u16 count = 0;

/*******************************************************************************
* Function Name  : Input_Capture_Init
* Input          : arr: the period value.
*                  psc: the prescaler value.
* Return         : None
*******************************************************************************/
void Input_Capture_Init( u16 arr, u16 psc )
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;

    //ʹ��IM2ʱ��
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);

    ultrasonic_GPIO_Init();  //����Trig��Echo��������

    TIM_DeInit(TIM2);
    //��ʱ�����ڣ�ʵ�ʾ����趨�Զ����ؼĴ��� ARR ��ֵ�� ARR ΪҪװ�ص�ʵ���Զ����ؼĴ�������Ӱ�ӼĴ����� ��ֵ�� �����÷�ΧΪ 0 �� 65535��
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    //��ʱ��Ԥ��Ƶ�����ã�ʱ��Դ����Ԥ��Ƶ�����Ƕ�ʱ������ʱ��CK_CNT�����趨 PSC �Ĵ�����ֵ��
    //���㹫ʽΪ�� ������ʱ��Ƶ�� (fCK_CNT) ����fCK_PSC / (PSC[15:0] + 1)����ʵ�� 1 �� 65536 ��Ƶ��
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    //ʱ�ӷ�Ƶ�����ö�ʱ��ʱ�� CK_INT Ƶ���������������Լ������˲�������ʱ��Ƶ�ʷ�Ƶ�ȡ�����ѡ�� 1�� 2�� 4 ��Ƶ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ü���ģʽ�����ϼ���ģʽ
    //TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;      //�����ظ���������ֵ��0���ظ���������ֻ�� 8 λ��ֻ�����ڸ߼���ʱ����
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);            //��ʼ��

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          //TIM1����Ƚ��ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //������Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //ʹ��ͨ��
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE ); //ʹ��TIM2�����ж�
    TIM_Cmd( TIM2, DISABLE );                    //��ʱ��ʹ��
}

void ENABLE_TIM(void)
{
    //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==RESET)
    {
        TIM_SetCounter(TIM2,0);
        count = 0;
        TIM_Cmd(TIM2,ENABLE);//�����źŵ�����������ʱ������
    }
}

void DISABLE_TIM(void)
{
    //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==SET)
    {
        TIM_Cmd(TIM2,DISABLE);//�����źŵ�����������ʱ������
    }
}

u32 GetCount(void)
{
    u32 t = 0;
    t = count*1000;
    t += TIM_GetCounter(TIM2);
    TIM_SetCounter(TIM2,0);
    Delay_Ms(10);
    return t;
}

//һ�λ�ȡ������������� ���β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�
//Ϊ�����������Ӱ�죬ȡ������ݵ�ƽ��ֵ���м�Ȩ�˲���
float Ultrasoniclength(void )
{
    u32 t = 0;
    int i = 0;
    float length = 0 , sum = 0;
    while(i!=5)
    {
       Start_Trig();
       while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==RESET);  //�˴�һֱ�ȣ��ȵ�Ϊ1��������һ��
       ENABLE_TIM();//�����źŵ�����������ʱ������
       i = i + 1;
       while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==SET);  //�˴�һֱ�ȣ��ȵ�Ϊ0��������һ����������while֮���ʱ����Ǹߵ�ƽʱ�䣬�����������ؽ��յ�ʱ��
       DISABLE_TIM();//�����źŵ�����������ʱ������
       t = TIM_GetCounter(TIM2);
       length=(t+count*1000)/58.0;//ͨ�������źż������
       sum = length + sum ;
       TIM_SetCounter(TIM2,0);
       count = 0;
       Delay_Ms(100);
     }
     length = sum/5.0;
     return length;
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
*******************************************************************************/
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־
        count++;
    }
}

