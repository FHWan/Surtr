#include "debug.h"
#include "usart.h"
#include "math.h"
#include "stdio.h"
#include "RC522.h"
#include "adc.h"
#include "beep.h"
#include "lcd.h"
#include "pic.h"
#include "EC20.h"
#include "gpio.h"
#include "timer.h"

#define V_RMS_MAX 1.414 // 声音信号的最大有效值

void Pub_Msgdata(void);
void Acquire_SensorDATE(void);
void ATOMIZER(void);
void LIGHT(void);

extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[100],Rxcouter3;
u8 data_len,datastr[10],send_jason[200];

u8 lat[20]="31.90950";//纬度
u8 lon[20]="118.891603";//经度
char *stry;

int t,i,ci,ka,card;
u8 temperature,humidity;
float db_temp,adcx;
float LAT,LATT,LON,LONN;
float pm;            // PM2.5
float Lux ;              //  光强
float WaterLevel;
u32   AD_PM;
float UV;                 // 紫外线值
int uvconcentration,water;              //紫外线等级
float noise;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART1_Init(115200);
    USART2_Init(115200);
    USART3_Init(9600);
//    LCD_Init();//LCD初始化
//    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//    ADC_Function_Init();
    EC20_Init();            //初始化ec20
    MQTT_Init();
    BEEP_Init();            //初始化蜂鸣器
    LIGHT();                //初始化LED
    ATOMIZER();             //雾化器初始化
    RC522_Init();           //初始化射频卡模块
    Input_Capture_Init(1000-1,72-1);         //超声波
    while(DHT11_Init())     //DHT11初始化
    {
        Delay_Ms(200);
    }

    LCD_ShowString(20,10,"light",BLUE,WHITE,16,0);
    LCD_ShowString(10,30,"PM:",BLACK,WHITE,16,0);
    LCD_ShowString(10,50,"temp:",BLACK,WHITE,16,0);
    LCD_ShowString(10,70,"hum:",BLACK,WHITE,16,0);
    LCD_ShowString(10,90,"UV:",BLACK,WHITE,16,0);
    LCD_ShowString(10,110,"HC:",BLACK,WHITE,16,0);

    while(1)
    {
        ci++;
        Acquire_SensorDATE();
        if(ci>=10)
        {
            i=0;
            Read_GPS(lat,lon);
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
            Pub_Msgdata();
            LAT=0;
            LATT=0;
            LON=0;
            LONN=0;
            ci=0;
            card=0;
        }
        Delay_Ms(100);
    }
}

