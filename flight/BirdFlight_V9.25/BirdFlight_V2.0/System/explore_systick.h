#ifndef __EXPLORE_SYSTICK_H_
#define __EXPLORE_SYSTICK_H_

#include "stm32f4xx.h"
#include "explore_system.h"

void Systick_Init(u8 SYSCLK);						// 初始化延时函数
void delay_us(u32 nus);							// 延时nus微秒
void delay_ms(u16 nms);							// 延时nms毫秒
void delay_xms(u16 nms);						// 延时nms毫秒

#endif /* __EXPLORE_SYSTICK_H_ */
