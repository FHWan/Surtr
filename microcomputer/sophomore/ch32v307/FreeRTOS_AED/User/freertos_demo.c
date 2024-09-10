/**
 ****************************************************************************************************
 * @file        freertos_demo.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       FreeRTOS 应用程序
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 CH32V307开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com/forum.php
 * 公司网址:www.alientek.com
 * 购买地址:zhengdianyuanzi.tmall.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/EC20/EC20.h"
#include "./BSP/adc/adc.h"
#include "./BSP/BEEPLED/gpio.h"
#include "./BSP/servo/servo.h"
#include "./BSP/MPU6050/MPU6050.h"

#define PWM_Open    80          //舵机开启
#define PWM_Close   90          //舵机关闭

extern u8 RxBuffer1[200],Rxcouter1;
extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[200],Rxcouter3;

u8 lat[20]="31.6789801";
u8 lon[20]="119.9522227";
u8 data_len,datastr[20],send_jason[200];

bool warning;                   //示警判断
int k;                         //按键判断，1按下，0无
bool get_mes=0;                 //ec20数据获取 1为接收开，0为关
char *stry;
char manager_id[10];
char picture[30];
char identity[10];
u8 *start_index = 0;
u8 *end_index = 0;
char count = 0;
int open;                       //舵机开启标志位0关 1开  bool类型只有0和1，其他会爆栈，程序跑飞
int ec,se,jian;                 //计数判断
int Lux;
float power;                    //电池电量
short gyrox,gyroy,gyroz;    //陀螺仪原始数据
float pitch,roll,yaw;           //欧拉角
float distance;
/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  1024                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

///* TASK1 任务 配置
// * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
// */
//#define TASK1_PRIO      2                   /* 任务优先级 */
//#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
//void task1(void *pvParameters);             /* 任务函数 */

/* EC20发送 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define EC20_SEND_TASK_PRIO                  2       /* EC20发送消息到服务器，优先级最高 */
#define EC20_SEND_STK_SIZE                   128    /* 堆栈大小 */
TaskHandle_t EC20SENDTASK_Handler;
void EC20_Send_task(void *pvParameters);
/* MPU6050 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define MPU6050_TASK_PRIO                  3       /* MPU6050 */
#define MPU6050_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t MPU6050TASK_Handler;
void Mpu6050_task(void *pvParameters);
/* 舵机 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define SERVO_TASK_PRIO                  4       /* 舵机 */
#define SERVO_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t SERVOTASK_Handler;
void Servo_task(void *pvParameters);
/* 电量检测 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define BATTERY_TASK_PRIO                  5       /* 电量检测 */
#define BATTERY_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t BATTERYTASK_Handler;
void Battery_task(void *pvParameters);
/* 光强检测 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define LIGHT_TASK_PRIO                  6       /* 光强检测 */
#define LIGHT_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t LIGHTTASK_Handler;
void Light_task(void *pvParameters);
/* 蜂鸣器报警 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define BEEP_TASK_PRIO                  7       /* 蜂鸣器报警和红LED闪烁，优先级最低 */
#define BEEP_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t BEEPTASK_Handler;
void Beep_task(void *pvParameters);
/* 红LED闪烁 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define LED_TASK_PRIO                  8       /* 蜂鸣器报警和红LED闪烁，优先级最低 */
#define LED_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t LEDTASK_Handler;
void Led_task(void *pvParameters);
/* EC20获取 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define EC20_GET_TASK_PRIO                  9       /* EC20获取小程序信息 */
#define EC20_GET_STK_SIZE                   64     /* 堆栈大小 */
TaskHandle_t EC20GETTASK_Handler;
void EC20_Get_task(void *pvParameters);
/******************************************************************************************************/

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t )EC20_Send_task,
                    (const char*    )"EC20_Send",
                    (uint16_t       )EC20_SEND_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )EC20_SEND_TASK_PRIO,
                    (TaskHandle_t*  )&EC20SENDTASK_Handler);
    /* MPU6050任务 */
    xTaskCreate((TaskFunction_t )Mpu6050_task,
                    (const char*    )"Mpu6050",
                    (uint16_t       )MPU6050_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )MPU6050_TASK_PRIO,
                    (TaskHandle_t*  )&MPU6050TASK_Handler);
    /* 舵机任务 */
    xTaskCreate((TaskFunction_t )Servo_task,
                    (const char*    )"Servo",
                    (uint16_t       )SERVO_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )SERVO_TASK_PRIO,
                    (TaskHandle_t*  )&SERVOTASK_Handler);
    /* 电量检测任务 */
    xTaskCreate((TaskFunction_t )Battery_task,
                    (const char*    )"Battery",
                    (uint16_t       )BATTERY_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )BATTERY_TASK_PRIO,
                    (TaskHandle_t*  )&BATTERYTASK_Handler);
    /* 光强检测任务 */
    xTaskCreate((TaskFunction_t )Light_task,
                    (const char*    )"Light",
                    (uint16_t       )LIGHT_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LIGHT_TASK_PRIO,
                    (TaskHandle_t*  )&LIGHTTASK_Handler);
    /* 蜂鸣器报警任务 */
    xTaskCreate((TaskFunction_t )Beep_task,
                    (const char*    )"Beep",
                    (uint16_t       )BEEP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )BEEP_TASK_PRIO,
                    (TaskHandle_t*  )&BEEPTASK_Handler);
    /* 红LED闪烁任务 */
    xTaskCreate((TaskFunction_t )Led_task,
                    (const char*    )"Led",
                    (uint16_t       )LED_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LED_TASK_PRIO,
                    (TaskHandle_t*  )&LEDTASK_Handler);
    /* EC20获取任务 */
    xTaskCreate((TaskFunction_t )EC20_Get_task,
                    (const char*    )"EC20_Get",
                    (uint16_t       )EC20_GET_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )EC20_GET_TASK_PRIO,
                    (TaskHandle_t*  )&EC20GETTASK_Handler);

    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

