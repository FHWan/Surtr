/**
 ****************************************************************************************************
 * @file        usart.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       串口初始化代码(一般是串口1)，支持printf
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 CH32V307开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20230720
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "./SYSTEM/sys/sys.h"


/* 引脚和串口 定义 */
//#define USART_TX_GPIO_PORT                      GPIOA
//#define USART_TX_GPIO_PIN                       GPIO_Pin_9
//#define USART_TX_GPIO_CLK_ENABLE()              do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0)   /* PA口时钟使能 */
//
//#define USART_RX_GPIO_PORT                      GPIOA
//#define USART_RX_GPIO_PIN                       GPIO_Pin_10
//#define USART_RX_GPIO_CLK_ENABLE()              do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0)   /* PA口时钟使能 */
//
//#define USART_UX                                USART1
//#define USART_UX_IRQn                           USART1_IRQn
//#define USART_UX_IRQHandler                     USART1_IRQHandler
//#define USART_UX_CLK_ENABLE()                   do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); }while(0)  /* USART1 时钟使能 */

#define USART_REC_LEN               200         /* 定义最大接收字节数 200 */
#define USART_EN_RX                 1           /* 使能（1）/禁止（0）串口1接收 */

extern u8 RxBuffer1[200],Rxcouter1;
extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[200],Rxcouter3;

/******************************************************************************************/
void usart_init(uint32_t bound);                /* 串口初始化函数 */
void usart2_init(uint32_t bound);
void usart3_Init(uint32_t bound);
void Uart1_SendStr(char*SendBuf);
void Uart1_Send00(char*SendBuf);
void Uart2_SendStr(char*SendBuf);
void Uart3_SendStr(char*SendBuf);
void Clear_Buffer(uint32_t x);

#endif


