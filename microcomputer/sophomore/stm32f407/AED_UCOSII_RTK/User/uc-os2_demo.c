#include "uc-os2_demo.h"
#include "usart.h"
#include "./MALLOC/malloc.h"
#include "string.h"
#include "stdbool.h"	//bool����ֻ��0��1�������ᱬջ�������ܷ�

/*uC/OS-III*********************************************************************************************/
#include "os.h"
#include "cpu.h"

/******************************************************************************************************/
/* UCOSII�������� */
#define BEEP 		PDout(11)	//BEEP
#define LED_Bule 	PDout(0)	//�׹�
#define LED_Red 	PDout(1)	//���
#define PWM_Open 	89			//�������
#define PWM_Close 	95			//����ر�

u8 lat[20]="31.391915";
u8 lon[20]="118.894156";
u8 data_len,datastr[20],send_jason[200];
extern _GGA_Typedef GGA;

bool warning;					//ʾ���ж�
bool k;							//�����жϣ�1���£�0��
bool get_mes=0;					//ec20���ݻ�ȡ 1Ϊ���տ���0Ϊ��
char *stry;
char manager_id[10];
char picture[30];
char identity[10];
char *start_index = 0;
char *end_index = 0;
char count = 0;	
int open;						//���������־λ0�� 1��	bool����ֻ��0��1�������ᱬջ�������ܷ�
int ec,se,jian;					//�����ж�
int Lux; 
float power;					//��ص���
float pitch,roll,yaw; 			//ŷ����
float distance;


/* START ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define START_TASK_PRIO                 10      /* ��ʼ��������ȼ�����Ϊ��� */
#define START_STK_SIZE                  1024     /* ��ջ��С */

OS_STK START_TASK_STK[START_STK_SIZE];          /* �����ջ */
void start_task(void *pdata);                   /* ������ */


/* EC20���� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define EC20_SEND_TASK_PRIO                  1       /* EC20������Ϣ�������������ȼ���� */
#define EC20_SEND_STK_SIZE                   128    /* ��ջ��С */
OS_STK EC20_SEND_TASK_STK[EC20_SEND_STK_SIZE];       /* �����ջ */
void EC20_Send_task(void *pdata);                    /* ������ */

/* EC20��ȡ ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define EC20_GET_TASK_PRIO                  2       /* EC20��ȡС������Ϣ */
#define EC20_GET_STK_SIZE                   128     /* ��ջ��С */
OS_STK EC20_GET_TASK_STK[EC20_GET_STK_SIZE];        /* �����ջ */
void EC20_Get_task(void *pdata);                    /* ������ */

/* MPU6050 ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define MPU6050_TASK_PRIO                  3       /* MPU6050 */
#define MPU6050_STK_SIZE                   256     /* ��ջ��С */
OS_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];         /* �����ջ */
void Mpu6050_task(void *pdata);                    /* ������ */

/* ��� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define SERVO_TASK_PRIO                  4       /* ��� */
#define SERVO_STK_SIZE                   128     /* ��ջ��С */
OS_STK SERVO_TASK_STK[SERVO_STK_SIZE];           /* �����ջ */
void Servo_task(void *pdata);                    /* ������ */

/* ������� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define BATTERY_TASK_PRIO                  5       /* ������� */
#define BATTERY_STK_SIZE                   128     /* ��ջ��С */
OS_STK BATTERY_TASK_STK[BATTERY_STK_SIZE];         /* �����ջ */
void Battery_task(void *pdata);                    /* ������ */

/* ��ǿ��� ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define LIGHT_TASK_PRIO                  6       /* ��ǿ��� */
#define LIGHT_STK_SIZE                   128     /* ��ջ��С */
OS_STK LIGHT_TASK_STK[LIGHT_STK_SIZE];           /* �����ջ */
void Light_task(void *pdata);                    /* ������ */

/* �����������ͺ�LED��˸ ���� ����
 * ����: �������ȼ� ��ջ��С ��
 */
#define BELED_TASK_PRIO                  7       /* �����������ͺ�LED��˸�����ȼ���� */
#define BELED_STK_SIZE                   128     /* ��ջ��С */
OS_STK BELED_TASK_STK[BELED_STK_SIZE];           /* �����ջ */
void Beled_task(void *pdata);                    /* ������ */

/******************************************************************************************************/
/**
 * @brief       uC/OS-II������ں���
 * @param       ��
 * @retval      ��
 */
