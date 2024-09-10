/**
 ****************************************************************************************************
 * @file        usart.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       ���ڳ�ʼ������(һ���Ǵ���1)��֧��printf
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� CH32V307������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20230720
 * ��һ�η���
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
 * @brief       ����X��ʼ������
 * @param       ��
 * @retval      ��
 */
void usart_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* ʹ�ܴ���TX��ʱ�� */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* ʹ�ܴ���RX��ʱ�� */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); }while(0);/* ʹ�ܴ���ʱ�� */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_9;           /* ���ڷ������ź� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* ����������� */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO�ٶ�����Ϊ50M */
    GPIO_Init(GPIOA, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_10;           /* ����RX�� ģʽ���� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* �������� */
    GPIO_Init(GPIOA, &gpio_init_struct);        /* ����RX��,���ó�����ģʽ */

    /* USART��ʼ������*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* ������ */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* �ֳ�Ϊ8λ���ݸ�ʽ */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* һ��ֹͣλ */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* ����żУ��λ */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* ��Ӳ������ */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* �շ�ģʽ */
    USART_Init(USART1,&uartx_init_struct);                                        /* ��ʼ������ */

    nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;        /* ʹ��USART�ж�ͨ�� */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* ��ռ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* ��Ӧ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQͨ��ʹ��  */
    NVIC_Init(&nvic_init_struct);                            /* ��ʼ��NVIC  */

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         /* �������ڽ����ж� */
    USART_Cmd(USART1, ENABLE);                             /* ʹ�ܴ��� */
}
/**
 * @brief       ����X�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART1_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  /* ����Ǵ���1 */
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);     /* ����жϱ�־ */
        Res =USART_ReceiveData(USART1);                    /* ��ȡ���յ������� */

        if ((Rxcouter1 & 0x8000) == 0)                  /* ����δ��� */
        {
            if (Rxcouter1 & 0x4000)                     /* ���յ���0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter1 = 0;                      /* ���մ���,���¿�ʼ */
                }
                else
                {
                    Rxcouter1 |= 0x8000;                /* ��������� */
                }
            }
            else                                             /* ��û�յ�0X0D */
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
                        Rxcouter1 = 0;                  /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
    }
}

/**
 * @brief       ����X��ʼ������
 * @param       ��
 * @retval      ��
 */
void usart2_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* ʹ�ܴ���TX��ʱ�� */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); }while(0);/* ʹ�ܴ���RX��ʱ�� */
    do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); }while(0);/* ʹ�ܴ���ʱ�� */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_2;           /* ���ڷ������ź� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* ����������� */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO�ٶ�����Ϊ50M */
    GPIO_Init(GPIOA, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_3;           /* ����RX�� ģʽ���� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* �������� */
    GPIO_Init(GPIOA, &gpio_init_struct);        /* ����RX��,���ó�����ģʽ */

    /* USART��ʼ������*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* ������ */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* �ֳ�Ϊ8λ���ݸ�ʽ */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* һ��ֹͣλ */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* ����żУ��λ */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* ��Ӳ������ */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* �շ�ģʽ */
    USART_Init(USART2,&uartx_init_struct);                                        /* ��ʼ������ */

    nvic_init_struct.NVIC_IRQChannel = USART2_IRQn;        /* ʹ��USART�ж�ͨ�� */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* ��ռ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* ��Ӧ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQͨ��ʹ��  */
    NVIC_Init(&nvic_init_struct);                            /* ��ʼ��NVIC  */

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         /* �������ڽ����ж� */
    USART_Cmd(USART2, ENABLE);                             /* ʹ�ܴ��� */
}

/**
 * @brief       ����X�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART2_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  /* ����Ǵ���1 */
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);     /* ����жϱ�־ */
        Res =USART_ReceiveData(USART2);                    /* ��ȡ���յ������� */

        if ((Rxcouter2 & 0x8000) == 0)                  /* ����δ��� */
        {
            if (Rxcouter2 & 0x4000)                     /* ���յ���0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter2 = 0;                      /* ���մ���,���¿�ʼ */
                }
                else
                {
                    Rxcouter2 |= 0x8000;                /* ��������� */
                }
            }
            else                                             /* ��û�յ�0X0D */
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
                        Rxcouter2 = 0;                  /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
    }
}
/**
 * @brief       ����X��ʼ������
 * @param       ��
 * @retval      ��
 */
