/*
 * timer.h
 *
 *  Created on: 2023Äê7ÔÂ16ÈÕ
 *      Author: 30411
 */
#include <msp430.h>

#ifndef __PID_H
#define __PID_H

extern volatile int time;
extern volatile int encoderCount;
extern volatile int encoderCount2;
extern volatile float speedleft;
extern volatile float speedright;

void TimerA0_Capture(void);
void TimerA1_Capture(void);
float pid(float speed,int tar);

#endif /* TIMER_TIMER_H_ */
