#ifndef __FLOW_DEAL_H
#define __FLOW_DEAL_H

#include "stm32f4xx.h"
#include "Task.h"
#include "DronePara.h"
#include "arm_math.h"


#define LPF_1_(hz,t,in,out) ((out) += ( 1 / ( 1 + 1 / ( (hz) *3.14f *(t) ) ) ) *( (in) - (out) ))

void Flow_datadeal(_Data_Rx rx);


#endif 

