#include "PWM.h"

void Servo_Init(void)
{    
	TIM4_PWM_Init(100-1,16800-1);	//每1微秒记一次，一次记20000次
}

void Servo_SetAngle4(int Angle)
{
	TIM_SetTIM4Compare4( Angle );
}
