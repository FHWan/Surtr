#include "Uart4toTOF.h"
unsigned char Tx_Buf_Uart4[160];
unsigned char Rx_Buf_Uart4[65];

int Flag_Tx_Uart4_Busy=0;

void Uart4toTOF_Init(u32 Bound)
{
	//GPIO管脚配置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
  DMA_InitTypeDef DMA_InitStructure;   
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
  
	//DMA中断配置
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  
	
	//DMA
	DMA_DeInit(DMA1_Stream4);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);  

	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Tx_Buf_Uart4;  

	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  

	DMA_InitStructure.DMA_BufferSize = TX_LEN;  

	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  

	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  

	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
		
  
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      

	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          

	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
  
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   

          
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);    

	DMA_ITConfig(DMA1_Stream4,DMA_IT_TC,ENABLE);     

	//DMA
	DMA_DeInit(DMA1_Stream2);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Rx_Buf_Uart4;   
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
		
    
	DMA_Init(DMA1_Stream2, &DMA_InitStructure);    

	DMA_Cmd(DMA1_Stream2,ENABLE);  
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);		 //GPIOC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);		 //UART4

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); 	//GPIOC10 UART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); 	//GPIOC11 UART4
	
	//UART4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 	 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;							
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 						
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 							
	GPIO_Init(GPIOC,&GPIO_InitStructure); 										

   //UART4 
	USART_InitStructure.USART_BaudRate = Bound;								
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					
	USART_InitStructure.USART_Parity = USART_Parity_No;							
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART4, &USART_InitStructure); 											
	
	
	USART_ITConfig(UART4,USART_IT_TC,DISABLE);  
  USART_ITConfig(UART4,USART_IT_RXNE,DISABLE);  
  USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);  

	//Uart4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
 
	USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);  

	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);

	USART_ITConfig(UART4,USART_IT_TC,DISABLE);  
	USART_ITConfig(UART4,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(UART4,USART_IT_TXE,DISABLE);  
	USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);  
	

	USART_Cmd(UART4, ENABLE);					
}


  
void _Uart4_deal_irq_dma_tx(void)  
{  
    if(DMA_GetITStatus(DMA1_Stream4,DMA_IT_TCIF4) != RESET)   
    {  

        DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);  

        DMA_Cmd(DMA1_Stream4,DISABLE);  

        USART_ITConfig(UART4,USART_IT_TC,ENABLE);  
    }  
}  
  
  
uint8_t _Uart4_deal_irq_tx_end(void)  
{  
    if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)  
    {  
        USART_ITConfig(UART4,USART_IT_TC,DISABLE);  
        Flag_Tx_Uart4_Busy = 0;  
          
        return 1;  
    }        
    return 0;  
}  


  
void Uart4_tx(uint8_t *data,uint16_t size)  
{  
    while (Flag_Tx_Uart4_Busy);  
    Flag_Tx_Uart4_Busy = 1;  
    memcpy(Tx_Buf_Uart4,data,size);  
    DMA_SetCurrDataCounter(DMA1_Stream4,size);  
    DMA_Cmd(DMA1_Stream4,ENABLE);  
}  



uint8_t _Uart4_deal_irq_rx_end(uint8_t *buf)  
{     
    uint16_t len = 0;  
      
    if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  
    {  
        UART4->SR;  
        UART4->DR; 
        DMA_Cmd(DMA1_Stream2,DISABLE);   
        DMA_ClearFlag(DMA1_Stream2,DMA_FLAG_TCIF2);   
        len = RX_LEN - DMA_GetCurrDataCounter(DMA1_Stream2);  
        memcpy(buf,Rx_Buf_Uart4,len);  
          
        DMA_SetCurrDataCounter(DMA1_Stream2,RX_LEN);  

        DMA_Cmd(DMA1_Stream2,ENABLE);  
  
        return len;  
    }   
      
    return 0;  
}  


  
void inf_Uart4_deal_irq_dma_tx(void)  
{  
    _Uart4_deal_irq_dma_tx();  
}  

  
uint8_t inf_Uart4_deal_irq_tx_end(void)  
{  
    return _Uart4_deal_irq_tx_end();  
}  
  
  
uint8_t inf_Uart4_deal_irq_rx_end(uint8_t *buf)  
{  
    return _Uart4_deal_irq_rx_end(buf);  
}

  
void Uart4_dma_tx_irq_handler(void)  
{  
    inf_Uart4_deal_irq_dma_tx();  
}  


_Data_Rx TOF_rx;
void Uart4_irq_handler(void){  	
		OS_ERR err;	 
    inf_Uart4_deal_irq_tx_end();  	  
    TOF_rx.len = inf_Uart4_deal_irq_rx_end(TOF_rx.buf);  
    if (TOF_rx.len != 0)  
		{  	
			OSSemPost(&TOF_proc,OS_OPT_POST_1,&err);
    }
} 



  
void DMA1_Stream4_IRQHandler(void)  
{  	
		OSIntEnter();
    Uart4_dma_tx_irq_handler(); 
		OSIntExit();	
}  
      
  
void UART4_IRQHandler(void)   
{  
		OSIntEnter();
    Uart4_irq_handler(); 
		OSIntExit();
}



