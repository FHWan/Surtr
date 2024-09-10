/**
 ****************************************************************************************************
 * @file        freertos_demo.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-07-20
 * @brief       FreeRTOS Ӧ�ó���
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� CH32V307������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com/forum.php
 * ��˾��ַ:www.alientek.com
 * �����ַ:zhengdianyuanzi.tmall.com
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

#define PWM_Open    80          //�������
#define PWM_Close   90          //����ر�

extern u8 RxBuffer1[200],Rxcouter1;
extern u8 RxBuffer2[200],Rxcouter2;
extern u8 RxBuffer3[200],Rxcouter3;

u8 lat[20]="31.6789801";
u8 lon[20]="119.9522227";
u8 data_len,datastr[20],send_jason[200];

bool warning;                   //ʾ���ж�
int k;                         //�����жϣ�1���£�0��
bool get_mes=0;                 //ec20���ݻ�ȡ 1Ϊ���տ���0Ϊ��
char *stry;
char manager_id[10];
char picture[30];
char identity[10];
u8 *start_index = 0;
u8 *end_index = 0;
char count = 0;
int open;                       //���������־λ0�� 1��  bool����ֻ��0��1�������ᱬջ�������ܷ�
int ec,se,jian;                 //�����ж�
int Lux;
float power;                    //��ص���
short gyrox,gyroy,gyroz;    //������ԭʼ����
float pitch,roll,yaw;           //ŷ����
float distance;
/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  1024                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */

///* TASK1 ���� ����
// * ����: ������ �������ȼ� ��ջ��С ��������
// */
//#define TASK1_PRIO      2                   /* �������ȼ� */
//#define TASK1_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            Task1Task_Handler;  /* ������ */
//void task1(void *pvParameters);             /* ������ */

/* EC20���� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define EC20_SEND_TASK_PRIO                  2       /* EC20������Ϣ�������������ȼ���� */
#define EC20_SEND_STK_SIZE                   128    /* ��ջ��С */
TaskHandle_t EC20SENDTASK_Handler;
void EC20_Send_task(void *pvParameters);
/* MPU6050 ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define MPU6050_TASK_PRIO                  3       /* MPU6050 */
#define MPU6050_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t MPU6050TASK_Handler;
void Mpu6050_task(void *pvParameters);
/* ��� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define SERVO_TASK_PRIO                  4       /* ��� */
#define SERVO_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t SERVOTASK_Handler;
void Servo_task(void *pvParameters);
/* ������� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define BATTERY_TASK_PRIO                  5       /* ������� */
#define BATTERY_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t BATTERYTASK_Handler;
void Battery_task(void *pvParameters);
/* ��ǿ��� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define LIGHT_TASK_PRIO                  6       /* ��ǿ��� */
#define LIGHT_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t LIGHTTASK_Handler;
void Light_task(void *pvParameters);
/* ���������� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define BEEP_TASK_PRIO                  7       /* �����������ͺ�LED��˸�����ȼ���� */
#define BEEP_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t BEEPTASK_Handler;
void Beep_task(void *pvParameters);
/* ��LED��˸ ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define LED_TASK_PRIO                  8       /* �����������ͺ�LED��˸�����ȼ���� */
#define LED_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t LEDTASK_Handler;
void Led_task(void *pvParameters);
/* EC20��ȡ ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define EC20_GET_TASK_PRIO                  9       /* EC20��ȡС������Ϣ */
#define EC20_GET_STK_SIZE                   64     /* ��ջ��С */
TaskHandle_t EC20GETTASK_Handler;
void EC20_Get_task(void *pvParameters);
/******************************************************************************************************/

