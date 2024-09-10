#ifndef __PID_H
#define __PID_H

float i_pid(int16_t now_speed,float tar_speed);
float p_pid(int16_t now_position,float tar_position);
float limit(float now,float tar);
int16_t myabs(int a);
    
#endif
