#ifndef __VISIONDATA_DEAL_H
#define __VISIONDATA_DEAL_H

#include "stm32f4xx.h"
#include "DronePara.h"
#include "Task.h"
#include "SimpleDigitalFiltering.h"
#include "arm_math.h"

//图像160*120 中心点坐标
#define ImageCenter_x    0.8f
#define ImageCenter_y    0.6f

void Vision_datadeal(_Data_Rx rx);
#endif


