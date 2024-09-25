#ifndef __SIMPLEDIGITALFILTERING_H
#define __SIMPLEDIGITALFILTERING_H

#include "stm32f4xx.h"

float Average_Filter(float FilterData,uint16_t Length,float *FilterArray);

float Median_Filter(int FilterData,uint16_t Length,int *FilterArray);

#endif 

