/**
 ****************************************************************************************************
 * @file        usart.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       ���ڳ�ʼ������(һ���Ǵ���1)��֧��printf
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� CH32V307������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20230720
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "./SYSTEM/sys/sys.h"


/* ���źʹ��� ���� */
//#define USART_TX_GPIO_PORT                      GPIOA
//#define USART_TX_GPIO_PIN                       GPIO_Pin_9
//#define USART_TX_GPIO_CLK_ENABLE()              do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0)   /* PA��ʱ��ʹ�� */
//
//#define USART_RX_GPIO_PORT                      GPIOA
//#define USART_RX_GPIO_PIN                       GPIO_Pin_10
//#define USART_RX_GPIO_CLK_ENABLE()              do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0)   /* PA��ʱ��ʹ�� */
//
//#define USART_UX                                USART1
//#define USART_UX_IRQn                           USART1_IRQn
//#define USART_UX_IRQHandler                     USART1_IRQHandler
//#define USART_UX_CLK_ENABLE()                   do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); }while(0)  /* USART1 ʱ��ʹ�� */

#define USART_REC_LEN               200         /* �����������ֽ��� 200 */
#define USART_EN_RX                 1           /* ʹ�ܣ�1��/��ֹ��0������1���� */

extern u8 RxBuffer1[200],Rxcouter1;
extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[200],Rxcouter3;

/******************************************************************************************/
void usart_init(uint32_t bound);                /* ���ڳ�ʼ������ */
void usart2_init(uint32_t bound);
void usart3_Init(uint32_t bound);
void Uart1_SendStr(char*SendBuf);
void Uart1_Send00(char*SendBuf);
void Uart2_SendStr(char*SendBuf);
void Uart3_SendStr(char*SendBuf);
void Clear_Buffer(uint32_t x);

#endif


