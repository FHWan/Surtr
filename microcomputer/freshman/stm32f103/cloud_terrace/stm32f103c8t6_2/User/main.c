#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "string.h"
#include "usart.h"	
#include "OLED.h"
#include "PWM.h"
#include "PID.h"
#include "servor.h"
#include "Key.h"
#include "math.h"

#define N	4		//积分数量
#define YU 	2.5
#define YU2 9
#define YU3 9
#define DE  44

void bianyuan	(void);	//1、2题
void xunji		(void);	//3题
void xunji2		(void);	//4题
void controlMY	(void);
///////////////////////////////
float XXX=0,YYY=5;		//可编辑——原始
float OXX=13,OYY=18;	//1题
///////////////////////////////
int 	time=0,T=0,MODE=0;			//遇到边角次数
double 	X=0,Y=5;			
float 	SX=0.5,SY=0.5;		//(直)每次走的角度
float 	GX=1,GY=1;		//(弯)每次走的角度
float 	OX=0,OY=5;			//固定位置，写死
float 	OOX=0,OOY=5;			
float 	dX,dY;				//x,y的微分
uint8_t KeyNum = 0,KEY = 0;
int 	BILI;				
int 	PX=0,PY=0;			//x,y的偏差值
int		point=0;			
float	lenth,leng;				//长度

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	uart2_init(9600);
	Key_Init();
	Key_Init2();
	OLED_Init();
	Servo_Init();
	OLED_ShowString(1,1,"OX");
	OLED_ShowString(2,1,"OY");
	OLED_ShowString(3,1,"OXX");
	OLED_ShowString(4,1,"OYY");
	OLED_ShowString(1,12,"MODE");
	OLED_ShowSignedNum(1,7,OX,3);
	OLED_ShowSignedNum(2,7,OY,3);
	OLED_ShowSignedNum(3,7,OXX,3);
	OLED_ShowSignedNum(4,7,OYY,3);
	OLED_ShowNum(2,12,MODE,1);
	Servo_SetAngle1(OX);	//回中心 (0,14)
	Servo_SetAngle2(OY);
	while (1)
	{
		if(KEY==1)				//沿边缘,第2题
		{
			bianyuan();
		}
		if(KEY==2)				//循迹，第3、4题
		{
			xunji();
		}
		if(KEY==3)				//循迹，第3、4题
		{
			xunji2();
		}
		if(KEY>=4)				//复位加编辑，第3、4题
		{
			controlMY();
			OLED_ShowSignedNum(1,7,OX,3);
			OLED_ShowSignedNum(2,7,OY,3);
			OLED_ShowSignedNum(3,7,OXX,3);
			OLED_ShowSignedNum(4,7,OYY,3);
			OLED_ShowNum(2,12,MODE,1);
		}
		if(KEY<4)
			MODE=0;
	}
}

void bianyuan(void)
{
	OOX=OX;
	OOY=OY;
	Servo_SetAngle1(OXX);
	Servo_SetAngle2(OYY);
	Delay_ms(500);
	Servo_SetAngle1(-OXX);
	Servo_SetAngle2(OYY);
	Delay_ms(500);
	Servo_SetAngle1(-OXX+1);
	Servo_SetAngle2(2*OY-OYY);
	Delay_ms(500);
	Servo_SetAngle1(OXX+2);
	Servo_SetAngle2(2*OY-OYY);
	Delay_ms(500);
	Servo_SetAngle1(OXX);
	Servo_SetAngle2(OYY);
	Delay_ms(500); 
	Servo_SetAngle1(OX);	//回中心 (0,14)
	Servo_SetAngle2(OY);
	KEY=0;
}

void xunji(void)	
{
	if(BILI==0)
	{
		X=OX;
		Y=OY;
		BILI=1;
	}
	if(time==0)			//左上
	{
		PX=colour_x-LS_x+3;
	}
	if(time==1)				//右上
	{
		PX=colour_x-RX_x-12;
	}
	if(time==2)				//右下
	{
		PY=colour_y-RX_y-6;
	}
	if(time==3)				//左下
	{
		PX=colour_x-LS_x+6;
	}
	if(time==4)				//左下
	{
		PY=colour_y-LS_y+4;
	}
	if(PX >=  80) 		X-=2;
	else if(PX >=  YU)  X-=SX;
	if(PX <= -80)  		X+=2;
	else if(PX <= -YU)  X+=SX;
	if(PY >=  50) 		Y-=1;
	else if(PY >=  YU)  Y-=SY;
	if(PY <= -50)  		Y+=1;
	else if(PY <= -YU)  Y+=SY;
	if(X>= 90)	X =  90;
	if(X<=-90)	X = -90;
	if(Y<=-45)	Y = -45;
	if(Y>= 45)	Y =  45;
	Delay_ms(100);
	if((PX<YU&&PX>-YU)&&(PY<YU&&PY>-YU))
	{
		time++;
		if(time>=5)
		{
			time=0;
			KEY=0;
			BILI=0;
			Servo_SetAngle1(OX);	//回中心 (0,14)
			Servo_SetAngle2(OY);
		}
	}
}

