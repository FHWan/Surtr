#ifndef __LQR_CONTROL_H
#define __LQR_CONTROL_H

#include "stm32f4xx.h"
#include "Task.h"

void LQR_Init(LQR *WxBodyRate,LQR *WyBodyRate,LQR *WzBodyRate);
void MotorThrust(float f1,float f2,float f3,float f4);
void MotorThrustCallback(float Accelerator1,float Accelerator2,float Accelerator3,float Accelerator4,float arm_length,float rotor_drag_coeff);
void BodyRateControl(LQR *LQR_InputWx,LQR *LQR_InputWy,LQR *LQR_InputWz,float WxExpect,
				float WxEstimate,float WyExpect,float WyEstimate,float WzExpect,float WzEstimate);

void ThrustMixer(float arm_length);

#endif
