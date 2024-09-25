#ifndef _POSITION_CONTROL_H_
#define _POSITION_CONTROL_H_
#include "stm32f4xx.h"
#include "Task.h"
#include "DronePara.h"
#include "PID_control.h"
#include "Limits.h"

#define kAlmostZeroValueThreshold   0.001f

void Position_control(unsigned char Data_flag,float Climb,float Decline);
void ComputeDesiredAttitude(Vector3f_t DesiredAcceleration,float reference_heading);

#endif


