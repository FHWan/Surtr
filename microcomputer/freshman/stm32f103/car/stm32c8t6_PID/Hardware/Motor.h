#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor_Forward		(int8_t Speed);
void Motor_Right		(int8_t Speed1,int8_t Speed2);
void Motor_Left 		(int8_t Speed1,int8_t Speed2);
void Motor_Stop 		(void);
void Motor1_SetSpeed	(int8_t Speed);
void Motor2_SetSpeed	(int8_t Speed);

#endif
