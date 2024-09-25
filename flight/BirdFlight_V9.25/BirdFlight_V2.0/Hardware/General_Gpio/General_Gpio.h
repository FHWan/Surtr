#ifndef __GENERAL_GPIO_H
#define __GENERAL_GPIO_H

#include "stm32f4xx.h"
#include "explore_systick.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "task.h"

void EXTIX_Init(void);
void LED_Init(void);

#endif 
