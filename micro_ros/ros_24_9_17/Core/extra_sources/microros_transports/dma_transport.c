#include <uxr/client/transport.h>

#include <rmw_microxrcedds_c/config.h>

#include "main.h"
#include "cmsis_os.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "usart.h"
#include <JY61P/jy61p.h>
#include <Robotic_arm/robotic_arm.h>
#include <comm/comm.h>

#ifdef RMW_UXRCE_TRANSPORT_CUSTOM

// --- micro-ROS Transports ---
#define UART_DMA_BUFFER_SIZE 2048

static uint8_t dma_buffer[UART_DMA_BUFFER_SIZE];
static size_t dma_head = 0, dma_tail = 0;

bool cubemx_transport_open(struct uxrCustomTransport * transport){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;
    HAL_UART_Receive_DMA(uart, dma_buffer, UART_DMA_BUFFER_SIZE);
    return true;
}

bool cubemx_transport_close(struct uxrCustomTransport * transport){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;
    HAL_UART_DMAStop(uart);
    return true;
}

size_t cubemx_transport_write(struct uxrCustomTransport* transport, uint8_t * buf, size_t len, uint8_t * err){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;

    HAL_StatusTypeDef ret;
    if (uart->gState == HAL_UART_STATE_READY){
        ret = HAL_UART_Transmit_DMA(uart, buf, len);
        while (ret == HAL_OK && uart->gState != HAL_UART_STATE_READY){
            osDelay(1);
        }

        return (ret == HAL_OK) ? len : 0;
    }else{
        return 0;
    }
}

size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;

    int ms_used = 0;
    do
    {
        __disable_irq();
        dma_tail = UART_DMA_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(uart->hdmarx);
        __enable_irq();
        ms_used++;
        osDelay(portTICK_RATE_MS);
    } while (dma_head == dma_tail && ms_used < timeout);
    
    size_t wrote = 0;
    while ((dma_head != dma_tail) && (wrote < len)){
        buf[wrote] = dma_buffer[dma_head];
        dma_head = (dma_head + 1) % UART_DMA_BUFFER_SIZE;
        wrote++;
    }
    
    return wrote;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	if(huart == &huart1)
//	{
//	  KDCOM_Process((uint8*)rxbuf, &channel, pchxp, pchxi, pchxd, pchxt, pchxa, &startflag, &stopflag, 0, 0);
//	  memset(rxbuf, 0, 40);
//	  HAL_UART_Receive_DMA(&huart1, rxbuf, 40);
//	}
	if(huart==&huart2)
	{
		HAL_UART_Receive_DMA(&huart2, dma_buffer, UART_DMA_BUFFER_SIZE);
	}
	else if(huart==&huart3)
	{
		CopeSerial2Data(rx_buff1);
		HAL_UART_Receive_IT(&huart3,&rx_buff1,1);
	}
	else if(huart == &huart1)
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了
			}
			else //还没收到0X0D
			{
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收
				}
			}
		}
		HAL_UART_Receive_IT(&huart1,&aRxBuffer,1);
//	  KDCOM_Process((uint8*)rxbuf, &channel, pchxp, pchxi, pchxd, pchxt, pchxa, &startflag, &stopflag, 0, 0);
//	  memset(rxbuf, 0, 40);
//	  HAL_UART_Receive_DMA(&huart1, rxbuf, 40);
	}
//	else if(huart==&huart6)
//	{
//		CopeSerialData_arm(rx_buff_arm);
//		HAL_UART_Receive_IT(&huart6,&rx_buff_arm,1);
//	}
}


#endif //RMW_UXRCE_TRANSPORT_CUSTOM
