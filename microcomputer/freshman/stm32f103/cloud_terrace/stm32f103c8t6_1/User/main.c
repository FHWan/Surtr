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

#define N	4		//��������
#define YU 	2.5
#define YU2 9
#define YU3 9
#define DE  44

void bianyuan	(void);	//1��2��
void xunji		(void);	//3��
void xunji2		(void);	//4��
void controlMY	(void);
///////////////////////////////
float XXX=0,YYY=5;		//�ɱ༭����ԭʼ
float OXX=13,OYY=18;	//1��
///////////////////////////////
int 	time=0,T=0,MODE=0;			//�����߽Ǵ���
double 	X=0,Y=5;			
float 	SX=0.5,SY=0.5;		//(ֱ)ÿ���ߵĽǶ�
float 	GX=1,GY=1;		//(��)ÿ���ߵĽǶ�
float 	OX=0,OY=5;			//�̶�λ�ã�д��
float 	OOX=0,OOY=5;			
float 	dX,dY;				//x,y��΢��
uint8_t KeyNum = 0,KEY = 0;
int 	BILI;				
int 	PX=0,PY=0;			//x,y��ƫ��ֵ
int		point=0;			
float	lenth,leng;				//����

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
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
	Servo_SetAngle1(OX);	//������ (0,14)
	Servo_SetAngle2(OY);
	while (1)
	{
		if(KEY==1)				//�ر�Ե,��2��
		{
			bianyuan();
		}
		if(KEY==2)				//ѭ������3��4��
		{
			xunji();
		}
		if(KEY==3)				//ѭ������3��4��
		{
			xunji2();
		}
		if(KEY>=4)				//��λ�ӱ༭����3��4��
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
	Servo_SetAngle1(OX);	//������ (0,14)
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
	if(time==0)			//����
	{
		PX=colour_x-LS_x+3;
	}
	if(time==1)				//����
	{
		PX=colour_x-RX_x-12;
	}
	if(time==2)				//����
	{
		PY=colour_y-RX_y-6;
	}
	if(time==3)				//����
	{
		PX=colour_x-LS_x+6;
	}
	if(time==4)				//����
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
			Servo_SetAngle1(OX);	//������ (0,14)
			Servo_SetAngle2(OY);
		}
	}
}

void xunji2		(void)
{
	if(time==0)			//����
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
			Servo_SetAngle1(OX);	//������ (0,14)
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
	
	if(MODE==1)//��ʼλ��
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
	if(MODE==2)//�ı�λ��
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
void TIM2_IRQHandler(void)//���ö�ʱ��ÿ��1ms���һ���ٶ�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{	
		KeyNum = Key_GetNum();	//��ȡ����
		if(KeyNum!=0)
		{
			KEY=KeyNum;
		}
		if(KEY==2)
		{
			Servo_SetAngle1(X);  //x,��Ϊ������Ϊ��
			Servo_SetAngle2(Y);  //y
		}
		if(KEY==3)
		{
			PWM_SetCompare1(X+1500);  //x,��Ϊ������Ϊ��
			PWM_SetCompare2(Y+1500);  //y
		}
		if(KEY>=4)
		{
			Servo_SetAngle1(XXX);  //x,��Ϊ������Ϊ��
			Servo_SetAngle2(YYY);  //y
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}