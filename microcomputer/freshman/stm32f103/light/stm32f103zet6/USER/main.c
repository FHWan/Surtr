#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "adc.h"
#include "math.h"
#include "stdio.h"
#include "rc522.h"
#include "oled.h"
#include "ec20.h"
#include "string.h"

#define V_RMS_MAX 1.414 // 声音信号的最大有效值

void Acquire_SensorDATE(void);
void ATOMIZER(void);
void LIGHT(void);
//void Pub_Msgdata(void);

char str[30];
float Lux,UV;
float db,db_temp;
int UVindex;  //紫外线等级
u16 adcx;
u8 temperature;  	    //DHT11温度
u8 humidity;          //DHT11湿度度
u32 AD_PM=0,AD_LUX,AD_UV;
double pm=0;
char Card_ID[9];	 
int x;
u8 lat[20]="31.90950";
u8 lon[20]="118.891603";
u8 data_len,datastr[10],send_jason[200];

int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	uart_init(115200);								//设置串口波特率为115200
	uart2_init(115200);								//设置串口波特率为115200
	delay_init();								//初始化延迟函数
	Adc_Init();										//初始化ADC	
	ATOMIZER();        								//雾化器初始化
    RC522_Init ();  								//RC522打卡初始化
	LIGHT();										//初始化LED
	IIC_Init();										//初始化IIC
	OLED_Init();									//初始化OLED屏
	EC20_Init();									//初始化EC20
	
 	while(DHT11_Init())								//DHT11初始化	
	{
 		delay_ms(200);
	}			
  while(1)	
	{	
		Acquire_SensorDATE();	// 获取众多传感器数据
//		Read_GPS(lat,lon);
//		Pub_Msgdata();
		delay_ms(50);//延时60ms再进行
	}
}

// 获取众多传感器数据
void Acquire_SensorDATE(void)
{    
	    /* PM2.5 */
		AD_PM=Get_Adc_Average(ADC_Channel_1  ,20);	//获取ADC值
		pm= 0.17*AD_PM-0.1;	//PM2.5转换公式
//		sprintf(str,"PM2.5：%.2f \r\n",pm);
//		Uart1Send(str);//串口输出转换后的PM2.5值
//	    printf("PM2.5：%.2f \r\n",pm);
	
		/* 光强 */					
		AD_LUX=Get_Adc_Average(ADC_Channel_5  ,20);//获取ADC值
		Lux=39810*pow(2.71828,-0.01534*AD_LUX)+3467*pow(2.71828,-0.002379*AD_LUX); 	//光强转换公式
//		sprintf(str,"光强：%.2f \r\n",Lux);
//		Uart1Send(str);//串口输出转换后的光强值
//		printf("光强：%.2f \r\n",Lux);
	    if(Lux<5)	//当光强小于5时，点亮路灯
		{
			GPIO_ResetBits(GPIOC , GPIO_Pin_9); 
		}
		else   		//当光强大于5时，熄灭路灯
		{
			GPIO_SetBits(GPIOC , GPIO_Pin_9);
		}

        /*紫外线检测*/
		AD_UV=Get_Adc_Average(ADC_Channel_11  ,20);	//获取ADC值
		UV=(float)AD_UV*(5.0/4095.0);				//紫外线强度转换公式
	    UV=UV*1000;
		/*紫外线强度等级判定*/
		if	   (UV>=0&UV<50)	{UVindex=0;}
		else if(UV>=50&UV<227)  {UVindex=1;}
		else if(UV>=227&UV<318) {UVindex=2;}
		else if(UV>=318&UV<408) {UVindex=3;}
		else if(UV>=408&UV<503) {UVindex=4;}
		else if(UV>=503&UV<606) {UVindex=5;}
		else if(UV>=606&UV<696) {UVindex=6;}
		else if(UV>=696&UV<795) {UVindex=7;}
		else if(UV>=795&UV<881) {UVindex=8;}
		else if(UV>=881&UV<976) {UVindex=9;}
		else if(UV>=976&UV<1079){UVindex=10;}
		else					{UVindex=11;}
//		sprintf(str,"UVI:  %d\r\n",UVindex);
//		Uart1Send(str);//串口输出紫外线强度等级
//		printf("UVI:  %d 	\r\n",UVindex);	//串口输出紫外线强度等级

		/*DHT11*/
		DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值	
		sprintf(str,"---DHTT11 数据输出 ------- \r\n");
		Uart1Send(str);
		sprintf(str,"Temp:  %d C	\r\n",temperature); // 串口显示温度
		Uart1Send(str);
		sprintf(str,"Humi:  %d %%	\r\n",humidity);	// 串口显示湿度
		Uart1Send(str);
		sprintf(str,"-------------------------- \r\n");
		Uart1Send(str);
//		printf("---DHTT11 数据输出 ------- \r\n");				
//		printf("Temp:  %d C	\r\n",temperature);				   		   
//		printf("Humi:  %d %%	\r\n",humidity);		
//		printf("-------------------------- \r\n");

		/*雾化装置（PM2.5范围可以按需求更改）*/  
		if	(pm>50)	//当PM2.5数值大于50时，开始喷雾
		{
			GPIO_ResetBits(GPIOB , GPIO_Pin_7); 
			//雾化片1工作
		}				
		else		//当PM2.5数值小于50时，停止喷雾
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}

        /*噪音检测*/
		adcx=Get_Adc_Average(ADC_Channel_10  ,20);	//获取ADC值
		adcx=(float)adcx*(5.0/4095.0);				//ADC转化为电压值
		db_temp=adcx / V_RMS_MAX;//V_RMS_MAX为声音信号的最大有效值1.414
		db=20 * log10f(db_temp);					//声贝转换公式
