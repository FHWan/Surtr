#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8 RxBuffer1[200],Rxcouter1;
extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[200],Rxcouter3;

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void Uart1_SendStr(char*SendBuf);
void Uart2_Send00(char*SendBuf);
void Uart2_SendStr(char*SendBuf);
void Clear_Buffer(u8 x);//清空缓存
#endif


