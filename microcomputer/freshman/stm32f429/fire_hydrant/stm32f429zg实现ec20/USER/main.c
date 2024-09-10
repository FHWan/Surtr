#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "adc.h"
#include "rc522.h"
#include "ec20.h"
#include "math.h"
#include "lcd.h"
#include "HC.h"
#include "timer.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

void Pub_Msgdata(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
u8 lat[20]="31.6789801";//??
u8 lon[20]="119.9522227";//??
float LAT,LATT,LON,LONN;
u8 data_len,datastr[10],send_jason[200];

char Card_ID[9];
char *stry;

int t,i,ci,ka,card;
u8 temperature,humidity;
float db_temp,adcx;
float LAT,LATT,LON,LONN;
const float  OffSet = 0.483 ;
float v_pressure;
float Water_Pressure;
float pitch,roll,yaw; 		//欧拉角
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
float WaterLevel;
uint16_t Adc_buffer[4]; // ADC采集数据缓存

int main(void)
{
	int i=0;
    HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(9600);
	uart2_init(115200);				//初始化USART
	
	MY_ADC_Init();                  //初始化ADC1通道5
/////////////////////////////////////////////////////////////////////////////	
	LCD_Init();		//初始化LCD 
	POINT_COLOR=RED; 
	LCD_Clear(WHITE);
/////////////////////////////////////////////////////////////////////////////	
	LCD_ShowString(10,130,240,32,32,"EC20........");
//	EC20_Init();            //初始化ec20
//	MQTT_Init();
	TIM2_Init(5000-1,9000-1);       //定时器3初始化，定时器时钟为90M，分频系数为90000-1，
                                    //所以定时器3的频率为90M/90000=1K，自动重装载为5000-1，那么定时器周期就是5s
	LCD_Clear(WHITE);
/////////////////////////////////////////////////////////////////////////////	
	BEEP_MY();			 			//初始化蜂鸣器
	RC522_Init();  					//RC522打卡初始化
	ultrasound_init();				//超声波初始化
/////////////////////////////////////////////////////////////////////////////	
	LCD_ShowString(10,130,240,32,32,"MPU6050.....");
	while(mpu_dmp_init())			//初始化MPU6050(必须水平放置)
	{
		delay_ms(100);	
	}			
	LCD_Clear(WHITE);
/////////////////////////////////////////////////////////////////////////////	
	LCD_ShowString(10,0,240,32,32,"Hydrant");
    POINT_COLOR=BLUE; 
//	LCD_ShowString(10, 40,240,24,24,"Lon       :");
//	LCD_ShowString(10, 70,240,24,24,"Lat       :");
	LCD_ShowString(10,100,240,24,24,"Pressure  :");
	LCD_ShowString(10,130,240,24,24,"Pitch     :");
	LCD_ShowString(10,160,240,24,24,"Roll      :");
	LCD_ShowString(10,190,240,24,24,"Yaw       :");
	LCD_ShowString(10,220,240,24,24,"HC        :");
	POINT_COLOR=BLACK; 
    
    while(1)
	{
/////////////////////////////////////////////////////////////////////////////
		
		/*MPU6050*/
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
		mpu_dmp_get_data(&pitch,&roll,&yaw); //计算得到俯仰角、横滚角、航向角
		if(((pitch>10)||(pitch<-10))||((roll>10)||(roll<-10)))
		{
			LCD_ShowString(150,0,240,24,24,"Warning");
			for(ka=0;ka<100;ka++)
			{
				BEEP=0;
				delay_ms(1);
				BEEP=1;
				delay_ms(1);
			}
		}
		else
		{
			LCD_ShowString(150,0,240,24,24,"       ");
			
		}
		
///////////////////////////////////////////////////////////////////////////////
		
		/*RC522*/
		RC522_Handel();
		
/////////////////////////////////////////////////////////////////////////////

		/*水压*/
		v_pressure =Get_Adc_Average(ADC_CHANNEL_4,20) * 5.00 / 1024; 
		Water_Pressure = (v_pressure - OffSet) * 250;  //单位kap
		
/////////////////////////////////////////////////////////////////////////////
		
		/*HC*/
		WaterLevel=HC_Distance();
		
/////////////////////////////////////////////////////////////////////////////
		
		/*LCD*/
		
		LCD_ShowNum(170,100,Water_Pressure,4,24);
		
		if(pitch<0){
			LCD_ShowString(160,130,240,24,24,"-");
			LCD_ShowNum(170,130,-pitch,3,24);}
		else {
			LCD_ShowString(160,130,240,24,24," ");
			LCD_ShowNum(170,130,pitch,3,24);}
		if(roll<0){
			LCD_ShowString(160,160,240,24,24,"-");
			LCD_ShowNum(170,160,-roll,3,24);}
		else {
			LCD_ShowString(160,160,240,24,24," ");
			LCD_ShowNum(170,160,roll,3,24);}
		if(yaw<0){
			LCD_ShowString(160,190,240,24,24,"-");
			LCD_ShowNum(170,190,-yaw,3,24);}
		else {
			LCD_ShowString(160,190,240,24,24," ");
			LCD_ShowNum(170,190,yaw,3,24);}
		
		if((WaterLevel>1e-7)&&(WaterLevel<50))
		{
			if(WaterLevel<=10)
				LCD_ShowString(165,240,240,24,24,"Danger");
			else
				LCD_ShowString(165,240,240,24,24,"      ");
			LCD_ShowString(165,220,240,24,24,"     ");
			LCD_ShowNum(170,220,WaterLevel,3,24);
		}
		else
		{
			LCD_ShowString(165,220,240,24,24,"* * *");
			LCD_ShowString(160,240,240,24,24," Safe ");
		}
		LCD_ShowString(10,280,240,24,24,Card_ID);
			
///////////////////////////////////////////////////////////////////////////
			
		/*EC20*/
		ci++;
		if(ci>=10)
        {
            i=0;
//            Read_GPS(lat,lon);
            while(lat[i]>=48&&lat[i]<=57)
            {
                LAT=lat[i]-48+LAT*10;
                i++;
            }
            if (lat[i]=='.')
            {
                i++;
                while(lat[i]>=48&&lat[i]<=57)
                {
                    t++;
                    LATT+=pow(0.1,t)*(lat[i]-48);
                    i++;
                }
                LAT+=LATT;
            }i=0;t=0;

            while(lon[i]>=48&&lon[i]<=57)
            {
                LON=lon[i]-48+LON*10;
                i++;
            }
            if (lon[i]=='.')
            {
                i++;
                while(lon[i]>=48&&lon[i]<=57)
                {
                    t++;
                    LONN+=pow(0.1,t)*(lon[i]-48);
                    i++;
                }
                LON+=LONN;
            }i=0;t=0;
//            Pub_Msgdata();                 
			strcpy(Card_ID,"        ");
            LAT=0; LATT=0; LON=0; LONN=0; ci=0; card=0;
        }
		
/////////////////////////////////////////////////////////////////////////////
	}  
}

void Pub_Msgdata(void)
{
		data_len=Mqtt_Savedata(send_jason,Card_ID,Water_Pressure,LON,LAT,pitch,roll,yaw,WaterLevel);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"fire\",%s\r\n",datastr);//发布消息
        delay_ms(100);
        printf(send_jason);
//        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0
//        while(stry==NULL)
//        {
//			printf(send_jason);
//			delay_ms(100);
//            stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0
//        }
        delay_ms(300);
        Clear_Buffer(2);
}

