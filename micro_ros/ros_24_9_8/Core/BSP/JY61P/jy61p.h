#ifndef __JY61P_H
#define __JY61P_H
#include "usart.h"
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};

extern uint8_t rx_buff1;
extern float angle_x;
extern float angle_y;
extern float angle_z;

extern float acc_x;
extern float acc_y;
extern float acc_z;

extern float gyro_x;
extern float gyro_y;
extern float gyro_z;

void CopeSerial2Data(unsigned char ucData);
void sendcmd(uint8_t data[3]);
void get_data(void);

#endif
