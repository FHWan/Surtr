#ifndef __NEURONS_C
#define __NEURONS_C

#include "stm32f4xx.h"
#include "arm_math.h"
#include "Limits.h"
#include "math.h"

void Neurons_pidinit(void);
float Neurons_PID_Hight(float Errdata);
float Neurons_PID_Postionx(float Errdatax);
float Neurons_PID_Postiony(float Errdatay);
float Abs_Funcation(float pSrc);
#endif

