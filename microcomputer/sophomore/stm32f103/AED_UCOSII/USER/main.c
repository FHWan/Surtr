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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200);								//���ô��ڲ�����Ϊ115200 TX-PA9	 RX-PA10	usb�ڣ���ݮ��
	uart2_init(9600);								//���ô��ڲ�����Ϊ9600 	TX-PA2������	 RX-PA3������	�����Ʒ�������� TX RX GND (SET)	
													//���������EC20����֪��ΪɶEC20��������Ϣ��������
	uart3_init(115200);								//���ô��ڲ�����Ϊ115200 TX-PB10	 RX-PB11	EC20
	EC20_Init(); 					// EC20��ʼ��
	MQTT_Init();
	KEY_Init();						//��ʼ��������GND		PA8
	MPU_Init();						//��ʼ��MPU6050			SDA PC7	  SCL PC2
	while(mpu_dmp_init())			
	{
		delay_ms(100);	
	}		
	MY_ADC_Init();                  //��ʼ��ADC1ͨ��5,��ǿ	PA5
	BEEP_MY();						//��ʼ��������			PB7
	LED_MY();						//��ʼ���ƴ�				PA11�׹� PA12���
	Servo_Init();					//��ʼ�����				PA1
//	Servo_SetAngle(21);			//��
	Servo_SetAngle(10);			//�ر�

	ucosll_init();
}
	  
void LED_MY(void)		//LED��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ��GPIOA��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // ����PA11 PA12����Ϊ���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
}


void BEEP_MY(void)			//��������ʼ��
{
	 GPIO_InitTypeDef GPIO_InitStructure;

	// ʹ��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// ����PB7����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}






