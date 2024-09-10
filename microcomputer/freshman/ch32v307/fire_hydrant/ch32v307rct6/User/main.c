#include "debug.h"
#include "usart.h"
#include "math.h"
#include "stdio.h"
#include "RC522.h"
#include "adc.h"
#include "beep.h"
#include "MPU6050.h"
#include "gpio.h"
#include "timer.h"
#include "lcd.h"
#include "ec20.h"

void Pub_Msgdata(void);
void Acquire_SensorDATE(void);

extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[100],Rxcouter3;
u8 data_len,datastr[10],send_jason[200];

u8 lat[20]="31.90950";//纬度
u8 lon[20]="118.891603";//经度
char *stry;

extern u8 Card_ID[9]; //卡号

int i=0;
short  gyrox,gyroy,gyroz;    //陀螺仪原始数据
u8 wp_adc;
float Water_Pressure;
float Water_Level;
const float  OffSet = 0.483 ;
int t,q;

int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART1_Init(115200);
    USART2_Init(115200);
    USART3_Init(9600);
//    EC20_Init();
//    MQTT_Init();
//    LCD_Init();//LCD初始化
//    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//    ADC_Function_Init();
//    BEEP_Init();            //初始化蜂鸣器
//    RC522_Init();           //初始化射频卡模块
//    Input_Capture_Init(1000-1,72-1);         //超声波
    while(MPU_Init())       //初始化MPU6050
    {
        Delay_Ms(200);
    }
    while(1)
    {
        Acquire_SensorDATE();
        if(q>=5)
        {
            Read_GPS(lat,lon);
            Pub_Msgdata();
            q=0;
        }
        q++;
        //Delay_Ms(300);
    }

}

void Acquire_SensorDATE(void)
{
    /*MPU6050*/
    //MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //获得陀螺仪原始数据
//    if((gyrox>100)||(gyroy>100)||(gyroz>100)||(gyrox<-100)||(gyroy<-100)||(gyroz<-100))
//        for(t=0;t<200;t++)
//                {
//                    GPIO_SetBits(GPIOE , GPIO_Pin_0);
//                    delay_ms(2);
//                    GPIO_ResetBits(GPIOE , GPIO_Pin_0);
//                    delay_ms(2);
//                }
    MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz);
    gyrox=gyrox*0.01;
    gyroy=gyroy*0.01;
    gyroz=gyroz*0.01;
    if(!((gyrox<50&&gyrox>-50)&&(gyroy<50&&gyroy>-50)&&(gyroz<150&&gyroz>130)))
            {for(t=0;t<200;t++)
                    {
                        GPIO_SetBits(GPIOE , GPIO_Pin_0);
                        delay_ms(2);
                        GPIO_ResetBits(GPIOE , GPIO_Pin_0);
                        delay_ms(2);
                    }
            }

    /*水压*/
    wp_adc = Get_ADC_Val(ADC_Channel_4);
    Water_Pressure = (wp_adc - OffSet) * 5;

    /*RC522*/
    RC522_Handle();

    //超声波
    Water_Level = Ultrasoniclength();  //cm

    if(gyrox<0)
    {
        LCD_ShowString(10,10,"X:   -",RED,WHITE,16,0);
        gyrox=-gyrox;
    }
    else
        LCD_ShowString(10,10,"X:    ",RED,WHITE,16,0);
    LCD_ShowIntNum(70,10,gyrox,3,RED,WHITE,16);
    if(gyroy<0)
    {
        LCD_ShowString(10,30,"Y:   -",RED,WHITE,16,0);
        gyroy=-gyroy;
    }
    else
        LCD_ShowString(10,30,"Y:    ",RED,WHITE,16,0);
    LCD_ShowIntNum(70,30,gyroy,3,RED,WHITE,16);
    if(gyroy<0)
    {
        LCD_ShowString(10,50,"Z:   -",RED,WHITE,16,0);
        gyroz=-gyroz;
    }
    else
        LCD_ShowString(10,50,"Z:    ",RED,WHITE,16,0);
    LCD_ShowIntNum(70,50,gyroz,3,RED,WHITE,16);
    LCD_ShowString(10,70,"High:",RED,WHITE,16,0);
    LCD_ShowIntNum(70,70,Water_Level,3,RED,WHITE,16);
    LCD_ShowString(10,90,"Pres:",RED,WHITE,16,0);
    LCD_ShowIntNum(70,90,Water_Pressure,3,RED,WHITE,16);
}

void Pub_Msgdata(void)
{
        data_len=Mqtt_Savedata(send_jason,Card_ID,Water_Pressure,lon,lat,gyrox,gyroy,gyroz,Water_Level);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"fire\",%s\r\n",datastr);//发布消息
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
