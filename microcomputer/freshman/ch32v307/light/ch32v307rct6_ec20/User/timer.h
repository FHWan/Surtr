/*
 * timer.h
 *
 *  Created on: 2022Äê6ÔÂ12ÈÕ
 *      Author: hett
 */

#ifndef USER_TIMER_H_
#define USER_TIMER_H_

#include "ch32v30x_conf.h"

void Input_Capture_Init( u16 arr, u16 psc );
void ENABLE_TIM(void);
void DISABLE_TIM(void);
u32 GetCount(void);
float Ultrasoniclength(void);

#endif /* USER_TIMER_H_ */
