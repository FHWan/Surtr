#include "PWM.h"

void Servo_Init(void)
{    
	TIM4_PWM_Init(100-1,16800-1);	//ÿ1΢���һ�Σ�һ�μ�20000��
}

void Servo_SetAngle4(int Angle)
{
	TIM_SetTIM4Compare4( Angle );
}
