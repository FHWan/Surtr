/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Usart6toVision.c
 * ����   :�Ӿ��������ú���
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Usart6toVision.h"

unsigned char Tx_Buf_Uart6[160];
unsigned char Rx_Buf_Uart6[65];

int Flag_Tx_Uart6_Busy=0;

void Usart6toVision_Init(u32 Bound)
{	
  //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
  DMA_InitTypeDef DMA_InitStructure;   
  
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
  
	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream6_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);  
	
	//DMAͨ������
	DMA_DeInit(DMA2_Stream6);  
	DMA_InitStructure.DMA_Channel = DMA_Channel_5;   
	//�����ַ 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART6->DR);  
	//�ڴ��ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Tx_Buf_Uart6;  
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

	//����DMA2��ͨ��           
	DMA_Init(DMA2_Stream6, &DMA_InitStructure);    
	//�ж�ʹ��
	DMA_ITConfig(DMA2_Stream6,DMA_IT_TC,ENABLE);     


  /* ������DMA���� */
	//DMAͨ������  
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
		
	//����DMA2 ��ͨ��          
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);    
	//ʹ��ͨ��
	DMA_Cmd(DMA2_Stream1,ENABLE);  
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART6ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOA9����ΪUSART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOA10����ΪUSART6
	
	//USART6�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA9��PA10


   //USART6 ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART6, &USART_InitStructure); //��ʼ������1
	
  // �ж�����	
	USART_ITConfig(USART6,USART_IT_TC,DISABLE);  
  USART_ITConfig(USART6,USART_IT_RXNE,DISABLE);  
  USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);  

	//USART6 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ�����
	
	//����DMA��ʽ����  
	USART_DMACmd(USART6,USART_DMAReq_Tx,ENABLE);  
	//����DMA��ʽ����
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE);

	USART_ITConfig(USART6,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART6,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART6,USART_IT_TXE,DISABLE);  
	USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);  
	
	//��������
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
		//�����жϵ���ucosϵͳ����
		OSIntEnter();
		if(DMA_GetITStatus(DMA2_Stream6,DMA_IT_TCIF6) != RESET)   
    {  
        //�����־λ  
        DMA_ClearFlag(DMA2_Stream6,DMA_FLAG_TCIF6);  
        //�ر�DMA
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

