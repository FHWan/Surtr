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

#define V_RMS_MAX 1.414 // �����źŵ������Чֵ

void Acquire_SensorDATE(void);
void ATOMIZER(void);
void LIGHT(void);
//void Pub_Msgdata(void);

char str[30];
float Lux,UV;
float db,db_temp;
int UVindex;  //�����ߵȼ�
u16 adcx;
u8 temperature;  	    //DHT11�¶�
u8 humidity;          //DHT11ʪ�ȶ�
u32 AD_PM=0,AD_LUX,AD_UV;
double pm=0;
char Card_ID[9];	 
int x;
u8 lat[20]="31.90950";
u8 lon[20]="118.891603";
u8 data_len,datastr[10],send_jason[200];

int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	uart_init(115200);								//���ô��ڲ�����Ϊ115200
	uart2_init(115200);								//���ô��ڲ�����Ϊ115200
	delay_init();								//��ʼ���ӳٺ���
	Adc_Init();										//��ʼ��ADC	
	ATOMIZER();        								//������ʼ��
    RC522_Init ();  								//RC522�򿨳�ʼ��
	LIGHT();										//��ʼ��LED
	IIC_Init();										//��ʼ��IIC
	OLED_Init();									//��ʼ��OLED��
	EC20_Init();									//��ʼ��EC20
	
 	while(DHT11_Init())								//DHT11��ʼ��	
	{
 		delay_ms(200);
	}			
  while(1)	
	{	
		Acquire_SensorDATE();	// ��ȡ�ڶഫ��������
//		Read_GPS(lat,lon);
//		Pub_Msgdata();
		delay_ms(50);//��ʱ60ms�ٽ���
	}
}

// ��ȡ�ڶഫ��������
void Acquire_SensorDATE(void)
{    
	    /* PM2.5 */
		AD_PM=Get_Adc_Average(ADC_Channel_1  ,20);	//��ȡADCֵ
		pm= 0.17*AD_PM-0.1;	//PM2.5ת����ʽ
//		sprintf(str,"PM2.5��%.2f \r\n",pm);
//		Uart1Send(str);//�������ת�����PM2.5ֵ
//	    printf("PM2.5��%.2f \r\n",pm);
	
		/* ��ǿ */					
		AD_LUX=Get_Adc_Average(ADC_Channel_5  ,20);//��ȡADCֵ
		Lux=39810*pow(2.71828,-0.01534*AD_LUX)+3467*pow(2.71828,-0.002379*AD_LUX); 	//��ǿת����ʽ
//		sprintf(str,"��ǿ��%.2f \r\n",Lux);
//		Uart1Send(str);//�������ת����Ĺ�ǿֵ
//		printf("��ǿ��%.2f \r\n",Lux);
	    if(Lux<5)	//����ǿС��5ʱ������·��
		{
			GPIO_ResetBits(GPIOC , GPIO_Pin_9); 
		}
		else   		//����ǿ����5ʱ��Ϩ��·��
		{
			GPIO_SetBits(GPIOC , GPIO_Pin_9);
		}

        /*�����߼��*/
		AD_UV=Get_Adc_Average(ADC_Channel_11  ,20);	//��ȡADCֵ
		UV=(float)AD_UV*(5.0/4095.0);				//������ǿ��ת����ʽ
	    UV=UV*1000;
		/*������ǿ�ȵȼ��ж�*/
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
//		Uart1Send(str);//�������������ǿ�ȵȼ�
//		printf("UVI:  %d 	\r\n",UVindex);	//�������������ǿ�ȵȼ�

		/*DHT11*/
		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ	
		sprintf(str,"---DHTT11 ������� ------- \r\n");
		Uart1Send(str);
		sprintf(str,"Temp:  %d C	\r\n",temperature); // ������ʾ�¶�
		Uart1Send(str);
		sprintf(str,"Humi:  %d %%	\r\n",humidity);	// ������ʾʪ��
		Uart1Send(str);
		sprintf(str,"-------------------------- \r\n");
		Uart1Send(str);
//		printf("---DHTT11 ������� ------- \r\n");				
//		printf("Temp:  %d C	\r\n",temperature);				   		   
//		printf("Humi:  %d %%	\r\n",humidity);		
//		printf("-------------------------- \r\n");

		/*��װ�ã�PM2.5��Χ���԰�������ģ�*/  
		if	(pm>50)	//��PM2.5��ֵ����50ʱ����ʼ����
		{
			GPIO_ResetBits(GPIOB , GPIO_Pin_7); 
			//��Ƭ1����
		}				
		else		//��PM2.5��ֵС��50ʱ��ֹͣ����
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}

        /*�������*/
		adcx=Get_Adc_Average(ADC_Channel_10  ,20);	//��ȡADCֵ
		adcx=(float)adcx*(5.0/4095.0);				//ADCת��Ϊ��ѹֵ
		db_temp=adcx / V_RMS_MAX;//V_RMS_MAXΪ�����źŵ������Чֵ1.414
		db=20 * log10f(db_temp);					//����ת����ʽ
//		sprintf(str,"DB:  %.2f 	\r\n",db);
//		Uart1Send(str);//����ͨ����ʾ����
//		printf("DB:  %.2f 	\r\n",db);				//����ͨ����ʾ����			

		/*RC522*/
//		sprintf(str,"Ѱ��\r\n");
//		Uart1Send (str);
		RC522_Handel();
		
//		sprintf(str,"\r\n\r\n");
//		Uart1Send(str);
//		printf("\r\n\r\n");

		/*oled*/
		OLED_DispStr	(1,1,"PM",&tFont16);
		OLED_DisDecimal	(50,1,pm,3,&tFont16);//��ʾPM2.5ֵ
		OLED_DispStr	(1,15,"UVI",&tFont16);
		OLED_DisDecimal	(50,15,UVindex,1,&tFont16);//��ʾ������ǿ�ȵȼ�
		OLED_DispStr	(1,29,"temp",&tFont16);
		OLED_DisDecimal	(50,29,temperature,2,&tFont16);//��ʾ�¶�
		OLED_DispStr	(1,43,"hum",&tFont16);
		OLED_DisDecimal	(50,43,humidity,2,&tFont16);//��ʾʪ��
//		OLED_DispStr(1,57,"db",&tFont16);
//		OLED_DisDecimal(50,57,db,2,&tFont16);


//			delay_ms(100);
}



void LIGHT(void)//��������ܳ�ʼ��
{
		 GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ��GPIOC��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // ����PC9����Ϊ���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_9);
    
}


void ATOMIZER(void)//������ʼ��
	{
		 GPIO_InitTypeDef GPIO_InitStructure;

		// ʹ��GPIOB��ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		// ����PB7����Ϊ���ģʽ
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//��ʼ״̬���ر���Ƭ
		
		
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
