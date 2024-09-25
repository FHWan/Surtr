#ifndef __CALIBRATE_H
#define __CALIBRATE_H

#include "stm32f4xx.h"
#include <math.h>
#include "Task.h"

#define GRAVITY_MSS     9.7946f    //上海当地重力加速度  不同省市需修改

/* 6面校准采样数据 */
typedef struct
{
 float x;
 float y;
 float z;
}Acce_Unit;

bool Calibrate_accel(Acce_Unit accel_sample[6],
                      Acce_Unit *accel_offsets,
                      Acce_Unit *accel_scale);

#endif 
