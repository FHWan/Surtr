#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "adc.h"
#include "hc.h"
#include "rc522.h"
#include "myiic.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "ec20.h"
#include "string.h"
#include <stdio.h>
#include "timer.h"

void Pub_Msgdata(void);
u8 data_len,datastr[10],send_jason[200];
u8 i=10;

//ˮѹ
u8 wp_adc;
float Water_Pressure;
const float  OffSet = 0.483 ;

//ˮλ
float Water_Level;

//RFID
char Card_ID[9];

//mpu6050
float pitch,roll,yaw; 		//ŷ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����

//ec20��beidou
u8 lat[20]="31.90950";//??
u8 lon[20]="118.891603";//??

int main(void)
{	
	delay_init(84);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	uart2_init(115200);	 	//���ڳ�ʼ��Ϊ115200
//	LED_Init();			     //LED�˿ڳ�ʼ��		 	
	Adc_Init();					//ˮѹ
	Hcsr041Init();			//������
	RC522_Init();       //��ʼ����Ƶ��ģ��
//	EC20_Init();
//	MQTT_Init();
	while(mpu_dmp_init())
 	{
 		delay_ms(200);
	}  
  while(1){
		delay_ms(500);
		
		//J20 27 PA3
		//ˮѹ
		wp_adc = Get_Adc_Average(3,20);
		Water_Pressure = (wp_adc - OffSet) * 5;
		
		//ECHO PA1|TRIG PA0
		//������
		Water_Level = Hcsr041GetLength();
		
		//RFID
		RC522_Handel();		
		
		
		//mpu6050
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0);
		mpu_dmp_get_data(&pitch,&roll,&yaw); //����õ������ǡ�����ǡ������
		
//		//ec20��beidou
//		Read_GPS(lat,lon);
//		Pub_Msgdata();
//		while(i--)
//		{
//			Uart2Send("Water_Pressure:%f| |Water_Level:%f| |pitch:%f| |roll:%f| |yaw:%f| |Card_ID:%s| |lat:%s| |lon:%s|", Water_Pressure, Water_Level, pitch, roll, yaw, Card_ID, lat, lon);
//			delay_ms(1000);
//		}
//		i=5;

	}
}

void Pub_Msgdata(void)
{
      char *strx;
      
	 data_len=Mqtt_Savedata(send_jason,Card_ID,Water_Pressure,lon,lat,pitch,roll,yaw,Water_Level);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"fire\",%s\r\n",datastr);//????
        delay_ms(100);
	 printf("%s\r\n",send_jason);
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0
        while(strx==NULL)
        {

            strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0

        }
        delay_ms(1000);
        Clear_Buffer();
}
