/*
 * Motor.c
 *
 *  Created on: 2023��7��14��
 *      Author: me
 */
#include <msp430.h>
#include "Motor.h"

#define left 1
#define right 2

void Motor_Init()
{
    //ENB left
    P2DIR |= BIT4;      // P2.4 ����Ϊ���PWM
    P2SEL |= BIT4;      // P2.4 ����Ϊ TimerA2.1 �ĸ��ù���
    P2DIR |= BIT6;  P2OUT &= ~BIT6;
    P2DIR |= BIT2;  P2OUT &= ~BIT2;

    //ENA right
    P2DIR |= BIT5;      //P2.5����Ϊ���PWM
    P2SEL |= BIT5;
    P6DIR |= BIT1;  P6OUT &= ~BIT1;
    P6DIR |= BIT0;  P6OUT &= ~BIT0;

    // ���� TimerA0
    TA2CTL = TASSEL__SMCLK+MC_1;    // ѡ�� SMCLK ��Ϊʱ��Դ��ѡ�� Up ģʽ
    TA2CCR0 = 1500;                 // ���ü������ޣ����� PWM ������
    TA2CCR1 = 750;                  // ��ʼռ�ձ�Ϊ50%
    TA2CCR2 = 750;

    // ���� PWM ���ģʽ
    TA2CCTL1 = OUTMOD_7;
    TA2CCTL2 = OUTMOD_7;
}

/******
return
0:error
1:right
 ******/
int Motor_SetSpeed(int Motor, int Speed)
{
    if(Motor == left){

        if(Speed >= 0){
            P2OUT |= BIT6;
            P2OUT &= ~BIT2;
            TA2CCR1 = (Speed*15);
        }
        else{
            P2OUT &= ~BIT6;
            P2OUT |= BIT2;
            TA2CCR1 = -(Speed*15);
        }

        return 1;
    }
    else if(Motor == right){

            if(Speed >= 0){
                P6OUT |= BIT1;
                P6OUT &= ~BIT0;
                TA2CCR2 = (Speed*15);
            }
            else{
                P6OUT &= ~BIT1;
                P6OUT |= BIT0;
                TA2CCR2 = -(Speed*15);
            }

            return 1;
         }
         else return 0;
}


void Motor_Forward(int Speed)
{
    Motor_SetSpeed(left, Speed);
    Motor_SetSpeed(right, Speed);
}


void Motor_turn(int lSpeed, int rSpeed)
{
    Motor_SetSpeed(left, lSpeed);
    Motor_SetSpeed(right, rSpeed);
}