void usart3_init(uint32_t bound)
{
    GPIO_InitTypeDef  gpio_init_struct;
    USART_InitTypeDef uartx_init_struct;
    NVIC_InitTypeDef  nvic_init_struct;

    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); }while(0);/* ʹ�ܴ���TX��ʱ�� */
    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); }while(0);/* ʹ�ܴ���RX��ʱ�� */
    do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); }while(0);/* ʹ�ܴ���ʱ�� */

    gpio_init_struct.GPIO_Pin = GPIO_Pin_10;           /* ���ڷ������ź� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;            /* ����������� */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;          /* IO�ٶ�����Ϊ50M */
    GPIO_Init(GPIOB, &gpio_init_struct);

    gpio_init_struct.GPIO_Pin = GPIO_Pin_11;           /* ����RX�� ģʽ���� */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      /* �������� */
    GPIO_Init(GPIOB, &gpio_init_struct);        /* ����RX��,���ó�����ģʽ */

    /* USART��ʼ������*/
    uartx_init_struct.USART_BaudRate = bound;                                       /* ������ */
    uartx_init_struct.USART_WordLength = USART_WordLength_8b;                       /* �ֳ�Ϊ8λ���ݸ�ʽ */
    uartx_init_struct.USART_StopBits = USART_StopBits_1;                            /* һ��ֹͣλ */
    uartx_init_struct.USART_Parity = USART_Parity_No;                               /* ����żУ��λ */
    uartx_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   /* ��Ӳ������ */
    uartx_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                   /* �շ�ģʽ */
    USART_Init(USART3,&uartx_init_struct);                                        /* ��ʼ������ */

    nvic_init_struct.NVIC_IRQChannel = USART3_IRQn;        /* ʹ��USART�ж�ͨ�� */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority=0 ;   /* ��ռ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0;         /* ��Ӧ���ȼ�3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;            /* IRQͨ��ʹ��  */
    NVIC_Init(&nvic_init_struct);                            /* ��ʼ��NVIC  */

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         /* �������ڽ����ж� */
    USART_Cmd(USART3, ENABLE);                             /* ʹ�ܴ��� */
}

/**
 * @brief       ����X�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART3_IRQHandler(void)
{
    uint8_t Res;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  /* ����Ǵ���1 */
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);     /* ����жϱ�־ */
        Res =USART_ReceiveData(USART3);                    /* ��ȡ���յ������� */

        if ((Rxcouter3 & 0x8000) == 0)                  /* ����δ��� */
        {
            if (Rxcouter3 & 0x4000)                     /* ���յ���0x0d */
            {
                if (Res != 0x0a)
                {
                    Rxcouter3 = 0;                      /* ���մ���,���¿�ʼ */
                }
                else
                {
                    Rxcouter3 |= 0x8000;                /* ��������� */
                }
            }
            else                                             /* ��û�յ�0X0D */
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
                        Rxcouter3 = 0;                  /* �������ݴ���,���¿�ʼ���� */
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
void Uart1_Send00(char*SendBuf)//����1��ӡ����(�����������0x00��ֻ��һ��)
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

void Clear_Buffer(uint32_t x)//��ջ���
{
    u8 i;
    if(x==1)
    {
        for(i=0;i<Rxcouter1;i++)
            RxBuffer1[i]=0;//����
            Rxcouter1=0;
    }
    if(x==2)
    {
        for(i=0;i<Rxcouter2;i++)
            RxBuffer2[i]=0;//����
            Rxcouter2=0;
    }
    if(x==3)
    {
        for(i=0;i<Rxcouter3;i++)
            RxBuffer3[i]=0;//����
            Rxcouter3=0;
    }

}

/**
 * @brief       _write����
 * @param       *buf : Ҫ���͵�����,size: Ҫ���͵����ݳ���
 * @retval      size : ���ݳ���
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

