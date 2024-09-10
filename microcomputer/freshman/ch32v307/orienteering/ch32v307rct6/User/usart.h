#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "ch32v30x.h"

/* UART Printf Definition */
#define DEBUG_UART1    1
#define DEBUG_UART2    2
#define DEBUG_UART3    3

/* DEBUG UATR Definition */
//#define DEBUG   DEBUG_UART1
#define DEBUG   DEBUG_UART2
//#define DEBUG   DEBUG_UART3

void Clear_Buffer(u8 x);
void USART1_Init(u32 baudrate);
void USART2_Init(u32 baudrate);
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART3_Init(u32 baudrate);
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Uart3_SendStr(char*SendBuf);
void Uart1_SendStr(char*SendBuf);
void Uart2_SendStr(char*SendBuf);
void Uart2_SendDATA(u8 *SendBuf,u8 len);



#endif


