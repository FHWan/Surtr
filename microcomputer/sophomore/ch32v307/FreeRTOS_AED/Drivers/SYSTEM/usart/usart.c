/**
 ****************************************************************************************************
 * @file        usart.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       串口初始化代码(一般是串口1)，支持printf
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 CH32V307开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20230720
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/usart/usart.h"

u8 RxBuffer1[200],Rxcouter1 = 0;
u8 RxBuffer2[200],Rxcouter2 = 0;
u8 RxBuffer3[200],Rxcouter3 = 0;

void USART1_IRQHandler(void) __attribute__((interrupt()));
void USART2_IRQHandler(void) __attribute__((interrupt()));
void USART3_IRQHandler(void) __attribute__((interrupt()));

//void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/**
 * @brief       串口X初始化函数
 * @param       无
 * @retval      无
 */
void usart_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* 使能串口TX脚时钟 */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* 使能串口RX脚时钟 */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); }while(0);/* 使能串口时钟 */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_9;           /* 串口发送引脚号 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* 复用推挽输出 */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO速度设置为50M */
    GPIO_Init(GPIOA, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_10;           /* 串口RX脚 模式设置 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* 浮空输入 */
    GPIO_Init(GPIOA, &gpio_init_struct);        /* 串口RX脚,设置成输入模式 */

    /* USART初始化设置*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* 波特率 */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* 字长为8位数据格式 */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* 一个停止位 */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* 无奇偶校验位 */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* 无硬件流控 */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* 收发模式 */
    USART_Init(USART1,&uartx_init_struct);                                        /* 初始化串口 */

    nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;        /* 使能USART中断通道 */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* 抢占优先级3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* 响应优先级3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQ通道使能  */
    NVIC_Init(&nvic_init_struct);                            /* 初始化NVIC  */

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         /* 开启串口接受中断 */
    USART_Cmd(USART1, ENABLE);                             /* 使能串口 */
}
/**
 * @brief       串口X中断服务函数
 * @param       无
 * @retval      无
 */
void USART1_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  /* 如果是串口1 */
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);     /* 清除中断标志 */
        Res =USART_ReceiveData(USART1);                    /* 读取接收到的数据 */

        if ((Rxcouter1 & 0x8000) == 0)                  /* 接收未完成 */
        {
            if (Rxcouter1 & 0x4000)                     /* 接收到了0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter1 = 0;                      /* 接收错误,重新开始 */
                }
                else
                {
                    Rxcouter1 |= 0x8000;                /* 接收完成了 */
                }
            }
            else                                             /* 还没收到0X0D */
            {
                if (Res == 0x0d)
                {
                    Rxcouter1 |= 0x4000;
                }
                else
                {
                    RxBuffer1[Rxcouter1++] = Res;
//                    Rxcouter1++;

                    if (Rxcouter1 > (USART_REC_LEN - 1))
                    {
                        Rxcouter1 = 0;                  /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
    }
}

/**
 * @brief       串口X初始化函数
 * @param       无
 * @retval      无
 */
void usart2_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* 使能串口TX脚时钟 */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* 使能串口RX脚时钟 */
    do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); }while(0);/* 使能串口时钟 */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_2;           /* 串口发送引脚号 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* 复用推挽输出 */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO速度设置为50M */
    GPIO_Init(GPIOA, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_3;           /* 串口RX脚 模式设置 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* 浮空输入 */
    GPIO_Init(GPIOA, &gpio_init_struct);        /* 串口RX脚,设置成输入模式 */

    /* USART初始化设置*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* 波特率 */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* 字长为8位数据格式 */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* 一个停止位 */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* 无奇偶校验位 */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* 无硬件流控 */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* 收发模式 */
    USART_Init(USART2,&uartx_init_struct);                                        /* 初始化串口 */

    nvic_init_struct.NVIC_IRQChannel = USART2_IRQn;        /* 使能USART中断通道 */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* 抢占优先级3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* 响应优先级3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQ通道使能  */
    NVIC_Init(&nvic_init_struct);                            /* 初始化NVIC  */

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         /* 开启串口接受中断 */
    USART_Cmd(USART2, ENABLE);                             /* 使能串口 */
}

/**
 * @brief       串口X中断服务函数
 * @param       无
 * @retval      无
 */
