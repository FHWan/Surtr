#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "adc.h"
#include "dht11.h"
#include "OLED.h"
#include "rc522.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "ec20.h"
/************************************************
 ALIENTEK 探索者STM32F407开发板 实验18
 ADC模数转换实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

void read_max30102(u8 *HR,u8 *SPO2);
void max30102_Init(void);
void Pub_Msgdata(void);

u8 temperature;  	    
u8 humidity; 
u16 adcx;
float pitch,roll,yaw; //欧拉角
char Card_ID[9];
char card_ID[9];
char *stry;
float temp,wind;
u8 SPO2[5]={0},HR[5]={0};
u8 sp02=0,hr=0;
u8 lat[20]="31.90950";//??
u8 lon[20]="118.891603";//??

int main(void)
{
    int i=0;
	
    HAL_Init();                   	//初始化HAL库    
    Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(9600);             	//初始化USART
	uart2_init(115200);             	//初始化USART
	BEEP_MY();
	RC522_Init();  					//RC522打卡初始化
    MY_ADC_Init();                  //初始化ADC1通道5
	IIC_Init();						//初始化IIC
	OLED_Init();					//初始化OLED屏
	EC20_Init(); 					// EC20初始化
	while(mpu_dmp_init())			//初始化MPU6050(必须水平放置)
	{
		delay_ms(100);	
	}	
	while(DHT11_Init())				//初始化DHT11
	{
		delay_ms(100);	
	}	
	max30102_Init();				//初始化MAX30102
    while(1)
	{
		hr=0;
		sp02=0;
		/*DHT11*/
		DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值	PB12
		
		/*RC522*/
		RC522_Handel();
		stry=strstr((const char*)Card_ID,(const char*)"63FB1798");//返回OK
		if(stry)
		{	
			stry=0;
			strcpy(card_ID,"00000000");	
			strcpy(card_ID,"20231002");			
			strcpy(Card_ID,"0000000000");
			strcpy(card_ID,"0000000000");
		}
		
		/*风速*/
		adcx=Get_Adc_Average(ADC_CHANNEL_5,20);//获取通道5的转换值，20次取平均
		temp=(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
		temp*=1000;                           //小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
		wind=temp*0.027;
	
	
		/*MPU6050*/
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
		mpu_dmp_get_data(&pitch,&roll,&yaw); //计算得到俯仰角、横滚角、航向角
		
		/*MAX30102*/
		read_max30102(HR,SPO2);
		while(HR[i]>=48&&HR[i]<=57)
		{
			hr=HR[i]-48+hr*10;
			i++;
		}i=0;
		while(SPO2[i]>=48&&SPO2[i]<=57)
		{
			sp02=SPO2[i]-48+sp02*10;
			i++;
		}i=0;
			
		/*oled*/
		OLED_DispStr	(1,29,"HR",&tFont16);
		OLED_DisDecimal	(50,29,hr,0,&tFont16);
		OLED_DispStr	(1,43,"SPO2",&tFont16);
		OLED_DisDecimal	(50,43,sp02,0,&tFont16);
	
		Read_GPS(lat,lon);
		Pub_Msgdata();
		
		delay_ms(250);	
	} 
}

void Pub_Msgdata(void)
{
      char *strx;
      u8 data_len,datastr[10],send_jason[200];
      data_len=Mqtt_Savedata(send_jason,HR,SPO2,lon,lat,temperature, humidity,pitch,roll,yaw,wind,card_ID);
      sprintf(datastr,"%d",data_len);
      printf("AT+QMTPUBEX=0,0,0,0,\"waterlevel\",%s\r\n",datastr);//????
      delay_ms(100);
	  printf("%s\r\n",send_jason);

        delay_ms(1000);
        Clear_Buffer();
}

void max30102_Init(void)
{
	char *strx;
    Uart1_SendStr("AT\r\n");
    while(strx==NULL)
    { 
		Uart1_SendStr("AT\r\n");
        delay_ms(700);
       strx=strstr((const char*)RxBuffer1,(const char*)"OK");//??OK
    }
}


void read_max30102(u8 *HR,u8 *SPO2)
{
				char *strx;
        Clear_Buffer1();
        Uart1_SendStr("AT+HEART\r\n");
	      delay_ms(100);
				strx=strstr((const char*)RxBuffer1,(const char*)"OK");//??OK

        delay_ms(100);
        while(strx==NULL)
        {
            Uart1_SendStr("AT+HEART\r\n");
            delay_ms(100);
            strx=strstr((const char*)RxBuffer1,(const char*)"OK");//??OK
        }
        if(RxBuffer1[7]!='N')
        {
            HR[2]=NULL;
            HR[0]=RxBuffer1[7];
            HR[1]=RxBuffer1[8];
            if(RxBuffer1[9]!=0X0D)
                HR[2]=RxBuffer1[9];
        }



        Clear_Buffer1();  
        Uart1_SendStr("AT+SPO2\r\n");
				delay_ms(100);
				strx=strstr((const char*)RxBuffer1,(const char*)"OK");//??OK
        while(strx==NULL)
        {
						Uart1_SendStr("AT+SPO2\r\n");
					delay_ms(100);
            strx=strstr((const char*)RxBuffer1,(const char*)"OK");//??OK
        }
        if(RxBuffer1[6]!='N')
        {
            SPO2[2]=NULL;
            SPO2[0]=RxBuffer1[6];
            SPO2[1]=RxBuffer1[7];
            if(RxBuffer1[8]!=0X0D)
                SPO2[2]=RxBuffer1[8];
        }
}

