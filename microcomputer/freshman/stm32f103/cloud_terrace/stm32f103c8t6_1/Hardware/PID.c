#include "stm32f10x.h"                 
#include "pid.h"

int16_t myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

float pwm_control(float pwm)
{
    if(pwm>99)
        pwm=99;
    else if(pwm<-99)
        pwm=-99;
    return pwm;
}

float limit(float now,float tar)
{
    if(now>tar)
        now=tar;
    if(now<-tar)
        now=-tar;
    return now;
}

/*****************************************************************************************************/
//增量式pid速度控制

float i_Err=0,i_last_err=0,i_next_err=0,i_pwm=0,i_add=0,i_p=3.5,i_i=1.2,i_d=0;//80speed

float i_pid(int16_t now_speed,float tar_speed)
{
    now_speed=myabs(now_speed);
    i_Err=tar_speed-now_speed;
	  if(i_Err<5)
			i_i=0.1;
		else
			i_i=0.1;
    i_add=i_p*(i_Err-i_last_err)+i_i*(i_Err)+i_d*(i_Err+i_next_err-2*i_last_err);
    i_pwm+=i_add;
    i_pwm=pwm_control(i_pwm);
    i_next_err=i_last_err;
    i_last_err=i_Err;
    return i_pwm;
}

/***********************************************************************************************************/
//位置式pid位置控制

float p_Err=0,p_last_err=0,Integral=0,p_pwm=0,p_p=1,p_i=0,p_d=0.5;

float p_pid(int16_t now_position,float tar_position)
{
    now_position=myabs(now_position);
    p_Err=tar_position-now_position;
    if(myabs(p_Err)<5)
        p_p=0.01;
    else 
        p_p=1;
    p_pwm=p_p*p_Err+p_i*Integral+p_d*(p_Err-p_last_err);
    p_pwm=pwm_control(p_pwm);
    p_last_err=p_Err;
    return p_pwm;
}





