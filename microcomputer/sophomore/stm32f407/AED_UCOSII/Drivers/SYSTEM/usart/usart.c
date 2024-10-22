
#include "usart.h"
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "os.h"					//os 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/9/7
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 	  
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
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

void Uart1_SendStr(char*SendBuf)//串口1打印数据(这个无法发送0x00)
{
	while(*SendBuf)
	{
	  while((USART1->SR&0X40)==0);//等待发送完成 
    USART1->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}

void Uart1_Send00(char*SendBuf)//串口1打印数据(这个用来发送0x00，只发一个)
{
	  while((USART1->SR&0X40)==0);//等待发送完成 
    USART1->DR = (u8) *SendBuf; 
}

void Uart4_SendStr(char*SendBuf)//串口1打印数据(这个无法发送0x00)
{
	while(*SendBuf)
	{
	  while((UART4->SR&0X40)==0);//等待发送完成 
    UART4->DR = (u8) *SendBuf; 
		SendBuf++;
	}
}

#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

u8 RxBuffer1[200],Rxcouter1=0;
u8 RxBuffer2[200],Rxcouter2=0;
u8 RxBuffer4[200],Rxcouter4=0;

u8 aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲
UART_HandleTypeDef UART1_Handler; //UART句柄
UART_HandleTypeDef UART2_Handler; //UART2句柄
UART_HandleTypeDef UART4_Handler; //UART4句柄

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	
	//HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量(使用回调函数处理中断需要调用该函数）
  
}
void uart2_init(u32 bound)
{
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    //USART1
	UART2_Handler.Init.BaudRate=bound;				    //波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()会使能UART2
}

void uart4_init(u32 bound)
{	
	//UART 初始化设置
	UART4_Handler.Instance=UART4;					    //USART1
	UART4_Handler.Init.BaudRate=bound;				    //波特率
	UART4_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART4_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART4_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART4_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART4_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART4_Handler);					    //HAL_UART_Init()会使能UART1

}

//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		__HAL_UART_DISABLE_IT(huart,UART_IT_TC);
#if EN_USART1_RX
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//抢占优先级3，子优先级3
#endif	
	}
	else if(huart->Instance==USART2)//如果是串口2，进行串口2 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART2;	//复用为USART2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA3
		__HAL_UART_DISABLE_IT(huart,UART_IT_TC);
#if EN_USART1_RX
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
#endif	
	}
	else if(huart->Instance==UART4)//如果是串口4，进行串口4 MSP初始化
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();			//使能GPIOC时钟
		__HAL_RCC_UART4_CLK_ENABLE();			//使能USART4时钟
	
		GPIO_Initure.Pin=GPIO_PIN_10;			//PC10
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF8_UART4;	//复用为USART4
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   	//初始化PC10

		GPIO_Initure.Pin=GPIO_PIN_11;			//PC11
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   	//初始化PC11
		__HAL_UART_DISABLE_IT(huart,UART_IT_TC);
#if EN_USART1_RX
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(UART4_IRQn);				//使能USART4中断通道
		HAL_NVIC_SetPriority(UART4_IRQn,3,3);			//抢占优先级3，子优先级3
#endif	
	}

}


 


//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 
	
	u8 Res;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
        HAL_UART_Receive(&UART1_Handler,&Res,1,1000); 
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
	HAL_UART_IRQHandler(&UART1_Handler);	
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 
//串口2中断服务程序
void USART2_IRQHandler(void)                	
{ 
	
	u8 Res;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
        HAL_UART_Receive(&UART2_Handler,&Res,1,1000); 
		if((Rxcouter2&0x8000)==0)//接收未完成
		{
			if(Rxcouter2&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)Rxcouter2=0;//接收错误,重新开始
				else Rxcouter2|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)Rxcouter2|=0x4000;
				else
				{
					RxBuffer2[Rxcouter2&0X3FFF]=Res ;
					Rxcouter2++;
					if(Rxcouter2>(USART_REC_LEN-1))Rxcouter2=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	}
	HAL_UART_IRQHandler(&UART2_Handler);	
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 

//串口4中断服务程序
void UART4_IRQHandler(void)                	
{ 
	
	u8 Res;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	if((__HAL_UART_GET_FLAG(&UART4_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
        HAL_UART_Receive(&UART4_Handler,&Res,1,1000); 
		if((Rxcouter4&0x8000)==0)//接收未完成
		{
			if(Rxcouter4&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)Rxcouter4=0;//接收错误,重新开始
				else Rxcouter4|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)Rxcouter4|=0x4000;
				else
				{
					RxBuffer4[Rxcouter4&0X3FFF]=Res ;
					Rxcouter4++;
					if(Rxcouter4>(USART_REC_LEN-1))Rxcouter4=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	}
	HAL_UART_IRQHandler(&UART4_Handler);	
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 

void Clear_Buffer(u8 x)//清空缓存
{
    u8 i;
    if(x==1)
    {
        for(i=0;i<Rxcouter1;i++)
            RxBuffer1[i]=0;//缓存
            Rxcouter1=0;
    }
    if(x==2)
    {
        for(i=0;i<Rxcouter2;i++)
            RxBuffer2[i]=0;//缓存
            Rxcouter2=0;
    }
	if(x==4)
    {
        for(i=0;i<Rxcouter4;i++)
            RxBuffer4[i]=0;//缓存
            Rxcouter4=0;
    }

}


#endif	