/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{
    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */
    /* ��������1 */
    xTaskCreate((TaskFunction_t )EC20_Send_task,
                    (const char*    )"EC20_Send",
                    (uint16_t       )EC20_SEND_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )EC20_SEND_TASK_PRIO,
                    (TaskHandle_t*  )&EC20SENDTASK_Handler);
    /* MPU6050���� */
    xTaskCreate((TaskFunction_t )Mpu6050_task,
                    (const char*    )"Mpu6050",
                    (uint16_t       )MPU6050_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )MPU6050_TASK_PRIO,
                    (TaskHandle_t*  )&MPU6050TASK_Handler);
    /* ������� */
    xTaskCreate((TaskFunction_t )Servo_task,
                    (const char*    )"Servo",
                    (uint16_t       )SERVO_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )SERVO_TASK_PRIO,
                    (TaskHandle_t*  )&SERVOTASK_Handler);
    /* ����������� */
    xTaskCreate((TaskFunction_t )Battery_task,
                    (const char*    )"Battery",
                    (uint16_t       )BATTERY_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )BATTERY_TASK_PRIO,
                    (TaskHandle_t*  )&BATTERYTASK_Handler);
    /* ��ǿ������� */
    xTaskCreate((TaskFunction_t )Light_task,
                    (const char*    )"Light",
                    (uint16_t       )LIGHT_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LIGHT_TASK_PRIO,
                    (TaskHandle_t*  )&LIGHTTASK_Handler);
    /* �������������� */
    xTaskCreate((TaskFunction_t )Beep_task,
                    (const char*    )"Beep",
                    (uint16_t       )BEEP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )BEEP_TASK_PRIO,
                    (TaskHandle_t*  )&BEEPTASK_Handler);
    /* ��LED��˸���� */
    xTaskCreate((TaskFunction_t )Led_task,
                    (const char*    )"Led",
                    (uint16_t       )LED_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LED_TASK_PRIO,
                    (TaskHandle_t*  )&LEDTASK_Handler);
    /* EC20��ȡ���� */
    xTaskCreate((TaskFunction_t )EC20_Get_task,
                    (const char*    )"EC20_Get",
                    (uint16_t       )EC20_GET_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )EC20_GET_TASK_PRIO,
                    (TaskHandle_t*  )&EC20GETTASK_Handler);

    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}

/**
 * @brief       EC20��������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
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
            printf("AT+QMTPUBEX=0,0,0,0,\"aed\",%s\r\n",datastr);//������Ϣ
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
 * @brief       MPU6050����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Mpu6050_task(void *pvParameters)
{
    while (1)
    {
        while(MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz)!=0) {}
        MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz); //����õ������ǡ�����ǡ������
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
 * @brief       �������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Servo_task(void *pvParameters)
{
    while (1)
    {
        k=KEY_Scan(0);
        if((get_mes==1)&&(k==1))
        {
            open=1;     //��
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
            open=0;     //��
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
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
                Clear_Buffer(3);

                open=1;     //��
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
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
                Clear_Buffer(3);

                open=1;     //��
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
                strncat(picture, &RxBuffer3[start_index-RxBuffer3], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
                Clear_Buffer(3);

                open=1;     //��
                TIM_SetCompare1(TIM4,PWM_Open);
                count++;
            }
        }
        vTaskDelay(10);
    }
}

/**
 * @brief       �����������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
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
 * @brief       ��ǿ�������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Light_task(void *pvParameters)
{
    while (1)
    {
        Lux=Get_ADC_Val1(ADC_Channel_4);             //��ȡADCֵ
        Lux=(4050-Lux) / 10;
        if(Lux<=0)  Lux=0;

        if(Lux<70.0)    GPIO_SetBits(GPIOB , GPIO_Pin_0);           //����ǿС��100ʱ�������ƴ�
        else            GPIO_ResetBits(GPIOB , GPIO_Pin_0);

        vTaskDelay(10);
    }
}

/**
 * @brief       ��������������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
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
 * @brief       ��LED��˸����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
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
 * @brief       EC20��ȡ����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
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
                TIM_SetCompare1(TIM4,PWM_Close);     //0�ر�   90��
                GPIO_SetBits(GPIOB , GPIO_Pin_1);
                get_mes=0;
            }
            Clear_Buffer(2);
        }
        vTaskDelay(1);
    }
}
