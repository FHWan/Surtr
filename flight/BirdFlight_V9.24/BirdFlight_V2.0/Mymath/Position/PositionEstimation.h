#ifndef __POSITIONESTIMATION_H
#define __POSITIONESTIMATION_H

#include "stm32f4xx.h"
#include "InertialFilter.h"
#include "IMU_AHRS.h"
#include "DronePara.h"
#include "Task.h"
#include "digital_filter.h"
#include <os.h>

extern Butter_BufferData  flow_filter_buf[3];

void KalmanFilter_Init(KalmanFilter *XAXIS,KalmanFilter *YAXIS,KalmanFilter *ZAXIS , KalmanFilter *BAROMETER);
void POS_KalmanFilter(KalmanFilter *KalmanFilter_Input,float Position,float Acceleration);
void POS_Pixhawk(float Ultrasonic,float Xvision,float Yvision,float *Accel,float Position_dt);
void OpticalFlow_Estimation(float flow_x,float flow_y,float Accx,float Accy);
#endif 