void Acquire_SensorDATE(void)
{

    /* 光强 */
    Lux=Get_ADC_Val1(ADC_Channel_4);                                        //获取ADC值
    Lux=39810*pow(2.71828,-0.01534*Lux)+3467*pow(2.71828,-0.002379*Lux);  //光强转换公式
    if(Lux<5)   //当光强小于5时，点亮路灯
    {
        LCD_ShowString(90,10,"Open",RED,WHITE,16,0);
        GPIO_ResetBits(GPIOE , GPIO_Pin_4);
    }
    else        //当光强大于5时，熄灭路灯
    {
        LCD_ShowString(90,10,"    ",RED,WHITE,16,0);
        GPIO_SetBits(GPIOE , GPIO_Pin_4);
    }

    /*噪音检测*/
   db_temp=Get_ADC_Val1(ADC_Channel_5);   //获取ADC值
   db_temp=(float)db_temp*(5.0/4095.0);              //ADC转化为电压值
   db_temp=100*db_temp / V_RMS_MAX;//V_RMS_MAX为声音信号的最大有效值1.414

    /* PM2.5 */
    pm=Get_ADC_Val2(ADC_Channel_6);   //获取ADC值
    pm= 0.17*pm-0.1; //PM2.5转换公式

    /*雾化装置（PM2.5范围可以按需求更改）*/
    if  (pm>50) //当PM2.5数值大于10时，开始喷雾
    {
            water=1;
        GPIO_ResetBits(GPIOE , GPIO_Pin_2);      //雾化片1工作
    }
        else        //当PM2.5数值小于50时，停止喷雾,
    {
            water=0;
        GPIO_SetBits(GPIOE, GPIO_Pin_2);
    }

    /*紫外线检测*/
    UV=Get_ADC_Val2(ADC_Channel_7);  //获取ADC值
    UV=(float)UV*(5.0/4095.0);                //紫外线强度转换公式
    UV=UV*1000;

   /*紫外线强度等级判定*/
   if     (UV>0&UV<50)     {uvconcentration=0;}
   else if(UV>=50&UV<227)  {uvconcentration=1;}
   else if(UV>=227&UV<318) {uvconcentration=2;}
   else if(UV>=318&UV<408) {uvconcentration=3;}
   else if(UV>=408&UV<503) {uvconcentration=4;}
   else if(UV>=503&UV<606) {uvconcentration=5;}
   else if(UV>=606&UV<696) {uvconcentration=6;}
   else if(UV>=696&UV<795) {uvconcentration=7;}
   else if(UV>=795&UV<881) {uvconcentration=8;}
   else if(UV>=881&UV<976) {uvconcentration=9;}
   else if(UV>=976&UV<1079){uvconcentration=10;}
   else                    {uvconcentration=0;}

    /*DHT11*/
    DHT11_Read_Data(&temperature,&humidity);        //读取温湿度值

    /*RC522*/
    RC522_Handle();
    stry=strstr((const char*)Card_ID,(const char*)"B32ABB1D");
    if(stry!=NULL)
    {
        card=1;
        for(ka=0;ka<100;ka++)
        {
            GPIO_SetBits(GPIOE , GPIO_Pin_0);
            Delay_Ms(2);
            GPIO_ResetBits(GPIOE , GPIO_Pin_0);
            Delay_Ms(2);
        }
        for(i=0;i<9;i++)
        {
            Card_ID[i]=0;
        }
    }
    //超声波
    WaterLevel = Ultrasoniclength();  //cm
    if(WaterLevel>50)
    {
        LCD_ShowString(60,110,"** ",BLACK,WHITE,16,0);
        LCD_ShowString(80,110,"  Safe",GRAYBLUE,WHITE,16,0);
    }
    else
    {
        if(WaterLevel<=10)
            LCD_ShowString(80,110,"Danger",RED,WHITE,16,0);
        else
            LCD_ShowString(80,110,"      ",RED,WHITE,16,0);
        LCD_ShowIntNum(50,110,WaterLevel,3,BLACK,WHITE,16);
    }

    LCD_ShowIntNum(50,30,pm,3,BLACK,WHITE,16);
    LCD_ShowIntNum(50,50,temperature,3,BLACK,WHITE,16);
    LCD_ShowIntNum(50,70,humidity,3,BLACK,WHITE,16);
    LCD_ShowIntNum(50,90,uvconcentration,3,BLACK,WHITE,16);
}

void LIGHT(void)//发光二极管初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOF的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    // 配置PF4引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

     GPIO_SetBits(GPIOE, GPIO_Pin_4);

}


void ATOMIZER(void)//雾化器初始化
{
     GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOF的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    // 配置PE2引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    //初始状态，关闭雾化片
    GPIO_SetBits(GPIOE, GPIO_Pin_2);

}

void Pub_Msgdata(void)
{
        data_len=Mqtt_Savedata(send_jason,uvconcentration,db_temp,(int)temperature,(int)humidity,pm,LON,LAT,water,WaterLevel,card);
        sprintf(datastr,"%d",data_len);
        printf("AT+QMTPUBEX=0,0,0,0,\"light\",%s\r\n",datastr);//发布消息
        Delay_Ms(100);
        Uart2_SendStr(send_jason);
        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0
        while(stry==NULL)
        {
            stry=strstr((const char*)RxBuffer2,(const char*)"+QMTPUBEX: 0,0,0");//发布成功   +QMTPUBEX: 0,0,0
        }
        Delay_Ms(1000);
        Clear_Buffer(2);
}
