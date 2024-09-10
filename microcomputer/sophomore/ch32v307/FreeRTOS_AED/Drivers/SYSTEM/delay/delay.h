/**
 ****************************************************************************************************
 * @file        delay.h(FREERTOSר��)
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

#ifndef __DELAY_H
#define __DELAY_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/

void delay_init(uint16_t sysclk);   /* ��ʼ���ӳٺ��� */
void delay_ms(uint16_t nms);        /* ��ʱnms */
void delay_us(uint32_t nus);        /* ��ʱnus */

#endif


