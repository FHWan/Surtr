#ifndef INERTIALFILTER_H
#define INERTIALFILTER_H
#include "stm32f4xx.h"

void inertial_filter_predict(float dt, float x[2], float acc);
void inertial_filter_correct(float e, float dt, float x[2], int i, float w);

#endif 

