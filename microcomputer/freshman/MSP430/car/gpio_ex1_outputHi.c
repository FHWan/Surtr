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
    // �رտ��Ź�
    WDTCTL = WDTPW | WDTHOLD;
    P7DIR |= BIT0;  P7OUT &= ~BIT0; //��ʼ��������
   /*P7OUT |= BIT0;delay_ms(1);
     P7OUT &= ~BIT0;delay_ms(1);*/
    Motor_Init();                   //��ʼ�� Motor
    Infrared_Init();                //��ʼ�� Infrared
    TimerA0_Capture();
    TimerA1_Capture();
    __bis_SR_register(GIE);
    UART_Init();                    //��ʼ������
    OLED_Init();
    OLED_Clear();
    int t=0;
    // ������ѭ��
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
        case 'F'://ǰ��
        {
            sendstring("ǰ��\r\n");
            tar1 = 30;
            tar2 = 30;
            //Motor_turn(31,30);
            break;
        }
        case 'B'://����
        {
            sendstring("����\r\n");
            Motor_turn(-30,-32);
            break;
        }
        case 'L'://��ת
        {
            sendstring("��ת\r\n");
            Motor_turn(-20,20);
            delay_ms(250);
            Motor_turn(0,0);
            break;
        }
        case 'R'://��ת
        {
            sendstring("��ת\r\n");
            Motor_turn(20,-20);
            delay_ms(250);
            Motor_turn(0,0);
            break;
        }
        case 'P'://ֹͣ
        {
            sendstring("ֹͣ\r\n");
            Motor_turn(0,0);
            break;
        }
    }
}

/*#pragma vector=PORT1_VECTOR // P1���ж�Դ
__interrupt void Port_1 (void)
{
    __disable_interrupt(); // �ر��ܵ��ж����������жϴ����ӳ�

    if (P1IFG & BIT3) // ������P1.3���ж�
    {
        Counter_Left++;
        P1IFG &= ~BIT3; // ���P1.3���жϱ�־λ
    }

    if (P1IFG & BIT6) // ������P1.6���ж�
    {
        Counter_Left++;
        P1IFG &= ~BIT6; // ���P1.6���жϱ�־λ
    }

    if(Counter_Left>=664)
    {
        speedleft++;
        Counter_Left=0;
    }
    __enable_interrupt(); // �ָ��ܵ��ж�����
}*/
