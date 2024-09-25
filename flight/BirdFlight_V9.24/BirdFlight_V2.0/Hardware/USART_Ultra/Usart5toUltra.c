/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Usart5toUltra.c
 * 描述   :超声波是数据接收串口
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Usart5toUltra.h"

unsigned char Rx_Buf_Uart5[16];
unsigned char Tx_Buf_Uart5[16];
int Flag_Tx_Uart5_Busy=0;

void Uart5toUltra_Init(u32 Bound)
{	
  //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;  
  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE); //使能UART5时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); //使能DMA1时钟
	
	//串口5对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);  //GPIOC12复用为UART5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); 	 //GPIOD2复用为UART5
	
	//DMA发送中断设置
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  
	
	
	//DMA通道配置
	DMA_DeInit(DMA1_Stream7);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
	//外设地址 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);  
	//内存地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Tx_Buf_Uart5;  
	//dma传输方向
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
	//设置传输缓冲区的长度  
	DMA_InitStructure.DMA_BufferSize = TX_LEN;  
	//设置DMA的外设递增模式 一个外设  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//设置DMA的内存递增模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//外设数据字长 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//内存数据字长  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//设置DMA传输模式  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
	//设置优先级 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//指定如果FIFO模式或直接模式将用于指定的流：不使能FIFO模式    
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
	//指定了FIFO的阈值水平 
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
	//指定的配置内存传输
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
	//指定的配置外围转移   
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   

	//配置DMA1的通道           
	DMA_Init(DMA1_Stream7, &DMA_InitStructure);    
	//中断使能
	DMA_ITConfig(DMA1_Stream7,DMA_IT_TC,ENABLE);     
	
	

	/* 串口收DMA配置 */
	//DMA通道配置  
	DMA_DeInit(DMA1_Stream0);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Rx_Buf_Uart5;   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;   
	DMA_InitStructure.DMA_BufferSize = RX_LEN;   
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;    
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;    
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
  
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;           
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;           
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
		
	//配置DMA1 收通道          
	DMA_Init(DMA1_Stream0, &DMA_InitStructure);    
	//使能通道
	DMA_Cmd(DMA1_Stream0,ENABLE); 


	//UART5端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 				//GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 		//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 			//上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 				//GPIOD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 		//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 			//上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//UART5 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;											//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;							//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART5, &USART_InitStructure); 												//初始化串口5
	
	USART_ITConfig(UART5,USART_IT_TC,DISABLE);  
  USART_ITConfig(UART5,USART_IT_RXNE,DISABLE);  
  USART_ITConfig(UART5,USART_IT_IDLE,ENABLE);  

	//Uart5 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;				//串口5中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;	//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;				//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);													//根据指定的参数初始化VIC寄存器
	
	//采用DMA方式发送  
	USART_DMACmd(UART5,USART_DMAReq_Tx,ENABLE);
	//采用DMA方式接收
	USART_DMACmd(UART5,USART_DMAReq_Rx,ENABLE);
	
	USART_ITConfig(UART5,USART_IT_TC,DISABLE);  
	USART_ITConfig(UART5,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(UART5,USART_IT_TXE,DISABLE);  
	USART_ITConfig(UART5,USART_IT_IDLE,ENABLE);  
	
	USART_Cmd(UART5, ENABLE);  															//使能串口5 
}

void Uart5_tx(uint8_t *data,uint16_t size)  
{  
    while (Flag_Tx_Uart5_Busy);  
    Flag_Tx_Uart5_Busy = 1;   
    memcpy(Tx_Buf_Uart5,data,size);  
    DMA_SetCurrDataCounter(DMA1_Stream7,size);   
    DMA_Cmd(DMA1_Stream7,ENABLE);  
}  

uint8_t inf_Uart5_deal_irq_tx_end(void)  
{  
    if(USART_GetITStatus(UART5, USART_IT_TC) != RESET)  
    {  
        USART_ITConfig(UART5,USART_IT_TC,DISABLE);  
        Flag_Tx_Uart5_Busy = 0;  
          
        return 1;  
    }        
    return 0;    
}


uint8_t inf_Uart5_deal_irq_rx_end(uint8_t *buf)  
{  
   uint16_t len = 0;  
      
    if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)  
    {  
        UART5->SR;  
        UART5->DR;
        DMA_Cmd(DMA1_Stream0,DISABLE);  
        DMA_ClearFlag(DMA1_Stream0,DMA_FLAG_TCIF0);  
        len = RX_LEN - DMA_GetCurrDataCounter(DMA1_Stream0);  
        memcpy(buf,Rx_Buf_Uart5,len);   
        DMA_SetCurrDataCounter(DMA1_Stream0,RX_LEN);  
        DMA_Cmd(DMA1_Stream0,ENABLE);  
        return len;  
    }   
    return 0;  
}

void DMA1_Stream7_IRQHandler(void)  
{  
		OSIntEnter();
		if(DMA_GetITStatus(DMA1_Stream7,DMA_IT_TCIF7) != RESET)   
    {  
        DMA_ClearFlag(DMA1_Stream7,DMA_FLAG_TCIF7);  
        DMA_Cmd(DMA1_Stream7,DISABLE);    
        USART_ITConfig(UART5,USART_IT_TC,ENABLE);  
    } 
		OSIntExit();		
} 




uint16_t ReceiveHeight;
_Data_Rx Ultradata;
void Uart5_irq_handler(void)                                
{     
	inf_Uart5_deal_irq_tx_end();
	Ultradata.len = inf_Uart5_deal_irq_rx_end(Ultradata.buf);  
	if (Ultradata.len != 0)  
	{ 
		ReceiveHeight = ((((uint16_t)Ultradata.buf[0])<<8) + Ultradata.buf[1]);
	}				
} 




void UART5_IRQHandler(void)   
{  
		OSIntEnter();
    Uart5_irq_handler();
		OSIntExit();	
} 

 

void ReceiveUltraData()
{
	static u8 senddata[1] = {0x55};
	Uart5_tx(senddata,1);
}
	
void SendStopflag()
{
	//发送ASCII码字符 “1”
	USART_SendData(USART6,0X31);
}

