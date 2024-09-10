#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle1(float Angle)
{
	if(Angle>=90)	Angle=90;
	if(Angle<=-90)	Angle=-90;
	PWM_SetCompare1( (Angle+135) / 270 * 2000 + 500);
}

void Servo_SetAngle2(float Angle)
{
	Angle=-Angle;
	if(Angle>=45)	Angle=45;
	if(Angle<=-45)	Angle=-45;
	PWM_SetCompare2( (Angle+135) / 270 * 2000 + 500);
}
