#include "debug.h"
#include "usart.h"
#include "math.h"
#include "stdio.h"
#include "RC522.h"
#include "adc.h"
#include "beep.h"
#include "lcd.h"
#include "pic.h"
#include "MPU6050.h"
#include "EC20.h"

void Pub_Msgdata(void);
void Acquire_SensorDATE(void);
void read_max30102(u8 *HR,u8 *SPO2);
void max30102_Init(void);

extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[100],Rxcouter3;
char *stry;

u8 lat[20]="31.90950";//纬度
u8 lon[20]="118.891603";//经度

int i=0;
u8 temperature,humidity;
extern unsigned char SN[4]; //卡号
float temp,wind;
float  gyrox,gyroy,gyroz;    //陀螺仪原始数据
u8 SPO2[5]={0},HR[5]={0};
u8 sp02=0,hr=0;
float adcx;

int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART1_Init(115200);
    USART2_Init(115200);
    USART3_Init(9600);
    LCD_Init();//LCD初始化
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    ADC_Function_Init();
//    EC20_Init();            //初始化ec20
//    MQTT_Init();
    BEEP_Init();            //初始化蜂鸣器
    RC522_Init();           //初始化射频卡模块
    while(DHT11_Init())     //DHT11初始化
    {
        delay_ms(200);
    }
    while(MPU_Init())       //初始化MPU6050
    {
        Delay_Ms(200);
    }
    max30102_Init();        //初始化MAX30102
    while(1)
    {
        Acquire_SensorDATE();
//        Read_GPS(lat,lon);
//        Pub_Msgdata();
        Delay_Ms(1000);
    }
}

void Acquire_SensorDATE(void)
{
    hr=0;
    sp02=0;

    /*MPU6050*/
    MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //获得陀螺仪原始数据

    /*风速*/
    adcx=Get_ADC_Val(ADC_Channel_4);
    temp=3.3-(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
    temp*=1000;                           //小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
    wind=temp*0.027;

    /*DHT11*/
    DHT11_Read_Data(&temperature,&humidity);        //读取温湿度值

    /*RC522*/
    RC522_Handle();

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

    LCD_ShowString(10,10,"temp:",RED,WHITE,16,0);
    LCD_ShowIntNum(60,10,temperature,3,RED,WHITE,16);
    LCD_ShowString(10,30,"hum:",RED,WHITE,16,0);
    LCD_ShowIntNum(60,30,humidity,3,RED,WHITE,16);
    LCD_ShowString(10,50,"wind:",RED,WHITE,16,0);
    LCD_ShowIntNum(60,50,wind,3,RED,WHITE,16);
    LCD_ShowString(10,70,"HR:",RED,WHITE,16,0);
    LCD_ShowIntNum(60,70,hr,3,RED,WHITE,16);
    LCD_ShowString(10,90,"SPO2:",RED,WHITE,16,0);
    LCD_ShowIntNum(60,90,sp02,3,RED,WHITE,16);


}

void max30102_Init(void)
{
    char *strx;
    Uart3_SendStr("AT\r\n");
    while(strx==NULL)
    {
        Uart3_SendStr("AT\r\n");
        delay_ms(700);
       strx=strstr((const char*)RxBuffer3,(const char*)"OK");
    }
}

void read_max30102(u8 *HR,u8 *SPO2)
{
       char *strx;
       Clear_Buffer(3);
        Uart3_SendStr("AT+HEART\r\n");
          delay_ms(100);
                strx=strstr((const char*)RxBuffer3,(const char*)"OK");

        delay_ms(100);
        while(strx==NULL)
        {
            Uart3_SendStr("AT+HEART\r\n");
            delay_ms(100);
            strx=strstr((const char*)RxBuffer3,(const char*)"OK");
        }
        if(RxBuffer3[7]!='N')
        {
            HR[2]=NULL;
            HR[0]=RxBuffer3[7];
            HR[1]=RxBuffer3[8];
            if(RxBuffer3[9]!=0X0D)
            HR[2]=RxBuffer3[9];
        }

        Clear_Buffer(3);
        Uart3_SendStr("AT+SPO2\r\n");
                delay_ms(100);
                strx=strstr((const char*)RxBuffer3,(const char*)"OK");
        while(strx==NULL)
        {
                        Uart3_SendStr("AT+SPO2\r\n");
                    delay_ms(100);
            strx=strstr((const char*)RxBuffer3,(const char*)"OK");
        }
        if(RxBuffer3[6]!='N')
        {
            SPO2[2]=NULL;
            SPO2[0]=RxBuffer3[6];
            SPO2[1]=RxBuffer3[7];
            if(RxBuffer3[8]!=0X0D)
                SPO2[2]=RxBuffer3[8];
        }
}

void Pub_Msgdata(void)
{
      u8 data_len,datastr[10],send_jason[200];
        data_len=Mqtt_Savedata(send_jason,wind,lon,lat,gyrox,gyroy,gyroz,temperature,humidity,SN,sp02,hr);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"orienteering\",%s\r\n",datastr);//发布消息
        delay_ms(100);
        Uart2_SendStr(send_jason);
        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0
        while(stry==NULL)
        {

            stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0

        }
        delay_ms(1000);
        Clear_Buffer(2);
}

