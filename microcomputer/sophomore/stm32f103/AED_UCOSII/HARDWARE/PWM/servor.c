#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	TIM2_PWM_Init(200-1,7200-1);//20000-1,72-1
}

void Servo_SetAngle(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}

