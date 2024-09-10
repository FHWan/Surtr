#include "sys.h" 	
#include "delay.h"	
#include "string.h"
#include "adc.h"
#include "math.h"
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "EC20.h"
#include "PWM.h"
#include "servor.h"
#include "key.h"
#include "ucosll-use.h"

void BEEP_MY(void);
void LED_MY(void);

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	uart_init(115200);								//设置串口波特率为115200 TX-PA9	 RX-PA10	usb口，树莓派
	uart2_init(9600);								//设置串口波特率为9600 	TX-PA2连黑线	 RX-PA3连白线	电量计反面从左到右 TX RX GND (SET)	
													//别用这个搞EC20，不知道为啥EC20传来的信息会变成乱码
	uart3_init(115200);								//设置串口波特率为115200 TX-PB10	 RX-PB11	EC20
	EC20_Init(); 					// EC20初始化
	MQTT_Init();
	KEY_Init();						//初始化按键连GND		PA8
	MPU_Init();						//初始化MPU6050			SDA PC7	  SCL PC2
	while(mpu_dmp_init())			
	{
		delay_ms(100);	
	}		
	MY_ADC_Init();                  //初始化ADC1通道5,光强	PA5
	BEEP_MY();						//初始化蜂鸣器			PB7
	LED_MY();						//初始化灯带				PA11白光 PA12红光
	Servo_Init();					//初始化舵机				PA1
//	Servo_SetAngle(21);			//打开
	Servo_SetAngle(10);			//关闭

	ucosll_init();
}
	  
void LED_MY(void)		//LED初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置PA11 PA12引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
}


void BEEP_MY(void)			//蜂鸣器初始化
{
	 GPIO_InitTypeDef GPIO_InitStructure;

	// 使能GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// 配置PB7引脚为输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//高速
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}






