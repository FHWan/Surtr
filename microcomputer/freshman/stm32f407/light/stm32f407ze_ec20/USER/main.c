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

#define V_RMS_MAX 1.414 // �����źŵ������Чֵ

void Acquire_SensorDATE(void);
void ATOMIZER(void);
void LIGHT(void);

float db_temp,adcx;
u32 AD_PM;
char Card_ID[9];	 
int x;

int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	uart_init(115200);								//���ô��ڲ�����Ϊ115200
	uart2_init(115200);
	delay_init(168);								//��ʼ���ӳٺ���
    Adc_Init();										//��ʼ��ADC	
	ATOMIZER();        								//������ʼ��
    RC522_Init ( );  								//RC522�򿨳�ʼ��
	BEEP_Init();
	LIGHT();										//��ʼ��LED
	IIC_Init();										//��ʼ��IIC
	OLED_Init();									//��ʼ��OLED��

 	while(DHT11_Init())								//DHT11��ʼ��	
	{
 		delay_ms(200);
	}		
	
	while(EC20_init_check(0) != 0x0F);  // EC20��ʼ�����	
	
  while(1)	
	{		
		Acquire_SensorDATE();	// ��ȡ�ڶഫ��������
		GPS_Analysis();     // GPS���ݽ�
		Mqtt_Senddata();    // MQTT��������
		delay_ms(50);//��ʱ50ms�ٽ���
	}
}

// ��ȡ�ڶഫ��������
void Acquire_SensorDATE(void)
{

	    
	    /* PM2.5 */
		AD_PM=Get_Adc_Average(ADC_Channel_13  ,20);	//��ȡADCֵ
		pm= 0.17*AD_PM-0.1;	//PM2.5ת����ʽ
   
		/* ��ǿ */
		adcx=Get_Adc_Average(ADC_Channel_1  ,20);								//��ȡADCֵ
		Lux=39810*pow(2.71828,-0.01534*adcx)+3467*pow(2.71828,-0.002379*adcx); 	//��ǿת����ʽ
	    if(Lux<5)	//����ǿС��5ʱ������·��
		{
			GPIO_ResetBits(GPIOF , GPIO_Pin_4); 
		}
		else   		//����ǿ����5ʱ��Ϩ��·��
		{
			GPIO_SetBits(GPIOF , GPIO_Pin_4);
		}

        /*�����߼��*/
		adcx=Get_Adc_Average(ADC_Channel_11  ,20);	//��ȡADCֵ
		UV=(float)adcx*(5.0/4095.0);				//������ǿ��ת����ʽ
	    UV=UV*1000;
		/*������ǿ�ȵȼ��ж�*/
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
		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ		

		/*��װ�ã�PM2.5��Χ���԰�������ģ�*/  
		if	(pm>10)	//��PM2.5��ֵ����10ʱ����ʼ����
		{
			GPIO_ResetBits(GPIOF , GPIO_Pin_2);      //��Ƭ1����
		}				
		else		//��PM2.5��ֵС��50ʱ��ֹͣ����,
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_2);
		}
			
        /*�������*/
		adcx=Get_Adc_Average(ADC_Channel_3  ,20);	//��ȡADCֵ
		adcx=(float)adcx*(5.0/4095.0);				//ADCת��Ϊ��ѹֵ
		db_temp=adcx / V_RMS_MAX;//V_RMS_MAXΪ�����źŵ������Чֵ1.414
		noise=20 * log10f(db_temp);					//����ת����ʽ

		/*RC522*/
		RC522_Handel();		
		
		
		/*oled*/
		OLED_DispStr	(1,1,"PM",&tFont16);
		OLED_DisDecimal	(50,1,pm,2,&tFont16);//��ʾPM2.5ֵ
		OLED_DispStr	(1,15,"db",&tFont16);
		OLED_DisDecimal	(50,15,noise,2,&tFont16);//��ʾ����ǿ��
		OLED_DispStr	(1,29,"temp",&tFont16);
		OLED_DisDecimal	(50,29,temperature,2,&tFont16);//��ʾ�¶�
		OLED_DispStr	(1,43,"hum",&tFont16);
		OLED_DisDecimal	(50,43,humidity,2,&tFont16);//��ʾʪ��

			delay_ms(100);
}



void LIGHT(void)//��������ܳ�ʼ��
{
		 GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ��GPIOG��ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // ����PG2����Ϊ���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	 GPIO_SetBits(GPIOF, GPIO_Pin_4);
    
}


	void ATOMIZER(void)//������ʼ��
	{
		 GPIO_InitTypeDef GPIO_InitStructure;

		// ʹ��GPIOB��ʱ��
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		// ����PB1��PB2����Ϊ���ģʽ
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		//��ʼ״̬���ر���Ƭ
		
		
		GPIO_SetBits(GPIOF, GPIO_Pin_2);

	}











