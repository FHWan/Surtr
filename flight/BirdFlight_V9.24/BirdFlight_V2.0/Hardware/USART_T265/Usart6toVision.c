/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Usart6toVision.c
 * 描述   :视觉串口配置函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Usart6toVision.h"

unsigned char Tx_Buf_Uart6[160];
unsigned char Rx_Buf_Uart6[65];

int Flag_Tx_Uart6_Busy=0;

void Usart6toVision_Init(u32 Bound)
{	
  //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
  DMA_InitTypeDef DMA_InitStructure;   
  
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
  
	//DMA发送中断设置
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream6_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  
	
	//DMA通道配置
	DMA_DeInit(DMA2_Stream6);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_5;   
	//外设地址 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART6->DR);  
	//内存地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Tx_Buf_Uart6;  
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

	//配置DMA2的通道           
	DMA_Init(DMA2_Stream6, &DMA_InitStructure);    
	//中断使能
	DMA_ITConfig(DMA2_Stream6,DMA_IT_TC,ENABLE);     


  /* 串口收DMA配置 */
	//DMA通道配置  
	DMA_DeInit(DMA2_Stream1);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_5;   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART6->DR);  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Rx_Buf_Uart6;   
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
		
	//配置DMA2 收通道          
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);    
	//使能通道
	DMA_Cmd(DMA2_Stream1,ENABLE);  
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOA9复用为USART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOA10复用为USART6
	
	//USART6端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10


   //USART6 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART6, &USART_InitStructure); //初始化串口1
	
  // 中断配置	
	USART_ITConfig(USART6,USART_IT_TC,DISABLE);  
  USART_ITConfig(USART6,USART_IT_RXNE,DISABLE);  
  USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);  

	//USART6 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器、
	
	//采用DMA方式发送  
	USART_DMACmd(USART6,USART_DMAReq_Tx,ENABLE);  
	//采用DMA方式接收
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE);

	USART_ITConfig(USART6,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART6,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART6,USART_IT_TXE,DISABLE);  
	USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);  
	
	//启动串口
	USART_Cmd(USART6, ENABLE);
}


void Usart6_tx(uint8_t *data,uint16_t size)  
{  
    while (Flag_Tx_Uart6_Busy);  
    Flag_Tx_Uart6_Busy = 1;   
    memcpy(Tx_Buf_Uart6,data,size);  
    DMA_SetCurrDataCounter(DMA2_Stream6,size);   
    DMA_Cmd(DMA2_Stream6,ENABLE);  
}  


   
uint8_t inf_Uart6_deal_irq_tx_end(void)  
{  
    if(USART_GetITStatus(USART6, USART_IT_TC) != RESET)  
    {  
        USART_ITConfig(USART6,USART_IT_TC,DISABLE);  
        Flag_Tx_Uart6_Busy = 0;  
          
        return 1;  
    }        
    return 0;    
}  
  
 
uint8_t inf_Uart6_deal_irq_rx_end(uint8_t *buf)  
{  
   uint16_t len = 0;  
      
    if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)  
    {  
        USART6->SR;  
        USART6->DR;
        DMA_Cmd(DMA2_Stream1,DISABLE);  
        DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);  
        len = RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream1);  
        memcpy(buf,Rx_Buf_Uart6,len);   
        DMA_SetCurrDataCounter(DMA2_Stream1,RX_LEN);  
        DMA_Cmd(DMA2_Stream1,ENABLE);  
        return len;  
    }   
    return 0;  
}

     
  
void DMA2_Stream6_IRQHandler(void)  
{  
		//进入中断调用ucos系统函数
		OSIntEnter();
		if(DMA_GetITStatus(DMA2_Stream6,DMA_IT_TCIF6) != RESET)   
    {  
        //清除标志位  
        DMA_ClearFlag(DMA2_Stream6,DMA_FLAG_TCIF6);  
        //关闭DMA
        DMA_Cmd(DMA2_Stream6,DISABLE);    
        USART_ITConfig(USART6,USART_IT_TC,ENABLE);  
    } 
		OSIntExit();		
}  
     
_Vio_Rx t265_Rx;
void USART6_IRQHandler(void)   
{  
		OS_ERR err;	 
		OSIntEnter();	
    inf_Uart6_deal_irq_tx_end();  	  
    t265_Rx.len = inf_Uart6_deal_irq_rx_end(t265_Rx.buf);  
    if (t265_Rx.len == 65)  
		{  	
			OSSemPost(&VIO_proc,OS_OPT_POST_1,&err);
    }
		OSIntExit();
} 

