#include "explore_usart.h"

/**
 * USART_RX_STA: 软件虚拟的寄存器,用于控制字节流的接收
 * USART_RX_STA[15]: 接收完成标志
 * USART_RX_STA[14]: 接收到0x0d
 * USART_RX_STA[13:0]: 接收到的有效字节数目
 */
u16 USART_RX_STA = 0;							// 接收状态标记

u8 USART_RX_BUF[USART_REC_LEN];						// 接收缓冲,最大USART_REC_LEN个字节.

/**
 * @Description 串口1中断服务函数,每有接收一个字节,申请一次中断,中断函数里面接收,直到接收到换行停止接收
 */
void USART1_IRQHandler(void)
{
	u8 Res;								// 用于保存本次串口接收到的字节
	OSIntEnter();
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		// 判断是不是接受中断,如果是接受中断,执行if里面的代码
	{
		Res = USART_ReceiveData(USART1);			// 读取串口1接收到的数据
		if((USART_RX_STA & 0x8000) == 0)			// 接收未完成,这里接收的是一大串字节
		{
			if(USART_RX_STA & 0x4000)			// 判断前一个接收的是不是0x0d
			{
				if(Res != 0x0a)				// 在前一个接收到时0x0d的基础上,如果在接受的不是到0x0a
				{
					USART_RX_STA = 0;		// 接收错误,重新开始
				}
				else					// 在前一个接收到时0x0d的基础上,如果再接收到0x0a
				{
					USART_RX_STA |= 0x8000;		// 就把USART_RX_STA中接收完成标志置位,表示接收完成了
				}
			}
			else						// 如果前一个字节还没收到0x0d的话,就接着接收下一个字节
			{	
				if(Res == 0x0d)				// 如果当前接收到的是0x0d的话
				{
					USART_RX_STA |= 0x4000;		// 则置位接收到0x0d的标志位 USART_RX_STA[14]
				}
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF] = Res;	// 将当前接收到的值存入缓存数组中
					USART_RX_STA++;					// 接收到的字节个数加一
					if(USART_RX_STA > (USART_REC_LEN-1))		// 判断接收到的数据有没有超过最开始设置的缓存区长度
					{
						USART_RX_STA = 0;	// 如果超出范围,表明接收数据错误,重新开始接收
					}
				}
			}
		}
	}
	OSIntExit();
}

/**
 * @Description 初始化I/O串口1 
 * @param bound 波特率
 * @return null 无返回值
 */
 void Usart_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;				// 创建一个GPIO初始化结构体
	USART_InitTypeDef USART_InitStructure;				// 创建一个串口初始化结构体
	NVIC_InitTypeDef NVIC_InitStructure;				// 创建一个中断初始化结构体

	// 第一步:使能外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		// 使能USART1时钟

	// 第二步:设置串口1对应的GPIO复用映射
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);	// GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	// GPIOA10复用为USART1

	// 第四步:配置串口1对应的GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;		// GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			// 复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			// 推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			// 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);				// 初始化PA9，PA10

	// 第五步:USART1初始化设置
	USART_InitStructure.USART_BaudRate = bound;			// 波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;		// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
	USART_Init(USART1, &USART_InitStructure);			// 初始化串口1
	USART_Cmd(USART1, ENABLE);					// 使能串口1

	// 第六步:配置串口1中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			// 开启相关中断
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		// 串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	// 抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		// 亚优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);					// 根据指定的参数初始化NVIC寄存器
}

// 加入以下代码,支持printf函数,而不需要选择use MicroLIB
#pragma import(__use_no_semihosting)

// 标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;

/**
 * @Description 定义_sys_exit()以避免使用半主机模式
 */
int _sys_exit(int x)
{
	return x = x;
}

/**
 * @Description 重定义fputc函数
 */
int fputc(int ch, FILE *f)
{
	while((USART1->SR&0X40)==0);					// 循环发送,直到发送完毕
	USART1->DR = (u8) ch;
	return ch;
}
