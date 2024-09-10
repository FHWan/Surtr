/*
 * Infrared.c
 *
 *  Created on: 2023��7��15��
 *      Author: me
 */

#include <msp430.h>
#include "Motor.h"
#include "PID.h"

#define  L1  (P4IN & BIT3)
#define  L2  (P4IN & BIT0)
#define  M   (P3IN & BIT7)
#define  R2  (P8IN & BIT2)
#define  R1  (P8IN & BIT1)

volatile int tar1 = 0;
volatile int tar2 = 0;

void Infrared_Init(void)
{
    P4DIR &= ~BIT3;
    P4DIR &= ~BIT0;
    P3DIR &= ~BIT7;
    P8DIR &= ~BIT2;
    P8DIR &= ~BIT1;
}

void Infrared_find(void)
{
    if(R2!=0&&L2!=0)
    {
        //tar1=30;tar2=30;
        //Motor_turn(speedleft,speedright);
        Motor_turn(36,35);
    }

    if(R2!=0&&L2==0)                    //С��ת
    {
        //tar1=20;tar2=30;
        Motor_turn(26,35);
        while(!(M==0&&R2!=0&&L2!=0))    //û��������һֱת
        {
            //Motor_turn(speedleft,speedright);
            if(L1==0)                   //����ת
            {
                //tar1=-15;tar2=30;
                Motor_turn(-25,40);
            }
            if(R2==0)
            {
                //tar1=30;tar2=20;
                Motor_turn(36,25);
            }
            if(R1==0)
            {
                //tar1=30;tar2=-15;
                Motor_turn(40,-25);
            }
        }
    }

    if(L1==0)                   //����ת
    {
        //tar1=-15;tar2=30;
        Motor_turn(-25,40);
        delay_ms(60);
        while(!(M==0&&R2!=0&&L2!=0))    //û��������һֱת
        {
            //Motor_turn(speedleft,speedright);
            if(R2==0)
            {
                //tar1=30;tar2=20;
                Motor_turn(36,25);
            }

        }
    }

    if(L2!=0&&R2==0)        //С��ת
    {
        //tar1=30;tar2=20;
        Motor_turn(36,25);
        while(!(M==0&&L2!=0&&R2!=0))    //һֱת
        {
            //Motor_turn(speedleft,speedright);
            if(R1==0)                   //����ת
            {
                //tar1=30;tar2=-15;
                Motor_turn(40,-25);
            }
            if(L2==0)
            {
                //tar1=20;tar2=30;
                Motor_turn(26,35);
            }
            if(L1==0)
            {
                //tar1=-15;tar2=30;
                Motor_turn(-25,40);
            }
          }
    }

    if(R1==0)                   //����ת
    {
        //tar1=30;tar2=-15;
        Motor_turn(40,-25);
        delay_ms(60);
        while(!(M==0&&L2!=0&&R2!=0))    //һֱת
        {
            //Motor_turn(speedleft,speedright);
            if(L2==0)
           {
                //tar1=20;tar2=30;
                Motor_turn(26,35);
           }
        }
    }
}
