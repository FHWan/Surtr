#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 





extern u8 RxBuffer[200];
extern u8 Rxcouter;





/* USART1 */
#define USART1_MAX_RECV_LEN     200                        /* 最大接收缓存字节数 200 */
#define USART1_MAX_SEND_LEN     200                        /* 最大发送缓存字节数 200 */
extern uint8_t USART1_RX_BUF[USART1_MAX_RECV_LEN];         /* 接收缓冲,最大USART1_MAX_RECV_LEN个字节.末字节为换行符 */
extern uint16_t USART1_RX_STA;                             /* 接收状态标记 */
extern uint8_t USART1_SingleByte;                          /* 单字节接收 */
extern uint8_t USART1_TX_BUF[USART1_MAX_SEND_LEN];     /* 发送缓冲,最大USART1_MAX_SEND_LEN个字节 */

/* USART2 */
#define USART2_MAX_RECV_LEN     400                        /* 最大接收缓存字节数 1024 */
#define USART2_SEN_LEN          400                        /* 最大发送缓存字节数 1024 */
extern uint8_t USART2_RX_BUF[USART2_MAX_RECV_LEN];         /* 接收缓冲,最大USART2_MAX_RECV_LEN个字节.末字节为换行符 */
extern uint16_t USART2_RX_STA;                             /* 接收状态标记 */
extern __align(8) uint8_t USART2_TX_BUF[USART2_SEN_LEN];   /* 发送缓冲,最大USART2_MAX_SEND_LEN个字节 */
extern uint8_t USART2_RX_Flag;                         	   /* 串口2接收标志位 */
extern uint8_t USART2_SingleByte;                          /* 单字节接收 */

#define USART2_DMA_REC_SIZE 400
extern uint8_t USART2_RX_DMA_BUF[USART2_DMA_REC_SIZE];                   /* DMA接收缓冲,最大USART2_MAX_RECV_LEN个字节.末字节为换行符 */
extern uint16_t USART2_RX_DMA_STA;                                        /* DMA接收状态标记 */

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void uart2_init(u32 bound);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

void Uart2Send(unsigned char *p_data, unsigned int uiSize);	
void printf1(char * fmt,...);







#endif

