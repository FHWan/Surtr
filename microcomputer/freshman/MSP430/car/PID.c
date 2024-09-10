/*
 * timer.c
 *
 *  Created on: 2023年7月16日
 *      Author: 30411
 */
#include <msp430.h>
#include "Infrared.h"
#include "PID.h"
#include "Motor.h"
#include "oled.h"

volatile int    encoderCount = 0;
volatile int    encoderCount2 = 0;
volatile int    time = 0;
volatile float  speedleft = 0;
volatile float  speedright = 0;

/* @breif:Timer_A0 输入捕获初始化，可用来读取编码器
 * @parm: None
 */
void TimerA0_Capture(void)
{
    TA0CCTL0 = CCIE;            // 允许定时器A0的CCR0中断
    TA0CCR0 = 25000;            // 设置CCR0的值，产生1ms的中断（1/25MHz * 25000 = 1ms）
    TA0CTL = TASSEL_2 + MC_1;   // 选择SMCLK作为时钟源，设置计数器为增计数模式

    __enable_interrupt();       // 全局使能中断

    P1DIR &= ~(BIT2 + BIT3);    // 将P1.2和P1.3设置为输入模式
    P1SEL |= BIT2 + BIT3;       // 将P1.2和P1.3选择为TimerA0的功能

    TA0CTL = TASSEL_2 + MC_2 + TACLR;   // 选择SMCLK作为时钟源，设置计数器为连续计数模式，并清除计数器
    TA0CCTL2 = CM_1 + CCIS_0 + CAP + CCIE; // 设置为下降沿捕获模式，选择CCIxA作为输入源，启用捕获模式，并启用捕获比较中断
}
void TimerA1_Capture(void)
{
        TA1CTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3; //SMCLK,连续计数，中断允许，计数器清零
        TA1CCTL1 |= CAP+CM_1+CCIS_0+CCIE;           //捕获模式，上升沿捕获，CCI1A输入，同步捕获，中断允许
        P2DIR &=~ BIT0;                             //初始化捕获IO口
        P2SEL |=  BIT0;
}

float Err=0,Er_1=0,Er_2=0,PWM=0,add=0,P=0.5,I=0.1,D=0,Limit=99;//所用电机最高速度为100

float pid(float speed,int tar)//利用PID控制速度
{
    if(speed<0)
        speed=-speed;
    int Err=tar-speed;
    add=P*(Err-Er_1)+I*(Err)+D*(Err+Er_2-2*Er_1);
    PWM+=add;
    if(PWM > Limit)
        PWM=Limit;
    if(PWM<0)
        PWM=0;
    Er_2=Er_1;
    Er_1=Err;
    return PWM;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR(void)
{
    time++;
    if(time>=5)
    {
        speedleft  = (float) encoderCount  / 4;
        speedright = (float) encoderCount2 / 4;
        //OLED_ShowNum(1,1,speedleft,4,12);
        //OLED_ShowNum(1,3,speedright,4,12);
        if(tar1<0)  speedleft  = -speedleft;
        if(tar2<0)  speedright = -speedright;
        speedleft  = pid(speedleft ,tar1);
        speedright = pid(speedright,tar2);
        if(tar1<0)  speedleft  = -speedleft;
        if(tar2<0)  speedright = -speedright;
        //Motor_turn(speedleft,speedright);
        //OLED_ShowNum(1,5,speedleft,4,12);
        //OLED_ShowNum(1,7,speedright,4,12);
        encoderCount  = 0;
        encoderCount2 = 0;
        time=0;
    }
    TA0CCTL1 &= ~CCIFG;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerA0_CCR1_ISR(void)
{
    if (TA0CCTL2 & CCI)
        encoderCount++;

    TA0CCTL2 &= ~CCIFG;   // 清除CCR2中断标志
}

#pragma vector=TIMER1_A1_VECTOR  //Timer_A捕获中断向量 p2.0
__interrupt void Timer_A1(void)
{
    if(TA1IV == 2)
        encoderCount2++;

    TA1CCTL1 &= ~CCIFG;   // 清除中断标志
}
