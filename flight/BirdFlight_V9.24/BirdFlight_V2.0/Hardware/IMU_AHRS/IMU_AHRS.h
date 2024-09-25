#ifndef __IMU_AHRS_H
#define __IMU_AHRS_H

extern volatile float Acc_x;
extern volatile float Acc_y;
extern volatile float Acc_z;
void IMU_HardwareInit(void);
void IMU_getInfo(void);



extern volatile float RDrone_R[3][3];
extern float Accel_Pixhawk[3];

#endif


