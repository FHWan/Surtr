/**
 ****************************************************************************************************
 * @file        delay.c(FREERTOS专用)
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       提供delay_init初始化函数， delay_us和delay_ms等延时函数
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 CH32V307开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com/forum.php
 * 公司网址:www.alientek.com
 * 购买地址:zhengdianyuanzi.tmall.com
 *
 * 修改说明
 * V1.0 20230720
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/delay/delay.h"
#include "FreeRTOS.h"
#include "task.h"


static uint16_t g_fac_us = 0;                 /* us延时倍乘数 */

/**
 * @brief       初始化延迟函数
 * @param       sysclk: 系统时钟频率, 即CPU频率(HCLK)
 * @retval      无
 */
void delay_init(uint16_t sysclk)
{
    g_fac_us = sysclk;                        /* HCLK做时基，不分频 */

    NVIC_SetPriority(Software_IRQn, 0xf0);    /* 设置软件中断优先级 */
    NVIC_SetPriority(SysTicK_IRQn, 0xf0);     /* 设置滴答定时器中断优先级 */

    SysTick->CTLR= 0;                         /* 清除控制寄存器配置 */
    SysTick->SR  = 0;                         /* 清除计数溢出标志 */
    SysTick->CNT = 0;                         /* 计数值清零 */
    SysTick->CMP = SystemCoreClock/configTICK_RATE_HZ;  /* 设置比较值 */
    SysTick->CTLR= 0x1f;                      /* 把控制寄存器低5位设置为1，使能计数器、中断、选择HCLK做时基、使能自动重装载、向下计数 */
}

/**
 * @brief       延时nus
 * @param       nus: 要延时的us数.
 * @note        注意: 在主频144M的情况下,nus的值不要大于2^24/g_fac_us
 * @retval      无
 */
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->CMP;           /* LOAD的值 */

    ticks = nus * g_fac_us;                   /* 需要的节拍数 */
    told = SysTick->CNT;                      /* 刚进入时的计数器值 */

    while (1)
    {
        tnow = SysTick->CNT;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;          /* 递减计数 */
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;                        /* 时间超过/等于要延迟的时间,则退出 */
            }
        }
    }
}

/**
 * @brief     延时nms
 * @param     nms: 要延时的ms数 (0< nms <= 65535)
 * @retval    无
 */
void delay_ms(uint16_t nms)
{
    uint32_t i;

    for (i=0; i<nms; i++)
    {
        delay_us(1000);
    }
}
