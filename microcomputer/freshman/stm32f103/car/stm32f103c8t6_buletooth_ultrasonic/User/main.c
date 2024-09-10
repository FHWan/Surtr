#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "string.h"
#include "usart.h"	
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "PWM.h"
#include "hc.h"
#include "Timer.h"

///////
//1 2//
//   //
///////
void Find(void);
void Blue(void);
void Clear_Buffer1(void);
void HC(void);

uint8_t KeyNum;
int8_t Speed=60;
uint8_t RxData,t=0;
int hc;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	Timer_Init();
	HC_SR04_Init();
//	OLED_Init();
//	Motor_Init();
//	Key_Init();
//	BEEP_Init();
//	OLED_ShowString(1, 1, "RxData:");
//	OLED_ShowString(3, 1, "hc:");
	
	while (1)
	{
//		Uart1_SendStr("good\r\n");
//		OLED_ShowString(3, 8, RxBuffer1);
//		Clear_Buffer1();
//		Delay_ms(3000);
//		Find();
//		Blue();
		HC();
	}
}

void Find(void)/*循迹*/
{
	if(L1==1&&L2==1&&R2==1&&R1==1)
	{
		Motor_Forward(67);
		OLED_ShowString(1, 8, "Forward");
	}
	
	if((L1==0||L2==0)&&(R2==1||R1==1))
	{
		OLED_ShowString(1, 8, "Left   ");Uart1_SendStr("Left\r\n");
		while(!(L1==1&&L2==1&&M==0&&R2==1&&R1==1))
		{
			Motor_Left(67,67);
			if((L1==0||L2==0)&&(R2==0||R1==0))
			{
				Motor_Stop();
				OLED_ShowString(1, 8, "Stop   ");
				Uart1_SendStr("Stop\r\n");
			}
		}
			
	}
			
	if((L1==1||L2==1)&&(R2==0||R1==0))
	{
		OLED_ShowString(1, 8, "Right   ");Uart1_SendStr("Right\r\n");
		while(!(L1==1&&L2==1&&M==0&&R2==1&&R1==1))
		{
			Motor_Right(67,67);
			if((L1==0||L2==0)&&(R2==0||R1==0))
			{
				Motor_Stop();
				OLED_ShowString(1, 8, "Stop   ");
				Uart1_SendStr("Stop\r\n");
			}
		}
	}
	
	if((L1==0||L2==0)&&(R2==0||R1==0))
	{
		Motor_Stop();
		OLED_ShowString(1, 8, "Stop   ");
		Uart1_SendStr("Stop\r\n");
	}
		 
}


void Blue(void)/*蓝牙*/
{	
	OLED_ShowString(3, 1, "RxData:");
	OLED_ShowString(3, 8, RxBuffer1);
	printf("good\r\n");
//	if(t==100)
//	{
//		OLED_ShowString(3, 1, "RxData:       ");
//		t=0;
//	}t++;
	Clear_Buffer1();
}
	
void Clear_Buffer1(void)//清空缓存
{
		u8 i;
		for(i=0;i<Rxcouter1;i++)
		RxBuffer1[i]=0;//缓存
		Rxcouter1=0;
}

void HC(void)/*超声波*/
{
//	do
//	{
		hc = sonar_mm();
//		OLED_ShowNum(3, 4, hc, 4);
//	if(hc<=100&&hc>=20)
//	{	
//		OLED_ShowString(1, 8, "return");
//		Motor_Forward(0);
//		Delay_ms(1500);
//	}
//	}while(hc<=150&&hc>0);
}