/**
 * @brief       EC20发送任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
bool EC20Init = 0;
void EC20_Send_task(void *pvParameters)
{
    while (1)
    {
        if(EC20Init == 0){
            delay_ms(5000);
            delay_ms(5000);
            EC20_Init();
            MQTT_Init();
            TIM_SetCompare1(TIM4,PWM_Close);
            EC20Init = 1;
        }
        else{
            vTaskDelay(2500);
            Clear_Buffer(2);
            Read_GPS(lat,lon);

            data_len=Mqtt_Savedata(send_jason,
                                    identity,
                                    picture,
                                    manager_id,
                                    lon,lat,
                                    pitch,roll,yaw,
                                    power,
                                    count,
                                    warning,
                                    open,
                                    Lux
            );
            sprintf(datastr,"%d",data_len);
            printf("AT+QMTPUBEX=0,0,0,0,\"aed\",%s\r\n",datastr);//发布消息
            vTaskDelay(100);
            printf(send_jason);
            memset(manager_id,'\0', sizeof(manager_id));
            memset(picture,'\0', sizeof(picture));
            memset(identity,'\0', sizeof(identity));
            Clear_Buffer(2);
            vTaskDelay(2500);
        }
    }
}

/**
 * @brief       MPU6050任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Mpu6050_task(void *pvParameters)
{
    while (1)
    {
        while(MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz)!=0) {}
        MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz); //计算得到俯仰角、横滚角、航向角
        pitch=gyrox*0.01;
        roll=gyroy*0.01;
        yaw=gyroz*0.01;

        if(((pitch>10)||(pitch<-10))||((roll>10)||(roll<-10)))
            warning=1;
        else
            warning=0;
        vTaskDelay(10);
    }
}

/**
 * @brief       舵机任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Servo_task(void *pvParameters)
{
    while (1)
    {
        k=KEY_Scan(0);
        if((get_mes==1)&&(k==1))
        {
            open=1;     //开
            TIM_SetCompare1(TIM4,PWM_Open);
            sprintf(identity,"Weixin");
            get_mes=0;
            count++;
        }
        else if((open==0)&&(k==1))
        {
            Uart3_SendStr("OK\r\n");
        }
        else if((open==1)&&(k==1))
        {
            open=0;     //关
            TIM_SetCompare1(TIM4,PWM_Close);
        }
        if (open==0)
        {
            if(strstr((const char*)RxBuffer3,(const char*)"Unknown")!=NULL)
            {
                sprintf(identity,"Uk");
                memset(picture,'\0', sizeof(picture));
                start_index = strstr(RxBuffer3,"Unknown");
                end_index   = strstr(RxBuffer3,".jpg");
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
                Clear_Buffer(3);

                open=1;     //开
                TIM_SetCompare1(TIM4,PWM_Open);
                count++;
            }
            else if(strstr((const char*)RxBuffer3,(const char*)"fan")!=NULL)
            {
                sprintf(identity,"Admin");
                sprintf(manager_id,"fan");
                memset(picture,'\0', sizeof(picture));
                start_index = strstr(RxBuffer3,"fan");
                end_index   = strstr(RxBuffer3,".jpg");
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
                Clear_Buffer(3);

                open=1;     //开
                TIM_SetCompare1(TIM4,PWM_Open);
                count++;
            }
            else if(strstr((const char*)RxBuffer3,(const char*)"xzf")!=NULL)
            {
                sprintf(identity,"Admin");
                sprintf(manager_id,"xzf");
                memset(picture,'\0', sizeof(picture));
                start_index = strstr(RxBuffer3,"xzf");
                end_index   = strstr(RxBuffer3,".jpg");
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
                Clear_Buffer(3);

                open=1;     //开
                TIM_SetCompare1(TIM4,PWM_Open);
                count++;
            }
        }
        vTaskDelay(10);
    }
}

/**
 * @brief       电量检测任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Battery_task(void *pvParameters)
{
    while (1)
    {
        Clear_Buffer(1);
        Uart1_SendStr("\x01\x04");
        Uart1_Send00("\x00");
        Uart1_SendStr("\x01");
        Uart1_Send00("\x00");
        Uart1_SendStr("\x01\x60\x0A");

        vTaskDelay(100);

        if((RxBuffer1[0]=='\x01')&&(RxBuffer1[1]=='\x04')&&(RxBuffer1[2]=='\x02'))
        {
            power = RxBuffer1[3]*256 + RxBuffer1[4];
            power = (power - 1080) / 0.24;
            power = (int)power / 10.0;
        }
    }
}

/**
 * @brief       光强检测任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Light_task(void *pvParameters)
{
    while (1)
    {
        Lux=Get_ADC_Val1(ADC_Channel_4);             //获取ADC值
        Lux=(4050-Lux) / 10;
        if(Lux<=0)  Lux=0;

        if(Lux<70.0)    GPIO_SetBits(GPIOB , GPIO_Pin_0);           //当光强小于100时，点亮灯带
        else            GPIO_ResetBits(GPIOB , GPIO_Pin_0);

        vTaskDelay(10);
    }
}

/**
 * @brief       蜂鸣器报警任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Beep_task(void *pvParameters)
{
    while (1)
    {
        if(get_mes==1)
        {
            for(jian=0;jian<50;jian++)
            {
                GPIO_SetBits(GPIOE , GPIO_Pin_0);
                vTaskDelay(3);
                GPIO_ResetBits(GPIOE , GPIO_Pin_0);
                vTaskDelay(3);
            }
        }
        vTaskDelay(100);
    }
}
/**
 * @brief       红LED闪烁任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Led_task(void *pvParameters)
{
    while (1)
    {
        if(get_mes==1)
        {
            GPIO_SetBits(GPIOB , GPIO_Pin_1);
            vTaskDelay(100);
            GPIO_ResetBits(GPIOB , GPIO_Pin_1);
        }
        else
        {
            GPIO_ResetBits(GPIOB , GPIO_Pin_1);
        }
        vTaskDelay(100);
    }
}
/**
 * @brief       EC20获取任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void EC20_Get_task(void *pvParameters)
{
    while (1)
    {
        stry=strstr((const char*)RxBuffer2,(const char*)"+QMTRECV: 0,0");
        if(stry!=NULL)
        {
            if((strstr((const char*)RxBuffer2,(const char*)"{\"id\":\"1\"}")!=NULL)&&(open==0))
            {
                get_mes=1;
            }
            else if(strstr((const char*)RxBuffer2,(const char*)"{\"id\":\"0\"}")!=NULL)
            {
                open=0;
                TIM_SetCompare1(TIM4,PWM_Close);     //0关闭   90度
                GPIO_SetBits(GPIOB , GPIO_Pin_1);
                get_mes=0;
            }
            Clear_Buffer(2);
        }
        vTaskDelay(1);
    }
}
