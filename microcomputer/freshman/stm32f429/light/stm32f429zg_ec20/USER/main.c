#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "adc.h"
#include "dht11.h"
#include "rc522.h"
#include "ec20.h"
#include "math.h"
#include "lcd.h"
#include "HC.h"

void Pub_Msgdata(void);
void LIGHT(void);//��������ܳ�ʼ��
void ATOMIZER(void);//������ʼ��

u8 lat[20]="31.6789801";//??
u8 lon[20]="119.9522227";//??
float LAT,LATT,LON,LONN;
u8 data_len,datastr[10],send_jason[200];

char Card_ID[9];
char *stry;

int t,i,ci,card;
u8 temperature,humidity;
float db_temp,adcx;
float LAT,LATT,LON,LONN;
float pm;            // PM2.5
float Lux ;              //  ��ǿ
float WaterLevel;
u32   AD_PM;
float UV;                 // ������ֵ
int uvconcentration,water;              //�����ߵȼ�
float noise;
uint16_t Adc_buffer[4]; // ADC�ɼ����ݻ���

int main(void)
{
	int i=0;
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(9600);
	uart2_init(115200);				//��ʼ��USART
//	MY_ADC_Init();                  //��ʼ��ADC1ͨ��5
///////////////////////////////////////////////////////////////////////////////	
//	LCD_Init();		//��ʼ��LCD 
//	POINT_COLOR=RED; 
//	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
//	LCD_ShowString(10,130,240,32,32,"EC20........");
//	EC20_Init();            //��ʼ��ec20
//	MQTT_Init();
//	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
//	BEEP_MY();			 			//��ʼ��������
	RC522_Init();  					//RC522�򿨳�ʼ��
//	ultrasound_init();				//��������ʼ��
///////////////////////////////////////////////////////////////////////////////	
//	LCD_ShowString(10,130,240,32,32,"DHT11.......");
//	while(DHT11_Init())				//��ʼ��DHT11
//	{
//		delay_ms(100);	
//	}				
//	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
//	LIGHT();
//	ATOMIZER();
///////////////////////////////////////////////////////////////////////////////	
//	LCD_ShowString(10,0,240,32,32,"Light");
//    POINT_COLOR=BLUE; 
//	LCD_ShowString(10,40, 240,24,24,"Noise     :");
//	LCD_ShowString(10,70, 240,24,24,"PM2.5     :");
//	LCD_ShowString(10,100,240,24,24,"UV        :");
//	LCD_ShowString(10,130,240,24,24,"Temp      :");
//	LCD_ShowString(10,160,240,24,24,"Hum       :");
////	LCD_ShowString(10,190,240,24,24,"Pitch     :");
//	LCD_ShowString(10,220,240,24,24,"HC        :");
//	POINT_COLOR=BLACK; 
    
    while(1)
	{
/////////////////////////////////////////////////////////////////////////////
		
//		/*DHT11*/
//		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ	PB12
//		
///////////////////////////////////////////////////////////////////////////////
//		
//		/*RC522*/
		RC522_Handel();
//		
///////////////////////////////////////////////////////////////////////////////

//		/* ��ǿ */
//		Lux=Get_Adc_Average(ADC_CHANNEL_8,20);				//��ȡADCֵ
//		Lux=39810*pow(2.71828,-0.01534*Lux)+3467*pow(2.71828,-0.002379*Lux);  //��ǿת����ʽ
//		if(Lux<5)   //����ǿС��5ʱ������·��
//		{
//			LCD_ShowString(170,0,240,32,32,"Open");
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET);//�ر�PE2
//		}
//		else        //����ǿ����5ʱ��Ϩ��·��
//		{
//			LCD_ShowString(170,0,240,32,32,"    ");
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);//��PE2
//		}
//		
//		/*�������*/
//		db_temp=Get_Adc_Average(ADC_CHANNEL_4,20);   //��ȡADCֵ
//		db_temp=(float)db_temp*(3.3/4095.0);              //ADCת��Ϊ��ѹֵ
//		db_temp=100*db_temp / 1.414;//�����źŵ������Чֵ1.414
//		
//		 /* PM2.5 */
//		pm=Get_Adc_Average(ADC_CHANNEL_5,20);   //��ȡADCֵ
//		pm= 0.17*pm-0.1; //PM2.5ת����ʽ
//		/*��װ�ã�PM2.5��Χ���԰�������ģ�*/
//		if  (pm>100) //��PM2.5��ֵ����10ʱ����ʼ����
//		{
//			water=1;
//			POINT_COLOR=RED; 
//			LCD_ShowString(80,70,240,32,32,"!!!");
//			POINT_COLOR=BLACK; 
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);      //��Ƭ1����
//		}
//		else        //��PM2.5��ֵС��50ʱ��ֹͣ����,
//		{
//			water=0;
//			LCD_ShowString(80,70,240,32,32,"   ");
//			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);
//		}
//		
//		 /*�����߼��*/
//		UV=Get_Adc_Average(ADC_CHANNEL_7,20);  //��ȡADCֵ
//		UV=(float)UV*(5.0/4095.0);                //������ǿ��ת����ʽ
//		UV=UV*1000;