//定时器3中断服务函数
void TIM2_IRQHandler(void)
{
	 if((TIM2->SR & TIM_FLAG_UPDATE) != RESET)
		{
			TIM2->SR = ~ TIM_FLAG_UPDATE;
//			Read_GPS(lat,lon);
//            while(lat[i]>=48&&lat[i]<=57)
//            {
//                LAT=lat[i]-48+LAT*10;
//                i++;
//            }
//            if (lat[i]=='.')
//            {
//                i++;
//                while(lat[i]>=48&&lat[i]<=57)
//                {
//                    t++;
//                    LATT+=pow(0.1,t)*(lat[i]-48);
//                    i++;
//                }
//                LAT+=LATT;
//            }i=0;t=0;

//            while(lon[i]>=48&&lon[i]<=57)
//            {
//                LON=lon[i]-48+LON*10;
//                i++;
//            }
//            if (lon[i]=='.')
//            {
//                i++;
//                while(lon[i]>=48&&lon[i]<=57)
//                {
//                    t++;
//                    LONN+=pow(0.1,t)*(lon[i]-48);
//                    i++;
//                }
//                LON+=LONN;
//            }i=0;t=0;
//            Pub_Msgdata();                
//			strcpy(Card_ID,"        ");
//            LAT=0; LATT=0; LON=0; LONN=0; card=0;
			
		}

}
