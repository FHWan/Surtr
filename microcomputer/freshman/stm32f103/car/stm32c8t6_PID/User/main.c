#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "string.h"
#include "usart.h"	
#include "OLED.h"
#include "Motor.h"
#include "PWM.h"
#include "Encoder.h"
#include "PID.h"

///////
//1 2//
//   //
///////
void Clear_Buffer1(void);

int speed1,speed2,time1=0,tar1,tar2;
uint16_t pwm1,pwm2;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	OLED_Init();
	Motor_Init();
	PWM_Init();
	light_Init();
	Encoder1_Init();
	Encoder2_Init();
	while (1)
	{
		Motor1_SetSpeed(100);
			Motor2_SetSpeed(70);
		//OLED_ShowString(1,1,"OK");
//		printf("OK\r\n");
//		if(R2==1&&L2==1)
//		{
//			tar1=30;
//			tar2=30;
//		}
//		
//		if(R2==1&&L2==0)					//С��ת
//		{	
//			tar1=20;
//			tar2=30;
//			while(!(M==0&&R2==1&&L2==1))	//û��������һֱת
//			{
//				if(L1==0)					//����ת
//				{
//					tar1=-15;
//					tar2=30;
//				}
//				if(R2==0)
//				{
//					tar1=30;
//					tar2=20;
//				}
//				if(R1==0)
//				{
//					tar1=30;
//					tar2=-15;
//				}
//			}
//		}
//			
//		if(L1==0)					//����ת
//		{
//			tar1=-15;
//			tar2=30;
//			Delay_ms(100);
//			while(!(M==0&&R2==1&&L2==1))	//û��������һֱת
//			{
//				if(R2==0)
//				{
//					tar1=30;
//					tar2=20;
//				}
//				
//			}
//		}
//		
//		if(L2==1&&R2==0)		//С��ת
//		{
//			tar1=30;
//			tar2=20;
//			while(!(M==0&&L2==1&&R2==1))	//һֱת
//			{
//				if(R1==0)					//����ת
//				{
//					tar1=30;
//					tar2=-15;
//				}
//				if(L2==0)
//				{
//					tar1=20;
//					tar2=30;
//				}
//				if(L1==0)
//				{
//					tar1=-15;
//					tar2=30;
//				}
//			}
//		}
//		
//		if(R1==0)					//����ת
//		{
//			tar1=30;
//			tar2=-15;
//			Delay_ms(100);
//			while(!(M==0&&L2==1&&R2==1))	//һֱת
//			{
//				if(L2==0)
//				{
//					tar1=20;
//					tar2=30;
//				}
//			}
//		}
//////		if((L1==0||L2==0)&&(R2==0||R1==0))	//ͣ��
//////		{
//////			Motor_Stop();
//////		}
	}
}
	
void Clear_Buffer1(void)//��ջ���
{
		u8 i;
		for(i=0;i<Rxcouter1;i++)
		RxBuffer1[i]=0;//����
		Rxcouter1=0;
}


void TIM2_IRQHandler(void)//���ö�ʱ��ÿ��1ms���һ���ٶ�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		time1++;
		if(time1==5)
		{
			Get_Motor_Speed(&speed1,&speed2);
			speed1=0.1*speed1;
			speed2=0.1*speed2;
			OLED_ShowNum(1,1,speed1,4);
////			pwm1=pid1(speed1,tar1);//����ߵ������PID����
////			pwm2=pid1(speed2,tar2);//���ұߵ������PID����
//			Motor1_SetSpeed(pwm1);
//			Motor2_SetSpeed(pwm2);
			
			time1=0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

