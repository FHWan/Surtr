#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ec20.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "PWM.h"
#include "servor.h"
#include "adc.h"
#include "key.h"
#include "uc-os2_demo.h"

void BEEP_MY(void);
void LED_MY(void);

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7); /* 设置时钟,168Mhz */
    delay_init(168);                    /* 延时初始化 */
    uart_init(9600);             	//初始化USART1		电量计	电量计反面从左到右 TX RX GND (SET)
	uart2_init(115200);             //初始化USART2		EC20
	uart4_init(115200);				//初始化UART4		人脸识别
	EC20_Init(); 					// EC20初始化
	MQTT_Init();
	KEY_Init();						//初始化按键连GND		PC1
	while(mpu_dmp_init())			//初始化MPU6050			SDA PD9	  SCL PD10
	{
		delay_ms(100);	
	}		
	MY_ADC_Init();                  //初始化ADC1通道10,光强 PC0
	BEEP_MY();						//初始化蜂鸣器			PD11
	LED_MY();						//初始化灯带			PD0蓝光 PD1红光
	Servo_Init();					//初始化舵机			PB9
//	Servo_SetAngle4(89);			//打开
	Servo_SetAngle4(95);			//关闭
    uc_os2_demo();                      /* 运行uC/OS-II例程 */
}


void BEEP_MY(void)		//蜂鸣器初始化
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOD时钟
	
    GPIO_Initure.Pin=GPIO_PIN_11; //PD11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);	//PD11置1 
}

void LED_MY(void)		//LED初始化
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOD时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0 | GPIO_PIN_1; //PD0 PD1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 | GPIO_PIN_1,GPIO_PIN_RESET);	//PD0 PD1置1 
}
