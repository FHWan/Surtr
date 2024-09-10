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
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7); /* ����ʱ��,168Mhz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    uart_init(9600);             	//��ʼ��USART1		������	�����Ʒ�������� TX RX GND (SET)
	uart2_init(115200);             //��ʼ��USART2		EC20
	uart4_init(115200);				//��ʼ��UART4		����ʶ��
	EC20_Init(); 					// EC20��ʼ��
	MQTT_Init();
	KEY_Init();						//��ʼ��������GND		PC1
	while(mpu_dmp_init())			//��ʼ��MPU6050			SDA PD9	  SCL PD10
	{
		delay_ms(100);	
	}		
	MY_ADC_Init();                  //��ʼ��ADC1ͨ��10,��ǿ PC0
	BEEP_MY();						//��ʼ��������			PD11
	LED_MY();						//��ʼ���ƴ�			PD0���� PD1���
	Servo_Init();					//��ʼ�����			PB9
//	Servo_SetAngle4(89);			//��
	Servo_SetAngle4(95);			//�ر�
    uc_os2_demo();                      /* ����uC/OS-II���� */
}


void BEEP_MY(void)		//��������ʼ��
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_11; //PD11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);	//PD11��1 
}

void LED_MY(void)		//LED��ʼ��
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0 | GPIO_PIN_1; //PD0 PD1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 | GPIO_PIN_1,GPIO_PIN_RESET);	//PD0 PD1��1 
}
