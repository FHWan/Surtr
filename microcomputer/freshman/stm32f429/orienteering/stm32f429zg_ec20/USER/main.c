#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "adc.h"
#include "dht11.h"
#include "rc522.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "ec20.h"
#include "math.h"
#include "lcd.h"

void read_max30102(u8 *HR,u8 *SPO2);
void max30102_Init(void);
void Pub_Msgdata(void);

int t,i,ci,card;
u8 lat[20]="31.6789801";//??
u8 lon[20]="119.9522227";//??
//u8 lat[20]="31.90950";//??
//u8 lon[20]="118.891603";//??
float LAT,LATT,LON,LONN;
u8 data_len,datastr[10],send_jason[200];

u16 adcx;
float pitch,roll,yaw; //ŷ����
char Card_ID[9];
char *stry;
float temp,WindSpeed;

u8 SPO2[5]={0},HR[5]={0};
u8 sp02=0,hr=0;
uint8_t temperature;    // �¶�
uint8_t humidity;       // ʪ��
uint16_t Adc_buffer[4]; // ADC�ɼ����ݻ���

int main(void)
{
	int i=0;
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(9600);
	uart2_init(115200);				//��ʼ��USART
/////////////////////////////////////////////////////////////////////////////	
	LCD_Init();		//��ʼ��LCD 
	POINT_COLOR=RED; 
	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
////	LCD_ShowString(10,130,240,32,32,"EC20........");
////	EC20_Init();            //��ʼ��ec20
////	MQTT_Init();
////	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
//	BEEP_MY();						//��ʼ��������
//	RC522_Init();  					//RC522�򿨳�ʼ��
///////////////////////////////////////////////////////////////////////////////		
//	LCD_ShowString(10,130,240,32,32,"max30102....");
//	max30102_Init();//��ʼ��MAX30102
//	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
////	LCD_ShowString(10,130,240,32,32,"MPU6050.....");
////	while(mpu_dmp_init())			//��ʼ��MPU6050(����ˮƽ����)
////	{
////		delay_ms(100);	
////	}			
////	LCD_Clear(WHITE);
///////////////////////////////////////////////////////////////////////////////	
//	LCD_ShowString(10,130,240,32,32,"DHT11.......");
//	while(DHT11_Init())				//��ʼ��DHT11
//	{
//		delay_ms(100);	
//	}				
//	LCD_Clear(WHITE);
/////////////////////////////////////////////////////////////////////////////	
//    MY_ADC_Init();                  //��ʼ��ADC1ͨ��5
/////////////////////////////////////////////////////////////////////////////	
	LCD_ShowString(10,0,240,32,32,"Orienteer");
    POINT_COLOR=BLACK; 
//	LCD_ShowString(10,40, 240,24,24,"WindSpeed :");
	LCD_ShowString(10,70, 240,24,24,"SPO2      :");
	LCD_ShowString(10,100,240,24,24,"HR        :");
	LCD_ShowString(10,130,240,24,24,"Temp      :");
	LCD_ShowString(10,160,240,24,24,"Hum       :");
//	LCD_ShowString(10,190,240,24,24,"Pitch     :");
//	LCD_ShowString(10,220,240,24,24,"Roll      :");
//	LCD_ShowString(10,250,240,24,24,"Yaw       :");
    
    while(1)
	{
/////////////////////////////////////////////////////////////////////////////
		
//		/*DHT11*/
//		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ	PB12
//		
///////////////////////////////////////////////////////////////////////////////
//		
//		/*RC522*/
//		RC522_Handel();
			
/////////////////////////////////////////////////////////////////////////////
		
		/*����*/
//		adcx=Get_Adc_Average(ADC_CHANNEL_5,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
//		temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		temp*=1000;                           //С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
//		WindSpeed=temp*0.027;
		
/////////////////////////////////////////////////////////////////////////////
		
		/*MPU6050*/
//		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
//		mpu_dmp_get_data(&pitch,&roll,&yaw); //����õ������ǡ�����ǡ������

/////////////////////////////////////////////////////////////////////////////
		
		/*MAX30102*/
//		hr=0;
//		sp02=0;
//		read_max30102(HR,SPO2);
//		while(HR[i]>=48&&HR[i]<=57)
//		{
//			hr=HR[i]-48+hr*10;
//			i++;
//		}i=0;
//		while(SPO2[i]>=48&&SPO2[i]<=57)
//		{
//			sp02=SPO2[i]-48+sp02*10;
//			i++;
//		}i=0;
		
/////////////////////////////////////////////////////////////////////////////
		
		/*LCD*/
//		LCD_ShowNum(170,40,WindSpeed,3,24);
		
		if((sp02>0)&&(hr>0))
		{
			LCD_ShowNum(170,70,sp02,3,24);
			LCD_ShowNum(170,100,hr,3,24);
		}
		
		LCD_ShowNum(170,130,temperature,3,24);
		LCD_ShowNum(170,160,humidity,3,24);
		
//		if(pitch<0){
//			LCD_ShowString(160,190,240,24,24,"-");
//			LCD_ShowNum(170,190,-pitch,3,24);}
//		else {
//			LCD_ShowString(160,190,240,24,24," ");
//			LCD_ShowNum(170,190,pitch,3,24);}
//		if(roll<0){
//			LCD_ShowString(160,220,240,24,24,"-");
//			LCD_ShowNum(170,220,-roll,3,24);}
//		else {
//			LCD_ShowString(160,220,240,24,24," ");
//			LCD_ShowNum(170,220,roll,3,24);}
//		if(yaw<0){
//			LCD_ShowString(160,250,240,24,24,"-");
//			LCD_ShowNum(170,250,-yaw,3,24);}
//		else {
//			LCD_ShowString(160,250,240,24,24," ");
//			LCD_ShowNum(170,250,yaw,3,24);}
	
		LCD_ShowString(10,280,240,24,24,Card_ID);
			
/////////////////////////////////////////////////////////////////////////////
			
		/*EC20*/
//		ci++;
//		if(ci>=5)
//        {
//            i=0;
//            Read_GPS(lat,lon);
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
//			strcpy(Card_ID,"00000000");
//            LAT=0; LATT=0; LON=0; LONN=0; ci=0;
//        }
		
/////////////////////////////////////////////////////////////////////////////
	}  
}

void Pub_Msgdata(void)
{
        data_len=Mqtt_Savedata(send_jason,Card_ID,LON,LAT,pitch,roll,yaw,temperature,humidity,WindSpeed,hr,sp02);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"orienteering\",%s\r\n",datastr);//������Ϣ
        delay_ms(100);
        printf(send_jason);
        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//�����ɹ�   +QMTPUBEX: 0,0,0
        while(stry==NULL)
        {
            stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//�����ɹ�   +QMTPUBEX: 0,0,0
        }
        delay_ms(1000);
        Clear_Buffer(2);
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
        Clear_Buffer(1);
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



        Clear_Buffer(1);  
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
