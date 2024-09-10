#include "sys.h"
#include "usart.h"	  
#include "OLED.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

void Uart1_SendStr(char*SendBuf)//����1��ӡ����
{
	while(*SendBuf)
	{
	  while((USART1->SR&0X40)==0);//�ȴ�������� 
    USART1->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}

void Uart2_SendStr(char*SendBuf)//����1��ӡ����
{
	while(*SendBuf)
	{
	  while((USART2->SR&0X40)==0);//�ȴ�������� 
    USART2->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

u8 RxBuffer1[200],Rxcouter1=0;
u8 RxBuffer2[200],Rxcouter2=0;
int i=0,j=0;
int colour_x=0,colour_y=0;
int LS_x=0,LS_y=0;//����
int LX_x=0,LX_y=0;//����
int RS_x=0,RS_y=0;//����
int RX_x=0,RX_y=0;//����

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

void Clear_Buffer1(void)//��ջ���
{
		u8 i;
		for(i=0;i<Rxcouter1;i++)
		RxBuffer1[i]=0;//����
		Rxcouter1=0;
}

void Clear_Buffer2(void)//��ջ���
{
		u8 i;
		for(i=0;i<Rxcouter2;i++)
		RxBuffer2[i]=0;//����
		Rxcouter2=0;
}

void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}
void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// ����ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	// ��ʼ�� ���ڶ�ӦIO��  TX-PA2  RX-PA3
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	// ��ʼ�� ����ģʽ״̬
	USART_InitStrue.USART_BaudRate=bound; // ������
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // Ӳ��������
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // ���� ���� ģʽ��ʹ��
	USART_InitStrue.USART_Parity=USART_Parity_No; // û����żУ��
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // һλֹͣλ
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // ÿ�η������ݿ��Ϊ8λ
	USART_Init(USART2,&USART_InitStrue);
	
	USART_Cmd(USART2,ENABLE);//ʹ�ܴ���
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//���������ж�
	
	// ��ʼ�� �ж����ȼ�
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);

}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((Rxcouter1&0x8000)==0)//����δ���
			{
			if(Rxcouter1&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)Rxcouter1=0;//���մ���,���¿�ʼ
				else Rxcouter1|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)Rxcouter1|=0x4000;
				else
					{
					RxBuffer1[Rxcouter1&0X3FFF]=Res ;
					Rxcouter1++;
					if(Rxcouter1>(USART_REC_LEN-1))Rxcouter1=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
	

void USART2_IRQHandler() 
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET) //�жϲ��� 
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //����жϱ�־
    
		RxBuffer2[Rxcouter2] = USART_ReceiveData(USART2);     //���մ���1���ݵ�buff������
		Rxcouter2++; 
        
		if(RxBuffer2[5] == 'n')
		{
			colour_x=0;
			colour_y=0;
		}
		
			if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '0') || Rxcouter2 == USART_REC_LEN)    //���������0
			{
				if(RxBuffer2[0]=='('&&((RxBuffer2[1]>='0'&&RxBuffer2[1]<='9')||(RxBuffer2[1]=='-'&&(RxBuffer2[2]>='0'&&RxBuffer2[2]<='9'))))
				{
					colour_x=0;
					colour_y=0;
					for(i=2;RxBuffer2[i]>='0'&&RxBuffer2[i]<='9';i++);
					i+=1;
					if(RxBuffer2[i]==' ')
					{
						if(RxBuffer2[1]!='-')
						{
							for(j=1;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								colour_x=RxBuffer2[j]-48+colour_x*10;
							j=i+1;
						}
						else
						{
							for(j=2;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								colour_x=RxBuffer2[j]-48+colour_x*10;
							colour_x=-colour_x;
							j=i+1;
						}
						if(j==i+1)
						{
							if(RxBuffer2[j]!='-')
							{
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									colour_y=RxBuffer2[j]-48+colour_y*10;
									j++;
								}
								j=0;
							}
							else
							{
								j+=1;
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									colour_y=RxBuffer2[j]-48+colour_y*10;
									j++;
								}
								colour_y=-colour_y;
								j=0;
							}
						}
					}
					Rxcouter2=0; 
				}
				else
				{
					Rxcouter2=0;   			//����������Ҫ�����ݻ��ߴﵽ����������ʼ���½���
				}
			}
			
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '1') || Rxcouter2 == USART_REC_LEN)    //���Ͻ�����[]
			{
				if(RxBuffer2[0]=='('&&((RxBuffer2[1]>='0'&&RxBuffer2[1]<='9')||(RxBuffer2[1]=='-'&&(RxBuffer2[2]>='0'&&RxBuffer2[2]<='9'))))
				{
					LS_x=0;
					LS_y=0;
					for(i=2;RxBuffer2[i]>='0'&&RxBuffer2[i]<='9';i++);
					i+=1;
					if(RxBuffer2[i]==' ')
					{
						if(RxBuffer2[1]!='-')
						{
							for(j=1;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								LS_x=RxBuffer2[j]-48+LS_x*10;
							j=i+1;
						}
						else
						{
							for(j=2;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								LS_x=RxBuffer2[j]-48+LS_x*10;
							LS_x=-LS_x;
							j=i+1;
						}
						if(j==i+1)
						{
							if(RxBuffer2[j]!='-')
							{
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									LS_y=RxBuffer2[j]-48+LS_y*10;
									j++;
								}
								j=0;
							}
							else
							{
								j+=1;
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									LS_y=RxBuffer2[j]-48+LS_y*10;
									j++;
								}
								LS_y=-LS_y;
								j=0;
							}
						}
					}
					Rxcouter2=0; 
				}
				else
				{
					Rxcouter2=0;   			//����������Ҫ�����ݻ��ߴﵽ����������ʼ���½���
				}
			}
				
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '2') || Rxcouter2 == USART_REC_LEN)    //���Ͻ�����2
			{
				if(RxBuffer2[0]=='('&&((RxBuffer2[1]>='0'&&RxBuffer2[1]<='9')||(RxBuffer2[1]=='-'&&(RxBuffer2[2]>='0'&&RxBuffer2[2]<='9'))))
				{
					RS_x=0;
					RS_y=0;
					for(i=2;RxBuffer2[i]>='0'&&RxBuffer2[i]<='9';i++);
					i+=1;
					if(RxBuffer2[i]==' ')
					{
						if(RxBuffer2[1]!='-')
						{
							for(j=1;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								RS_x=RxBuffer2[j]-48+RS_x*10;
							j=i+1;
						}
						else
						{
							for(j=2;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								RS_x=RxBuffer2[j]-48+RS_x*10;
							RS_x=-RS_x;
							j=i+1;
						}
						if(j==i+1)
						{
							if(RxBuffer2[j]!='-')
							{
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									RS_y=RxBuffer2[j]-48+RS_y*10;
									j++;
								}
								j=0;
							}
							else
							{
								j+=1;
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									RS_y=RxBuffer2[j]-48+RS_y*10;
									j++;
								}
								RS_y=-RS_y;
								j=0;
							}
						}
					}
					Rxcouter2=0; 
				}
				else
				{
					Rxcouter2=0;   			//����������Ҫ�����ݻ��ߴﵽ����������ʼ���½���
				}
			}
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '3')  || Rxcouter2 == USART_REC_LEN)    //���½�����3
			{
				if(RxBuffer2[0]=='('&&((RxBuffer2[1]>='0'&&RxBuffer2[1]<='9')||(RxBuffer2[1]=='-'&&(RxBuffer2[2]>='0'&&RxBuffer2[2]<='9'))))
				{
					RX_x=0;
					RX_y=0;
					for(i=2;RxBuffer2[i]>='0'&&RxBuffer2[i]<='9';i++);
					i+=1;
					if(RxBuffer2[i]==' ')
					{
						if(RxBuffer2[1]!='-')
						{
							for(j=1;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								RX_x=RxBuffer2[j]-48+RX_x*10;
							j=i+1;
						}
						else
						{
							for(j=2;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
								RX_x=RxBuffer2[j]-48+RX_x*10;
							RX_x=-RX_x;
							j=i+1;
						}
						if(j==i+1)
						{
							if(RxBuffer2[j]!='-')
							{
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									RX_y=RxBuffer2[j]-48+RX_y*10;
									j++;
								}
								j=0;
							}
							else
							{
								j+=1;
								while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
								{
									RX_y=RxBuffer2[j]-48+RX_y*10;
									j++;
								}
								RX_y=-RX_y;
								j=0;
							}
						}
					}
					Rxcouter2=0; 
				}
			else
			{
				Rxcouter2=0;   			//����������Ҫ�����ݻ��ߴﵽ����������ʼ���½���
			}
		}
					
		else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '4')  || Rxcouter2 == USART_REC_LEN)    //���½�����4
		{
			if(RxBuffer2[0]=='('&&((RxBuffer2[1]>='0'&&RxBuffer2[1]<='9')||(RxBuffer2[1]=='-'&&(RxBuffer2[2]>='0'&&RxBuffer2[2]<='9'))))
			{
				LX_x=0;
				LX_y=0;
				for(i=2;RxBuffer2[i]>='0'&&RxBuffer2[i]<='9';i++);
				i+=1;
				if(RxBuffer2[i]==' ')
				{
					if(RxBuffer2[1]!='-')
					{
						for(j=1;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
							LX_x=RxBuffer2[j]-48+LX_x*10;
						j=i+1;
					}
					else
					{
						for(j=2;RxBuffer2[j]>='0'&&RxBuffer2[j]<='9';j++)
							LX_x=RxBuffer2[j]-48+LX_x*10;
						LX_x=-LX_x;
						j=i+1;
					}
					if(j==i+1)
					{
						if(RxBuffer2[j]!='-')
						{
							while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
							{
								LX_y=RxBuffer2[j]-48+LX_y*10;
								j++;
							}
							j=0;
						}
						else
						{
							j+=1;
							while(RxBuffer2[j]>='0'&&RxBuffer2[j]<='9')
							{
								LX_y=RxBuffer2[j]-48+LX_y*10;
								j++;
							}
							LX_y=-LX_y;
							j=0;
						}
					}
				}
				Rxcouter2=0; 
			}
			else
			{
				Rxcouter2=0;   			//����������Ҫ�����ݻ��ߴﵽ����������ʼ���½���
			}
		}
	}
}
//	{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
//		
//		if((Rxcouter2&0x8000)==0)//����δ���
//			{
//			if(Rxcouter2&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)Rxcouter2=0;//���մ���,���¿�ʼ
//				else Rxcouter2|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)Rxcouter2|=0x4000;
//				else
//					{
//					RxBuffer2[Rxcouter2&0X3FFF]=Res ;
//					Rxcouter2++;
//					if(Rxcouter2>(USART_REC_LEN-1))Rxcouter2=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
//} 

#endif	