void USART2_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  /* 如果是串口1 */
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);     /* 清除中断标志 */
        Res =USART_ReceiveData(USART2);                    /* 读取接收到的数据 */

        if ((Rxcouter2 & 0x8000) == 0)                  /* 接收未完成 */
        {
            if (Rxcouter2 & 0x4000)                     /* 接收到了0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter2 = 0;                      /* 接收错误,重新开始 */
                }
                else
                {
                    Rxcouter2 |= 0x8000;                /* 接收完成了 */
                }
            }
            else                                             /* 还没收到0X0D */
            {
                if (Res == 0x0d)
                {
                    Rxcouter2 |= 0x4000;
                }
                else
                {
                    RxBuffer2[Rxcouter2++] = Res;
                    //Rxcouter2++;

                    if (Rxcouter2 > (USART_REC_LEN - 1))
                    {
                        Rxcouter2 = 0;                  /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
    }
}
/**
 * @brief       串口X初始化函数
 * @param       无
 * @retval      无
 */
void usart3_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); }while(0);/* 使能串口TX脚时钟 */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); }while(0);/* 使能串口RX脚时钟 */
    do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); }while(0);/* 使能串口时钟 */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_10;           /* 串口发送引脚号 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* 复用推挽输出 */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO速度设置为50M */
    GPIO_Init(GPIOB, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_11;           /* 串口RX脚 模式设置 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* 浮空输入 */
    GPIO_Init(GPIOB, &gpio_init_struct);        /* 串口RX脚,设置成输入模式 */

    /* USART初始化设置*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* 波特率 */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* 字长为8位数据格式 */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* 一个停止位 */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* 无奇偶校验位 */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* 无硬件流控 */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* 收发模式 */
    USART_Init(USART3,&uartx_init_struct);                                        /* 初始化串口 */

    nvic_init_struct.NVIC_IRQChannel = USART3_IRQn;        /* 使能USART中断通道 */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* 抢占优先级3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* 响应优先级3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQ通道使能  */
    NVIC_Init(&nvic_init_struct);                            /* 初始化NVIC  */

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         /* 开启串口接受中断 */
    USART_Cmd(USART3, ENABLE);                             /* 使能串口 */
}

/**
 * @brief       串口X中断服务函数
 * @param       无
 * @retval      无
 */
void USART3_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  /* 如果是串口1 */
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);     /* 清除中断标志 */
        Res =USART_ReceiveData(USART3);                    /* 读取接收到的数据 */

        if ((Rxcouter3 & 0x8000) == 0)                  /* 接收未完成 */
        {
            if (Rxcouter3 & 0x4000)                     /* 接收到了0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter3 = 0;                      /* 接收错误,重新开始 */
                }
                else
                {
                    Rxcouter3 |= 0x8000;                /* 接收完成了 */
                }
            }
            else                                             /* 还没收到0X0D */
            {
                if (Res == 0x0d)
                {
                    Rxcouter3 |= 0x4000;
                }
                else
                {
                    RxBuffer3[Rxcouter3++] = Res;
//                    Rxcouter3++;

                    if (Rxcouter3 > (USART_REC_LEN - 1))
                    {
                        Rxcouter3 = 0;                  /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
    }
}

void Uart1_SendStr(char*SendBuf)
{
    while(*SendBuf)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, *SendBuf);
        SendBuf++;
    }
}
void Uart1_Send00(char*SendBuf)//串口1打印数据(这个用来发送0x00，只发一个)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    USART_SendData(USART1, *SendBuf);
}

void Uart2_SendStr(char*SendBuf)
{
    while(*SendBuf)
    {
      while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
      USART_SendData(USART2, *SendBuf);
      SendBuf++;
    }
}

void Uart3_SendStr(char*SendBuf)
{
    while(*SendBuf)
    {
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
        USART_SendData(USART3, *SendBuf);
        SendBuf++;
    }
}

void Clear_Buffer(uint32_t x)//清空缓存
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
    if(x==3)
    {
        for(i=0;i<Rxcouter3;i++)
            RxBuffer3[i]=0;//缓存
            Rxcouter3=0;
    }

}

/**
 * @brief       _write函数
 * @param       *buf : 要发送的数据,size: 要发送的数据长度
 * @retval      size : 数据长度
 */
int _write(int fd, char *buf, int size)
{
    int i;

    for(i=0; i<size; i++)
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, *buf++);
    }
    return size;
}