//	   /*������ǿ�ȵȼ��ж�*/
//		if     (UV>0&UV<50)     {uvconcentration=0;}
//	    else if(UV>=50&UV<227)  {uvconcentration=1;}
//     	else if(UV>=227&UV<318) {uvconcentration=2;}
//		else if(UV>=318&UV<408) {uvconcentration=3;}
//		else if(UV>=408&UV<503) {uvconcentration=4;}
//		else if(UV>=503&UV<606) {uvconcentration=5;}
//		else if(UV>=606&UV<696) {uvconcentration=6;}
//		else if(UV>=696&UV<795) {uvconcentration=7;}
//		else if(UV>=795&UV<881) {uvconcentration=8;}
//		else if(UV>=881&UV<976) {uvconcentration=9;}
//		else if(UV>=976&UV<1079){uvconcentration=10;}
//		else                    {uvconcentration=0;}
//		
///////////////////////////////////////////////////////////////////////////////
//		
//		/*HC*/
//		WaterLevel=HC_Distance();
//		
///////////////////////////////////////////////////////////////////////////////
//		
//		/*LCD*/
//		LCD_ShowNum(170,40,db_temp,3,24);
//		LCD_ShowNum(170,70,pm,3,24);
//		LCD_ShowNum(170,100,uvconcentration,3,24);
//		
//		LCD_ShowNum(170,130,temperature,3,24);
//		LCD_ShowNum(170,160,humidity,3,24);
//		
//		if((WaterLevel>1e-7)&&(WaterLevel<50))
//		{
//			if(WaterLevel<=10)
//				LCD_ShowString(165,240,240,24,24,"Danger");
//			else
//				LCD_ShowString(165,240,240,24,24,"      ");
//			LCD_ShowString(165,220,240,24,24,"     ");
//			LCD_ShowNum(170,220,WaterLevel,3,24);
//		}
//		else
//		{
//			LCD_ShowString(165,220,240,24,24,"* * *");
//			LCD_ShowString(160,240,240,24,24," Safe ");
//		}
//		stry=strstr((const char*)Card_ID,(const char*)"B32ABB1D");
//		if(stry!=NULL)	
//		{
//			card=1;
//			LCD_ShowString(170,280,240,24,24,"Right");
//		}
//		else
//			LCD_ShowString(170,280,240,24,24,"     ");
//		LCD_ShowString(10,280,240,24,24,Card_ID);
//			
/////////////////////////////////////////////////////////////////////////////
			
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
			strcpy(Card_ID,"00000000");
            LAT=0; LATT=0; LON=0; LONN=0; ci=0; card=0;
        }
		
/////////////////////////////////////////////////////////////////////////////
	}  
}

void Pub_Msgdata(void)
{
		data_len=Mqtt_Savedata(send_jason,uvconcentration,db_temp,temperature,humidity,pm,LON,LAT,water,(int)WaterLevel,card);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"light\",%s\r\n",datastr);//������Ϣ
        delay_ms(100);
        printf(send_jason);
        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//�����ɹ�   +QMTPUBEX: 0,0,0
        while(stry==NULL)
        {
            stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//�����ɹ�   +QMTPUBEX: 0,0,0
        }
        delay_ms(300);
        Clear_Buffer(2);
}

void LIGHT(void)//��������ܳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOE_CLK_ENABLE();  //ʹ��PEʱ��
    
    GPIO_InitStructure.Pin= GPIO_PIN_2;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;//����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//����
    HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET);//�ر�PE2
}

void ATOMIZER(void)//������ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOE_CLK_ENABLE();  				//ʹ��PEʱ��
    
    GPIO_InitStructure.Pin= GPIO_PIN_4;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;		//����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;	//����
    HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);//�ر�PE4
}