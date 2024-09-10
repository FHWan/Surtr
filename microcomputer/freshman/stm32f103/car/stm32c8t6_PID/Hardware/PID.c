/*
	PID算法用来控制运动变化	
*/
#include "stm32f10x.h"                  // Device header
float Err=0,Er_1=0,Er_2=0,PWM=0,add=0,P=3.5,I=0.4,D=0,Limit=99;//所用电机最高速度为100

float pid1(int16_t speed,float tar)//利用PID控制速度
{
	if(speed<0)
		speed=-speed;
    int Err=tar-speed;
    add=P*(Err-Er_1)+I*(Err)+D*(Err+Er_2-2*Er_1);
    PWM+=add;
	if(PWM > Limit)
		PWM=Limit;
	if(PWM<0)
		PWM=0;
    Er_2=Er_1;
    Er_1=Err;
    return PWM;
}


