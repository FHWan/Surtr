#ifndef _ATTITUDE_CONTROL_H
#define _ATTITUDE_CONTROL_H
#include "stm32f4xx.h"
#include "DronePara.h"
#include "arm_math.h"
#include "Task.h"
#include <math.h>

void Attitude_control(float PitchCalibration,float RollCalibration);

void Calculate_Thrust(float arm_length);

void MotorThrust(float f1,float f2,float f3,float f4);

void PWM_OUTPUT(	unsigned int Motor1,
									unsigned int Motor2,
									unsigned int Motor3,
									unsigned int Motor4);
									
void Safety_Protection(void);

									
typedef struct{
	Vector3f_t ExpectWRate;
	Vector3f_t LastEstimateGyro;
	Vector3f_t LastDerivative;
	Vector3f_t Thrust;
}AttitudeControl;

									
#endif