void uc_os2_demo(void)
{
    OSInit();                                                   /* UCOS��ʼ�� */
    OSTaskCreateExt((void(*)(void *) )start_task,               /* ������ */
                    (void *          )0,                        /* ���ݸ��������Ĳ��� */
                    (OS_STK *        )&START_TASK_STK[START_STK_SIZE - 1], /* �����ջջ�� */
                    (INT8U           )START_TASK_PRIO,          /* �������ȼ� */
                    (INT16U          )START_TASK_PRIO,          /* ����ID����������Ϊ�����ȼ�һ�� */
                    (OS_STK *        )&START_TASK_STK[0],       /* �����ջջ�� */
                    (INT32U          )START_STK_SIZE,           /* �����ջ��С */
                    (void *          )0,                        /* �û�����Ĵ洢�� */
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP); /* ����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ */
    OSStart();  /* ��ʼ���� */
    
    for (;;)
    {
        /* ����������� */
    }
}

/**
 * @brief       start_task
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *p_arg)
{
    OS_CPU_SR cpu_sr = 0;
    CPU_INT32U cnts;

    OSStatInit();                   /* ����ͳ������ */
    
    /* �������õĽ���Ƶ������SysTick */
    cnts = (CPU_INT32U)(HAL_RCC_GetSysClockFreq() / OS_TICKS_PER_SEC);
    OS_CPU_SysTickInit(cnts);
    OS_ENTER_CRITICAL();            /* �����ٽ���(�ر��ж�) */
    
	/* EC20�������� */
    OSTaskCreateExt((void(*)(void *) )EC20_Send_task,
                    (void *          )0,						//����һ����ָ��,EC20_Send_task����Ҫ��������
                    (OS_STK *        )&EC20_SEND_TASK_STK[EC20_SEND_STK_SIZE - 1],
                    (INT8U           )EC20_SEND_TASK_PRIO,
                    (INT16U          )EC20_SEND_TASK_PRIO,
                    (OS_STK *        )&EC20_SEND_TASK_STK[0],
                    (INT32U          )EC20_SEND_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
    /* EC20��ȡ���� */
    OSTaskCreateExt((void(*)(void *) )EC20_Get_task,
                    (void *          )0,
                    (OS_STK *        )&EC20_GET_TASK_STK[EC20_GET_STK_SIZE - 1],
                    (INT8U           )EC20_GET_TASK_PRIO,
                    (INT16U          )EC20_GET_TASK_PRIO,
                    (OS_STK *        )&EC20_GET_TASK_STK[0],
                    (INT32U          )EC20_GET_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
    /* MPU6050���� */
    OSTaskCreateExt((void(*)(void *) )Mpu6050_task,
                    (void *          )0,											
                    (OS_STK *        )&MPU6050_TASK_STK[MPU6050_STK_SIZE - 1],
                    (INT8U           )MPU6050_TASK_PRIO,
                    (INT16U          )MPU6050_TASK_PRIO,
                    (OS_STK *        )&MPU6050_TASK_STK[0],
                    (INT32U          )MPU6050_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* ������� */
    OSTaskCreateExt((void(*)(void *) )Servo_task,
                    (void *          )0,											
                    (OS_STK *        )&SERVO_TASK_STK[SERVO_STK_SIZE - 1],
                    (INT8U           )SERVO_TASK_PRIO,
                    (INT16U          )SERVO_TASK_PRIO,
                    (OS_STK *        )&SERVO_TASK_STK[0],
                    (INT32U          )SERVO_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* ����������� */
    OSTaskCreateExt((void(*)(void *) )Battery_task,
                    (void *          )0,											
                    (OS_STK *        )&BATTERY_TASK_STK[BATTERY_STK_SIZE - 1],
                    (INT8U           )BATTERY_TASK_PRIO,
                    (INT16U          )BATTERY_TASK_PRIO,
                    (OS_STK *        )&BATTERY_TASK_STK[0],
                    (INT32U          )BATTERY_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* ��ǿ������� */
    OSTaskCreateExt((void(*)(void *) )Light_task,
                    (void *          )0,											
                    (OS_STK *        )&LIGHT_TASK_STK[LIGHT_STK_SIZE - 1],
                    (INT8U           )LIGHT_TASK_PRIO,
                    (INT16U          )LIGHT_TASK_PRIO,
                    (OS_STK *        )&LIGHT_TASK_STK[0],
                    (INT32U          )LIGHT_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* �����������ͺ�LED��˸���� */
    OSTaskCreateExt((void(*)(void *) )Beled_task,
                    (void *          )0,											
                    (OS_STK *        )&BELED_TASK_STK[BELED_STK_SIZE - 1],
                    (INT8U           )BELED_TASK_PRIO,
                    (INT16U          )BELED_TASK_PRIO,
                    (OS_STK *        )&BELED_TASK_STK[0],
                    (INT32U          )BELED_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);	
					
					
    OS_EXIT_CRITICAL();             /* �˳��ٽ���(���ж�) */
    OSTaskSuspend(START_TASK_PRIO); /* ����ʼ���� */
}
/**
 * @brief       EC20��������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void EC20_Send_task(void *p_arg)
{
    while (1)
    {
		OSTimeDly(2500);
		Clear_Buffer(2);
//		Read_GPS(lat,lon);
//		Parase_RTK();       // ����RTK����
//		if(GGA.longitude == NULL)
//		{
//			strcpy(GGA.longitude,"119.9522227");
//			strcpy(GGA.latitude,"31.6789801");
//		}
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
		OSTimeDly(100);
		printf(send_jason);
		memset(manager_id,'\0', sizeof(manager_id));
		memset(picture,'\0', sizeof(picture));
		memset(identity,'\0', sizeof(identity));
		Clear_Buffer(2);
		
		OSTimeDly(2500);
    }
}

/**
 * @brief       EC20��ȡ����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void EC20_Get_task(void *p_arg)
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
				Servo_SetAngle4(PWM_Close);		//0�ر�	90��
				LED_Red=0;
				get_mes=0;
			}
			
		}Clear_Buffer(2);
        OSTimeDly(10);
    }
}

/**
 * @brief       MPU6050����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Mpu6050_task(void *p_arg)
{
    while (1)
    {
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
		mpu_dmp_get_data(&pitch,&roll,&yaw); //����õ������ǡ�����ǡ������
		
		if(((pitch>10)||(pitch<-10))||((roll>10)||(roll<-10)))
			warning=1;
		else
			warning=0;
		OSTimeDly(10);
    }
}

/**
 * @brief       �������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Servo_task(void *p_arg)
{
    while (1)
    {
		k=KEY_Scan(0);
		if((get_mes==1)&&(k==1))
		{
			open=1;		//��
			Servo_SetAngle4(PWM_Open);	
			sprintf(identity,"Weixin");
			get_mes=0;
			count++;
		}
		else if((open==0)&&(k==1))
		{
			Uart4_SendStr("OK\r\n");
		}
		else if((open==1)&&(k==1))
		{
			open=0;		//��
			Servo_SetAngle4(PWM_Close);
		}
		if (open==0)
		{
			if(strstr((const char*)RxBuffer4,(const char*)"Unknown")!=NULL)
			{
				sprintf(identity,"Unknown");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer4,"Unknown");
				end_index   = strstr(RxBuffer4,".jpg");
				strncat(picture, &RxBuffer4[start_index-RxBuffer4], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
				Clear_Buffer(4);
			
				open=1;		//��
				Servo_SetAngle4(PWM_Open);
				count++;				
			}
			else if(strstr((const char*)RxBuffer4,(const char*)"fan")!=NULL)
			{
				sprintf(identity,"Admin");
				sprintf(manager_id,"fan");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer4,"fan");
				end_index   = strstr(RxBuffer4,".jpg");
				strncat(picture, &RxBuffer4[start_index-RxBuffer4], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
				Clear_Buffer(4);
				
				open=1;		//��
				Servo_SetAngle4(PWM_Open);	
				count++;
			}
			else if(strstr((const char*)RxBuffer4,(const char*)"xzf")!=NULL)
			{
				sprintf(identity,"Admin");
				sprintf(manager_id,"xzf");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer4,"xzf");
				end_index   = strstr(RxBuffer4,".jpg");
				strncat(picture, &RxBuffer4[start_index-RxBuffer4], end_index - start_index + 4);  // ��Դ�ַ�����ָ����Χ�ڵ��ַ�ƴ�ӵ�Ŀ���ַ���
				Clear_Buffer(4);
				
				open=1;		//��
				Servo_SetAngle4(PWM_Open);	
				count++;
			}
		}
		OSTimeDly(10);
    }
}

/**
 * @brief       �����������
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Battery_task(void *p_arg)
{
    while (1)
    {
		Clear_Buffer(1);
		Uart1_SendStr("\x01\x04");
		Uart1_Send00("\x00");
		Uart1_SendStr("\x01");
		Uart1_Send00("\x00");
		Uart1_SendStr("\x01\x60\x0A");
		
		OSTimeDly(100);
		
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
void Light_task(void *p_arg)
{
    while (1)
    {
		Lux=Get_Adc_Average(ADC_CHANNEL_10,20);				//��ȡADCֵ
		Lux=(4050-Lux) / 10;
		if(Lux<=0)	Lux=0;
		
		if(Lux<70.0)  	LED_Bule = 1;			//����ǿС��100ʱ�������ƴ�
		else			LED_Bule = 0;
		
		OSTimeDly(10);
    }
}

/**
 * @brief       �����������ͺ�LED��˸����
 * @param       p_arg : �������(δ�õ�)
 * @retval      ��
 */
void Beled_task(void *p_arg)
{
    while (1)
    {
		if(get_mes==1)
		{
			for(jian=0;jian<50;jian++)
			{
				BEEP=0;
				OSTimeDly(3);
				BEEP=1;
				OSTimeDly(3);
			}
			LED_Red=~LED_Red;
		}
		else
		{
			LED_Red=0;
		}
		OSTimeDly(10);
    }
}
