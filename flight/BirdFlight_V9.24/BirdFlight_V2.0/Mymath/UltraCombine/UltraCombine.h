#ifndef __ULTRACOMBINE_H
#define __ULTRACOMBINE_H

#include "stm32f4xx.h"
#include "InertialFilter.h"
#include "IMU_AHRS.h"
#include "DronePara.h"
#include "Task.h"
#include "Timer5_Timing.h"
#include <os.h>

#define CONSTANTS_ONE_G					9.80665f		/* m/s^2*/

void Altitude_Ultrasonic(float Ultra,float *accel);

#endif 

