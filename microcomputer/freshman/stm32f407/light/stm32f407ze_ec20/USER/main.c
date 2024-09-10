#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "adc.h"
#include "math.h"
#include "stdio.h"
#include "beep.h"
#include "rc522.h"
#include "oled.h"
#include "EC20.h"

#define V_RMS_MAX 1.414 // 声音信号的最大有效值

void Acquire_SensorDATE(void);
void ATOMIZER(void);
void LIGHT(void);

float db_temp,adcx;
u32 AD_PM;
char Card_ID[9];	 
int x;

int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	uart_init(115200);								//设置串口波特率为115200
	uart2_init(115200);
	delay_init(168);								//初始化延迟函数
    Adc_Init();										//初始化ADC	
	ATOMIZER();        								//雾化器初始化
    RC522_Init ( );  								//RC522打卡初始化
	BEEP_Init();
	LIGHT();										//初始化LED
	IIC_Init();										//初始化IIC
	OLED_Init();									//初始化OLED屏

 	while(DHT11_Init())								//DHT11初始化	
	{
 		delay_ms(200);
	}		
	
	while(EC20_init_check(0) != 0x0F);  // EC20初始化检测	
	
  while(1)	
	{		
		Acquire_SensorDATE();	// 获取众多传感器数据
		GPS_Analysis();     // GPS数据解
		Mqtt_Senddata();    // MQTT发送数据
		delay_ms(50);//延时50ms再进行
	}
}

// 获取众多传感器数据
void Acquire_SensorDATE(void)
{

	    
	    /* PM2.5 */
		AD_PM=Get_Adc_Average(ADC_Channel_13  ,20);	//获取ADC值
		pm= 0.17*AD_PM-0.1;	//PM2.5转换公式
   
		/* 光强 */
		adcx=Get_Adc_Average(ADC_Channel_1  ,20);								//获取ADC值
		Lux=39810*pow(2.71828,-0.01534*adcx)+3467*pow(2.71828,-0.002379*adcx); 	//光强转换公式
	    if(Lux<5)	//当光强小于5时，点亮路灯
		{
			GPIO_ResetBits(GPIOF , GPIO_Pin_4); 
		}
		else   		//当光强大于5时，熄灭路灯
		{
			GPIO_SetBits(GPIOF , GPIO_Pin_4);
		}

        /*紫外线检测*/
		adcx=Get_Adc_Average(ADC_Channel_11  ,20);	//获取ADC值
		UV=(float)adcx*(5.0/4095.0);				//紫外线强度转换公式
	    UV=UV*1000;
		/*紫外线强度等级判定*/
		if	   (UV>0&UV<50)	    {UVindex=0;}
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
			
		/*DHT11*/
		DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值		

		/*雾化装置（PM2.5范围可以按需求更改）*/  
		if	(pm>10)	//当PM2.5数值大于10时，开始喷雾
		{
			GPIO_ResetBits(GPIOF , GPIO_Pin_2);      //雾化片1工作
		}				
		else		//当PM2.5数值小于50时，停止喷雾,
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_2);
		}
			
        /*噪音检测*/
		adcx=Get_Adc_Average(ADC_Channel_3  ,20);	//获取ADC值
		adcx=(float)adcx*(5.0/4095.0);				//ADC转化为电压值
		db_temp=adcx / V_RMS_MAX;//V_RMS_MAX为声音信号的最大有效值1.414
		noise=20 * log10f(db_temp);					//声贝转换公式

		/*RC522*/
		RC522_Handel();		
		
		
		/*oled*/
		OLED_DispStr	(1,1,"PM",&tFont16);
		OLED_DisDecimal	(50,1,pm,2,&tFont16);//显示PM2.5值
		OLED_DispStr	(1,15,"db",&tFont16);
		OLED_DisDecimal	(50,15,noise,2,&tFont16);//显示噪音强度
		OLED_DispStr	(1,29,"temp",&tFont16);
		OLED_DisDecimal	(50,29,temperature,2,&tFont16);//显示温度
		OLED_DispStr	(1,43,"hum",&tFont16);
		OLED_DisDecimal	(50,43,humidity,2,&tFont16);//显示湿度

			delay_ms(100);
}



void LIGHT(void)//发光二极管初始化
{
		 GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOG的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // 配置PG2引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	 GPIO_SetBits(GPIOF, GPIO_Pin_4);
    
}


	void ATOMIZER(void)//雾化器初始化
	{
		 GPIO_InitTypeDef GPIO_InitStructure;

		// 使能GPIOB的时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		// 配置PB1和PB2引脚为输出模式
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		//初始状态，关闭雾化片
		
		
		GPIO_SetBits(GPIOF, GPIO_Pin_2);

	}











