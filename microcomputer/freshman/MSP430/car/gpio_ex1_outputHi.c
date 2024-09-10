#include <msp430.h>
#include <string.h>
#include "Motor.h"
#include "Infrared.h"
#include "UART.h"
#include "oled.h"
#include "PID.h"

void countrle(void);

char *p;

int main(void)
{
    // 关闭看门狗
    WDTCTL = WDTPW | WDTHOLD;
    P7DIR |= BIT0;  P7OUT &= ~BIT0; //初始化蜂鸣器
   /*P7OUT |= BIT0;delay_ms(1);
     P7OUT &= ~BIT0;delay_ms(1);*/
    Motor_Init();                   //初始化 Motor
    Infrared_Init();                //初始化 Infrared
    TimerA0_Capture();
    TimerA1_Capture();
    __bis_SR_register(GIE);
    UART_Init();                    //初始化串口
    OLED_Init();
    OLED_Clear();
    int t=0;
    // 进入主循环
    while (1)
    {
        /*Motor_turn(30,30);
        OLED_ShowNum(1,1,speedleft,4,12);
        OLED_ShowNum(1,3,speedright,4,12);*/
        if(UCA0TXBUF == 'G')
        {
            for(t=0;t<=200;t++)
            {
                P7OUT |= BIT0;delay_ms(1);
                P7OUT &= ~BIT0;delay_ms(1);
            }
            while(1)
                Infrared_find();
        }
    }
}
void countrle(void)
{
    switch (UCA0TXBUF)
    {
        case 'F'://前进
        {
            sendstring("前进\r\n");
            tar1 = 30;
            tar2 = 30;
            //Motor_turn(31,30);
            break;
        }
        case 'B'://后退
        {
            sendstring("后退\r\n");
            Motor_turn(-30,-32);
            break;
        }
        case 'L'://左转
        {
            sendstring("左转\r\n");
            Motor_turn(-20,20);
            delay_ms(250);
            Motor_turn(0,0);
            break;
        }
        case 'R'://右转
        {
            sendstring("右转\r\n");
            Motor_turn(20,-20);
            delay_ms(250);
            Motor_turn(0,0);
            break;
        }
        case 'P'://停止
        {
            sendstring("停止\r\n");
            Motor_turn(0,0);
            break;
        }
    }
}

/*#pragma vector=PORT1_VECTOR // P1口中断源
__interrupt void Port_1 (void)
{
    __disable_interrupt(); // 关闭总的中断允许，避免中断处理延迟

    if (P1IFG & BIT3) // 当发生P1.3口中断
    {
        Counter_Left++;
        P1IFG &= ~BIT3; // 清除P1.3口中断标志位
    }

    if (P1IFG & BIT6) // 当发生P1.6口中断
    {
        Counter_Left++;
        P1IFG &= ~BIT6; // 清除P1.6口中断标志位
    }

    if(Counter_Left>=664)
    {
        speedleft++;
        Counter_Left=0;
    }
    __enable_interrupt(); // 恢复总的中断允许
}*/
