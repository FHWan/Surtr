#ifndef __EXTENSIONALKALMANFILTER_H
#define __EXTENSIONALKALMANFILTER_H

#include "stm32f4xx.h"
#include "MathTool.h"



void EKF_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float *q); 
#endif
