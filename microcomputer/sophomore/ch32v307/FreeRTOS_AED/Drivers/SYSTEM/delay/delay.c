/**
 ****************************************************************************************************
 * @file        delay.c(FREERTOSר��)
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       �ṩdelay_init��ʼ�������� delay_us��delay_ms����ʱ����
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� CH32V307������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com/forum.php
 * ��˾��ַ:www.alientek.com
 * �����ַ:zhengdianyuanzi.tmall.com
 *
 * �޸�˵��
 * V1.0 20230720
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/delay/delay.h"
#include "FreeRTOS.h"
#include "task.h"


static uint16_t g_fac_us = 0;                 /* us��ʱ������ */

/**
 * @brief       ��ʼ���ӳٺ���
 * @param       sysclk: ϵͳʱ��Ƶ��, ��CPUƵ��(HCLK)
 * @retval      ��
 */
void delay_init(uint16_t sysclk)
{
    g_fac_us = sysclk;                        /* HCLK��ʱ��������Ƶ */

    NVIC_SetPriority(Software_IRQn, 0xf0);    /* ��������ж����ȼ� */
    NVIC_SetPriority(SysTicK_IRQn, 0xf0);     /* ���õδ�ʱ���ж����ȼ� */

    SysTick->CTLR= 0;                         /* ������ƼĴ������� */
    SysTick->SR  = 0;                         /* ������������־ */
    SysTick->CNT = 0;                         /* ����ֵ���� */
    SysTick->CMP = SystemCoreClock/configTICK_RATE_HZ;  /* ���ñȽ�ֵ */
    SysTick->CTLR= 0x1f;                      /* �ѿ��ƼĴ�����5λ����Ϊ1��ʹ�ܼ��������жϡ�ѡ��HCLK��ʱ����ʹ���Զ���װ�ء����¼��� */
}

/**
 * @brief       ��ʱnus
 * @param       nus: Ҫ��ʱ��us��.
 * @note        ע��: ����Ƶ144M�������,nus��ֵ��Ҫ����2^24/g_fac_us
 * @retval      ��
 */
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->CMP;           /* LOAD��ֵ */

    ticks = nus * g_fac_us;                   /* ��Ҫ�Ľ����� */
    told = SysTick->CNT;                      /* �ս���ʱ�ļ�����ֵ */

    while (1)
    {
        tnow = SysTick->CNT;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;          /* �ݼ����� */
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;                        /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            }
        }
    }
}

/**
 * @brief     ��ʱnms
 * @param     nms: Ҫ��ʱ��ms�� (0< nms <= 65535)
 * @retval    ��
 */
void delay_ms(uint16_t nms)
{
    uint32_t i;

    for (i=0; i<nms; i++)
    {
        delay_us(1000);
    }
}
