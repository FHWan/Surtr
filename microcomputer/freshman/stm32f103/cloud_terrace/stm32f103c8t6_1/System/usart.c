#include "sys.h"
#include "usart.h"	  
#include "OLED.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

void Uart1_SendStr(char*SendBuf)//串口1打印数据
{
	while(*SendBuf)
	{
	  while((USART1->SR&0X40)==0);//等待发送完成 
    USART1->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}

void Uart2_SendStr(char*SendBuf)//串口1打印数据
{
	while(*SendBuf)
	{
	  while((USART2->SR&0X40)==0);//等待发送完成 
    USART2->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

u8 RxBuffer1[200],Rxcouter1=0;
u8 RxBuffer2[200],Rxcouter2=0;
int i=0,j=0;
int colour_x=0,colour_y=0;
int LS_x=0,LS_y=0;//左上
int LX_x=0,LX_y=0;//左下
int RS_x=0,RS_y=0;//右上
int RX_x=0,RX_y=0;//右下

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  

void Clear_Buffer1(void)//清空缓存
{
		u8 i;
		for(i=0;i<Rxcouter1;i++)
		RxBuffer1[i]=0;//缓存
		Rxcouter1=0;
}

void Clear_Buffer2(void)//清空缓存
{
		u8 i;
		for(i=0;i<Rxcouter2;i++)
		RxBuffer2[i]=0;//缓存
		Rxcouter2=0;
}

void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}
void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// 外设使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	// 初始化 串口对应IO口  TX-PA2  RX-PA3
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	// 初始化 串口模式状态
	USART_InitStrue.USART_BaudRate=bound; // 波特率
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // 发送 接收 模式都使用
	USART_InitStrue.USART_Parity=USART_Parity_No; // 没有奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // 一位停止位
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // 每次发送数据宽度为8位
	USART_Init(USART2,&USART_InitStrue);
	
	USART_Cmd(USART2,ENABLE);//使能串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启接收中断
	
	// 初始化 中断优先级
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		if((Rxcouter1&0x8000)==0)//接收未完成
			{
			if(Rxcouter1&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)Rxcouter1=0;//接收错误,重新开始
				else Rxcouter1|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)Rxcouter1|=0x4000;
				else
					{
					RxBuffer1[Rxcouter1&0X3FFF]=Res ;
					Rxcouter1++;
					if(Rxcouter1>(USART_REC_LEN-1))Rxcouter1=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
	

void USART2_IRQHandler() 
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET) //中断产生 
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //清除中断标志
    
		RxBuffer2[Rxcouter2] = USART_ReceiveData(USART2);     //接收串口1数据到buff缓冲区
		Rxcouter2++; 
        
		if(RxBuffer2[5] == 'n')
		{
			colour_x=0;
			colour_y=0;
		}
		
			if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '0') || Rxcouter2 == USART_REC_LEN)    //激光笔坐标0
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
					Rxcouter2=0;   			//不是我们需要的数据或者达到最大接收数则开始重新接收
				}
			}
			
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '1') || Rxcouter2 == USART_REC_LEN)    //左上角坐标[]
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
					Rxcouter2=0;   			//不是我们需要的数据或者达到最大接收数则开始重新接收
				}
			}
				
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '2') || Rxcouter2 == USART_REC_LEN)    //右上角坐标2
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
					Rxcouter2=0;   			//不是我们需要的数据或者达到最大接收数则开始重新接收
				}
			}
			else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '3')  || Rxcouter2 == USART_REC_LEN)    //右下角坐标3
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
				Rxcouter2=0;   			//不是我们需要的数据或者达到最大接收数则开始重新接收
			}
		}
					
		else if((RxBuffer2[Rxcouter2-1] == ')' && RxBuffer2[Rxcouter2-2] == '4')  || Rxcouter2 == USART_REC_LEN)    //左下角坐标4
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
				Rxcouter2=0;   			//不是我们需要的数据或者达到最大接收数则开始重新接收
			}
		}
	}
}
//	{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		Res =USART_ReceiveData(USART2);	//读取接收到的数据
//		
//		if((Rxcouter2&0x8000)==0)//接收未完成
//			{
//			if(Rxcouter2&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)Rxcouter2=0;//接收错误,重新开始
//				else Rxcouter2|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)Rxcouter2|=0x4000;
//				else
//					{
//					RxBuffer2[Rxcouter2&0X3FFF]=Res ;
//					Rxcouter2++;
//					if(Rxcouter2>(USART_REC_LEN-1))Rxcouter2=0;//接收数据错误,重新开始接收	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
//} 

#endif	

