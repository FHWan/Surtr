#ifndef __PID_CONTROL_H
#define __PID_CONTROL_H

#include "stm32f4xx.h"
#include "Task.h"
#include <stdio.h>
#include <math.h>
#include "DronePara.h"

#define lowpass_filter       7.9577e-3f

float PID_Control(PID *PIDpara, PIDOut *PIDstatus, float expect_PID, float feedback_PID, float PIDtime,float Integrallimiter);
float LPF_PID_Control(PID *PIDpara, PIDOut *PIDstatus, float expect_PID, float feedback_PID, float PIDtime, float Integrallimiter, float LPFParameter);

#endif

