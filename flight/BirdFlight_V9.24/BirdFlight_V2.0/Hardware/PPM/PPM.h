#ifndef __PPM_H_
#define __PPM_H_
#include "stm32f4xx.h"
#include "Task.h"
#include "explore_systick.h"
#include <string.h>
#include <stdio.h>

void TIM1_Cap_Init(u16 arr,u16 psc);
void PPM_dataDeal(void);
void Remote_Control_Mode_Init(void);

#endif

