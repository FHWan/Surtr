#ifndef __ADRC_CONTROL_H
#define __ADRC_CONTROL_H

#include "stm32f4xx.h"
#include "Task.h"
#include <stdio.h>
#include <math.h>
#include "DronePara.h"

float ADRC_Control(ADRC *ADRC_INPUT,float expect_ADRC,float feedback_ADRC);
void ADRC_Init(ADRC *PITCH_PARA,ADRC *ROLL_PARA,ADRC *YAW_PARA);



#endif 