void xunji2		(void)
{
	if(time==0)			//左上
	{
		PX=colour_x-LS_x+1;
		PY=colour_y-LS_y+1;
		if(PX >=  80) 		X-=2;
		else if(PX >=  4)  X-=GX;
		if(PX <= -80)  		X+=2;
		else if(PX <= -4)  X+=GX;
		if(PY >=  50) 		Y+=1;
		else if(PY >=  4)  Y+=GY;
		if(PY <= -50)  		Y-=1;
		else if(PY <= -4)  Y-=GY;
		Delay_ms(50);
		if((PX<4&&PX>-4)&&(PY<4&&PY>-4))
		{
			time++;
			if(time>=5)
			{
				time=1;
			}
		}
	}
	if(time==1)
	{
		dX=(RS_x-LS_x)/N;
		dY=(RS_y-LS_y)/N;
		do
		{
			if(((PX<YU2)&&(PX>-YU2)&&(PY<YU2)&&(PY>-YU2)))
				point++;
			PX=colour_x-(LS_x+point*dX);
			PY=colour_y-(LS_y+point*dY);
			if(PX >=  YU3)  X-=GX;
			if(PX <= -YU3)  X+=GX;
			if(PY >=  YU3)  Y+=GY;
			if(PY <= -YU3)  Y-=GY;
			Delay_ms(DE);
		}while(point<N);
		time++;
	}
	if(time==2)
	{
		point=0;
		dX=(RX_x-RS_x)/N;
		dY=(RX_y-RS_y)/N;
		do
		{
			if(((PX<YU2)&&(PX>-YU2)&&(PY<YU2)&&(PY>-YU2)))
				point++;
			PX=colour_x-(RS_x+point*dX);
			PY=colour_y-(RS_y+point*dY);
			if(PX >=  YU3)  X-=GX;
			if(PX <= -YU3)  X+=GX;
			if(PY >=  YU3)  Y+=GY;
			if(PY <= -YU3)  Y-=GY;
			Delay_ms(DE);
		}while(point<N);
		time++;
	}
	if(time==3)
	{
		point=0;
		dX=(LX_x-RX_x)/N;
		dY=(LX_y-RX_y)/N;
		do
		{
			if(((PX<YU2)&&(PX>-YU2)&&(PY<YU2)&&(PY>-YU2)))
				point++;
			PX=colour_x-(RX_x+point*dX);
			PY=colour_y-(RX_y+point*dY);
			if(PX >=  YU3)  X-=GX;
			if(PX <= -YU3)  X+=GX;
			if(PY >=  YU3)  Y+=GY;
			if(PY <= -YU3)  Y-=GY;
			Delay_ms(DE);
		}while(point<N);
		time++;
	}
	if(time==4)
	{
		point=0;
		dX=(LS_x-LX_x)/N;
		dY=(LS_y-LX_y)/N;
		do
		{
			if(((PX<YU2)&&(PX>-YU2)&&(PY<YU2)&&(PY>-YU2)))
				point++;
			PX=colour_x-(LX_x+point*dX);
			PY=colour_y-(LX_y+point*dY);
			if(PX >=  YU3)  X-=GX;
			if(PX <= -YU3)  X+=GX;
			if(PY >=  YU3)  Y+=GY;
			if(PY <= -YU3)  Y-=GY;
			Delay_ms(DE);
		}while(point<N+1);
		time++;
	}
		if(time>=5)
		{
			time=0;
			KEY=0;
			Servo_SetAngle1(OX);	//回中心 (0,14)
			Servo_SetAngle2(OY);
		}
}
void controlMY (void)
{
	if(KEY==5)
	{
		KEY=4;
		MODE++;
	}
	if(MODE>=3)
		MODE=0;
	if(MODE==0)
	{
		XXX=OX;
		YYY=OY;
	}
	
	if(MODE==1)//初始位置
	{
		if(KEY==6)
		{
			KEY=4;
			YYY++;
		}
		if(KEY==7)
		{
			KEY=4;
			XXX--;
		}
		if(KEY==8)
		{
			KEY=4;
			YYY--;
		}
		if(KEY==9)
		{
			KEY=4;
			XXX++;
		}
		OX=XXX;
		OY=YYY;
	}
	if(MODE==2)//四边位置
	{
		XXX=OXX;
		YYY=OYY;
		if(KEY==6)
		{
			KEY=4;
			YYY++;
		}
		if(KEY==7)
		{
			KEY=4;
			XXX--;
		}
		if(KEY==8)
		{
			KEY=4;
			YYY--;
		}
		if(KEY==9)
		{
			KEY=4;
			XXX++;
		}
		OXX=XXX;
		OYY=YYY;
	}
	
}
void TIM2_IRQHandler(void)//利用定时器每隔1ms检测一次速度
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{	
		KeyNum = Key_GetNum();	//获取按键
		if(KeyNum!=0)
		{
			KEY=KeyNum;
		}
		if(KEY==2)
		{
			Servo_SetAngle1(X);  //x,左为负，右为正
			Servo_SetAngle2(Y);  //y
		}
		if(KEY==3)
		{
			PWM_SetCompare1(X+1500);  //x,左为负，右为正
			PWM_SetCompare2(Y+1500);  //y
		}
		if(KEY>=4)
		{
			Servo_SetAngle1(XXX);  //x,左为负，右为正
			Servo_SetAngle2(YYY);  //y
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}