#ifndef _ENCODER_H
#define _ENCODER_H

void Encoder1_Init(void);
void Encoder2_Init(void);
int16_t Encoder1_Get(void);
int16_t Encoder2_Get(void);
s16 getTIMx_DetaCnt(TIM_TypeDef * TIMx);
void Get_Motor_Speed(int *leftSpeed,int *rightSpeed);

#endif
