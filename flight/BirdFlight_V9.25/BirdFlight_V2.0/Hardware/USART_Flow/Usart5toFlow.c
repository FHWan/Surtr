/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Usart5toFlow.c
 * ����   :���չ�������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Usart5toFlow.h"

unsigned char Tx_Buf_Uart5[160];
unsigned char Rx_Buf_Uart5[65];

int Flag_Tx_Uart5_Busy=0;

void Usart5toFlow_Init(u32 Bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;  
  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE); //ʹ��UART5ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); //ʹ��DMA1ʱ��
	
	//����5��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);  //GPIOC12����ΪUART5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); 	 //GPIOD2����ΪUART5
	
	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  
	
	
	//DMAͨ������
	DMA_DeInit(DMA1_Stream7);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
	//�����ַ 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);  
	//�ڴ��ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Tx_Buf_Uart5;  
	//dma���䷽��
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
	//���ô��仺�����ĳ���  
	DMA_InitStructure.DMA_BufferSize = TX_LEN;  
	//����DMA���������ģʽ һ������  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	//����DMA���ڴ����ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	//���������ֳ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	//�ڴ������ֳ�  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
	//����DMA����ģʽ  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
	//�������ȼ� 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
	//ָ�����FIFOģʽ��ֱ��ģʽ������ָ����������ʹ��FIFOģʽ    
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
	//ָ����FIFO����ֵˮƽ 
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
	//ָ���������ڴ洫��
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
	//ָ����������Χת��   
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   

	//����DMA1��ͨ��           
	DMA_Init(DMA1_Stream7, &DMA_InitStructure);    
	//�ж�ʹ��
	DMA_ITConfig(DMA1_Stream7,DMA_IT_TC,ENABLE);     
	
	

	/* ������DMA���� */
	//DMAͨ������  
	DMA_DeInit(DMA1_Stream0);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART5->DR);  
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Rx_Buf_Uart5;   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;   
	DMA_InitStructure.DMA_BufferSize = TX_LEN;   
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
		
	//����DMA1 ��ͨ��          
	DMA_Init(DMA1_Stream0, &DMA_InitStructure);    
	//ʹ��ͨ��
	DMA_Cmd(DMA1_Stream0,ENABLE); 

	//UART5�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 				//GPIOC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 		//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 			//����
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 				//GPIOD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 		//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 			//����
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//UART5 ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;											//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(UART5, &USART_InitStructure); 												//��ʼ������5
	
	USART_ITConfig(UART5,USART_IT_TC,DISABLE);  
  USART_ITConfig(UART5,USART_IT_RXNE,DISABLE);  
  USART_ITConfig(UART5,USART_IT_IDLE,ENABLE);  

	//Uart5 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;				//����5�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//����DMA��ʽ����  
	USART_DMACmd(UART5,USART_DMAReq_Tx,ENABLE);
	//����DMA��ʽ����
	USART_DMACmd(UART5,USART_DMAReq_Rx,ENABLE);
	
	USART_ITConfig(UART5,USART_IT_TC,DISABLE);  
	USART_ITConfig(UART5,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(UART5,USART_IT_TXE,DISABLE);  
	USART_ITConfig(UART5,USART_IT_IDLE,ENABLE);  
	
	USART_Cmd(UART5, ENABLE);  															//ʹ�ܴ���5 	
}


  
void _Uart5_deal_irq_dma_tx(void)  
{  
    if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7) != RESET)   
    {  

        DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);  

        DMA_Cmd(DMA2_Stream7,DISABLE);  

        USART_ITConfig(UART5,USART_IT_TC,ENABLE);  
    }  
}  
  
 void Usart5_tx(uint8_t *data,uint16_t size)  
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

_Data_Rx Flow_rx; 
void Uart5_irq_handler(void)                                
{  
		OS_ERR err;
    CPU_SR_ALLOC();	
	  OS_CRITICAL_ENTER();
    inf_Uart5_deal_irq_tx_end();  
    Flow_rx.len = inf_Uart5_deal_irq_rx_end(Flow_rx.buf);
    if (Flow_rx.len == 14)  
		{  	
			OSSemPost(&FLOW_proc,OS_OPT_POST_1,&err);
    }
		OS_CRITICAL_EXIT();					
} 


void UART5_IRQHandler(void)   
{  
		OSIntEnter();
    Uart5_irq_handler();
		OSIntExit();	
} 