//		sprintf(str,"DB:  %.2f 	\r\n",db);
//		Uart1Send(str);//串口通信显示声贝
//		printf("DB:  %.2f 	\r\n",db);				//串口通信显示声贝			

		/*RC522*/
//		sprintf(str,"寻卡\r\n");
//		Uart1Send (str);
		RC522_Handel();
		
//		sprintf(str,"\r\n\r\n");
//		Uart1Send(str);
//		printf("\r\n\r\n");

		/*oled*/
		OLED_DispStr	(1,1,"PM",&tFont16);
		OLED_DisDecimal	(50,1,pm,3,&tFont16);//显示PM2.5值
		OLED_DispStr	(1,15,"UVI",&tFont16);
		OLED_DisDecimal	(50,15,UVindex,1,&tFont16);//显示紫外线强度等级
		OLED_DispStr	(1,29,"temp",&tFont16);
		OLED_DisDecimal	(50,29,temperature,2,&tFont16);//显示温度
		OLED_DispStr	(1,43,"hum",&tFont16);
		OLED_DisDecimal	(50,43,humidity,2,&tFont16);//显示湿度
//		OLED_DispStr(1,57,"db",&tFont16);
//		OLED_DisDecimal(50,57,db,2,&tFont16);


//			delay_ms(100);
}



void LIGHT(void)//发光二极管初始化
{
		 GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOC的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // 配置PC9引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_9);
    
}


void ATOMIZER(void)//雾化器初始化
	{
		 GPIO_InitTypeDef GPIO_InitStructure;

		// 使能GPIOB的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		// 配置PB7引脚为输出模式
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//初始状态，关闭雾化片
		
		
		GPIO_SetBits(GPIOB, GPIO_Pin_7);

	}
	
//void Pub_Msgdata(void)
//{
//      char *strx;
//      
//  //      data_len=Mqtt_Savedata(send_jason,water_level,lon,lat,AIR_Quality0,AIR_Quality1,temperature, humidity, tumble);
//	 data_len=Mqtt_Savedata(send_jason,Card_ID,pressure,lon,lat,pitch,roll,yaw,length);
//        sprintf(datastr,"%d",data_len);
//        printf("AT+QMTPUBEX=0,0,0,0,\"fire\",%s\r\n",datastr);//????
//        delay_ms(100);
//	 printf("%s\r\n",send_jason);
//        //Uart2_SendStr(send_jason);
//        strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0
//        while(strx==NULL)
//        {

//            strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");//????   +QMTPUBEX: 0,0,0

//        }
//        delay_ms(1000);
//        Clear_Buffer();
//}
