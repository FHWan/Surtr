#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 





extern u8 RxBuffer[200];
extern u8 Rxcouter;





/* USART1 */
#define USART1_MAX_RECV_LEN     200                        /* �����ջ����ֽ��� 200 */
#define USART1_MAX_SEND_LEN     200                        /* ����ͻ����ֽ��� 200 */
extern uint8_t USART1_RX_BUF[USART1_MAX_RECV_LEN];         /* ���ջ���,���USART1_MAX_RECV_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART1_RX_STA;                             /* ����״̬��� */
extern uint8_t USART1_SingleByte;                          /* ���ֽڽ��� */
extern uint8_t USART1_TX_BUF[USART1_MAX_SEND_LEN];     /* ���ͻ���,���USART1_MAX_SEND_LEN���ֽ� */

/* USART2 */
#define USART2_MAX_RECV_LEN     400                        /* �����ջ����ֽ��� 1024 */
#define USART2_SEN_LEN          400                        /* ����ͻ����ֽ��� 1024 */
extern uint8_t USART2_RX_BUF[USART2_MAX_RECV_LEN];         /* ���ջ���,���USART2_MAX_RECV_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART2_RX_STA;                             /* ����״̬��� */
extern __align(8) uint8_t USART2_TX_BUF[USART2_SEN_LEN];   /* ���ͻ���,���USART2_MAX_SEND_LEN���ֽ� */
extern uint8_t USART2_RX_Flag;                         	   /* ����2���ձ�־λ */
extern uint8_t USART2_SingleByte;                          /* ���ֽڽ��� */

#define USART2_DMA_REC_SIZE 400
extern uint8_t USART2_RX_DMA_BUF[USART2_DMA_REC_SIZE];                   /* DMA���ջ���,���USART2_MAX_RECV_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART2_RX_DMA_STA;                                        /* DMA����״̬��� */

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart2_init(u32 bound);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

void Uart2Send(unsigned char *p_data, unsigned int uiSize);	
void printf1(char * fmt,...);







#endif

