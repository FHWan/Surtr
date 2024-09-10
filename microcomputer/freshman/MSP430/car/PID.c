/*
 * timer.c
 *
 *  Created on: 2023��7��16��
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

/* @breif:Timer_A0 ���벶���ʼ������������ȡ������
 * @parm: None
 */
void TimerA0_Capture(void)
{
    TA0CCTL0 = CCIE;            // ����ʱ��A0��CCR0�ж�
    TA0CCR0 = 25000;            // ����CCR0��ֵ������1ms���жϣ�1/25MHz * 25000 = 1ms��
    TA0CTL = TASSEL_2 + MC_1;   // ѡ��SMCLK��Ϊʱ��Դ�����ü�����Ϊ������ģʽ

    __enable_interrupt();       // ȫ��ʹ���ж�

    P1DIR &= ~(BIT2 + BIT3);    // ��P1.2��P1.3����Ϊ����ģʽ
    P1SEL |= BIT2 + BIT3;       // ��P1.2��P1.3ѡ��ΪTimerA0�Ĺ���

    TA0CTL = TASSEL_2 + MC_2 + TACLR;   // ѡ��SMCLK��Ϊʱ��Դ�����ü�����Ϊ��������ģʽ�������������
    TA0CCTL2 = CM_1 + CCIS_0 + CAP + CCIE; // ����Ϊ�½��ز���ģʽ��ѡ��CCIxA��Ϊ����Դ�����ò���ģʽ�������ò���Ƚ��ж�
}
void TimerA1_Capture(void)
{
        TA1CTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3; //SMCLK,�����������ж���������������
        TA1CCTL1 |= CAP+CM_1+CCIS_0+CCIE;           //����ģʽ�������ز���CCI1A���룬ͬ�������ж�����
        P2DIR &=~ BIT0;                             //��ʼ������IO��
        P2SEL |=  BIT0;
}

float Err=0,Er_1=0,Er_2=0,PWM=0,add=0,P=0.5,I=0.1,D=0,Limit=99;//���õ������ٶ�Ϊ100

float pid(float speed,int tar)//����PID�����ٶ�
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

    TA0CCTL2 &= ~CCIFG;   // ���CCR2�жϱ�־
}

#pragma vector=TIMER1_A1_VECTOR  //Timer_A�����ж����� p2.0
__interrupt void Timer_A1(void)
{
    if(TA1IV == 2)
        encoderCount2++;

    TA1CCTL1 &= ~CCIFG;   // ����жϱ�־
}
