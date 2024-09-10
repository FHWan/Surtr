/*
 * timer.c
 *
 *  Created on: 2022年6月12日
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

    //使能IM2时钟
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);

    ultrasonic_GPIO_Init();  //配置Trig和Echo两个引脚

    TIM_DeInit(TIM2);
    //定时器周期，实际就是设定自动重载寄存器 ARR 的值， ARR 为要装载到实际自动重载寄存器（即影子寄存器） 的值， 可设置范围为 0 至 65535。
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    //定时器预分频器设置，时钟源经该预分频器才是定时器计数时钟CK_CNT，它设定 PSC 寄存器的值。
    //计算公式为： 计数器时钟频率 (fCK_CNT) 等于fCK_PSC / (PSC[15:0] + 1)，可实现 1 至 65536 分频。
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    //时钟分频，设置定时器时钟 CK_INT 频率与死区发生器以及数字滤波器采样时钟频率分频比。可以选择 1、 2、 4 分频。
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置计数模式，向上计数模式
    //TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;      //设置重复计数器的值，0。重复计数器，只有 8 位，只存在于高级定时器。
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);            //初始化

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          //TIM1捕获比较中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //设置响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //使能通道
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE ); //使能TIM2更新中断
    TIM_Cmd( TIM2, DISABLE );                    //定时器使能
}

void ENABLE_TIM(void)
{
    //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==RESET)
    {
        TIM_SetCounter(TIM2,0);
        count = 0;
        TIM_Cmd(TIM2,ENABLE);//回响信号到来，开启定时器计数
    }
}

void DISABLE_TIM(void)
{
    //while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==SET)
    {
        TIM_Cmd(TIM2,DISABLE);//回响信号到来，开启定时器计数
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

//一次获取超声波测距数据 两次测距之间需要相隔一段时间，隔断回响信号
//为了消除余震的影响，取五次数据的平均值进行加权滤波。
float Ultrasoniclength(void )
{
    u32 t = 0;
    int i = 0;
    float length = 0 , sum = 0;
    while(i!=5)
    {
       Start_Trig();
       while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==RESET);  //此处一直等，等到为1，进行下一步
       ENABLE_TIM();//回响信号到来，开启定时器计数
       i = i + 1;
       while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==SET);  //此处一直等，等到为0，进行下一步，这两段while之间的时间就是高电平时间，即发出到返回接收的时间
       DISABLE_TIM();//回响信号到来，开启定时器计数
       t = TIM_GetCounter(TIM2);
       length=(t+count*1000)/58.0;//通过回响信号计算距离
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
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志
        count++;
    }
}

