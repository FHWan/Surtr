#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "adc.h"
#include "rc522.h"
#include "ec20.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "mpu6050.h"
#include "string.h"
#include <stdio.h>
#include "timer.h"
#include "hc.h"

void Pub_Msgdata(void);
u8 data_len,datastr[10],send_jason[200];


const float  OffSet = 0.483 ;
float v_pressure;
float Water_Pressure;
char Card_ID[9]="936219C5";
float pitch,roll,yaw; 		//欧拉角
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
float Water_Level;
u8 lat[20]="31.90950";//??
u8 lon[20]="118.891603";//??
u8 i=10;
int main(void)
 {	 
    
	float temp;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	uart2_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化		 	
 	Adc_Init();		  		//ADC初始化
	RC522_Init();       //初始化射频卡模块
	EC20_Init();
	MQTT_Init();
	Hcsr041Init();
	MPU_Init();					//初始化MPU6050
	while(mpu_dmp_init())
 	{
 		delay_ms(200);
	}  
	while(1)
	{
		v_pressure =Get_Adc_Average(ADC_Channel_10,10) * 5.00 / 1024; 
		Water_Pressure = (v_pressure - OffSet) * 250;  //单位kap
		RC522_Handel();
		Water_Level = Hcsr041GetLength();
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) { }
		mpu_dmp_get_data(&pitch,&roll,&yaw); //计算得到俯仰角、横滚角、航向角		
		delay_ms(250);	
		
		Read_GPS(lat,lon);
		Pub_Msgdata();
		while(i--)
		{
			Uart2Send("Water_Pressure:%f| |Water_Level:%f| |pitch:%f| |roll:%f| |yaw:%f| |Card_ID:%s| |lat:%s| |lon:%s|", Water_Pressure, Water_Level, pitch, roll, yaw, Card_ID, lat, lon);
			delay_ms(1000);
		}
		i=5;
	}
 }

void Pub_Msgdata(void)
{
      char *strx;
      
				//data_len=Mqtt_Savedata(send_jason,water_level,lon,lat,AIR_Quality0,AIR_Quality1,temperature, humidity, tumble);
	 data_len=Mqtt_Savedata(send_jason,Card_ID,Water_Pressure,lon,lat,pitch,roll,yaw,Water_Level);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"fire\",%s\r\n",datastr);//????
        delay_ms(100);
	 printf("%s\r\n",send_jason);
        //Uart2_SendStr(send_jason);
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0
        while(strx==NULL)
        {

            strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0

        }
        delay_ms(1000);
        Clear_Buffer();
}

