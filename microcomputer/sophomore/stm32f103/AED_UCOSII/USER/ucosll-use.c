#include "ucosll-use.h"

#define BEEP 		PBout(7)	//BEEP
#define LED_Bule 	PAout(11)	//白光
#define LED_Red 	PAout(12)	//红光
#define PWM_Open 	21			//舵机开启
#define PWM_Close 	10			//舵机关闭

u8 lat[20]="31.6789801";
u8 lon[20]="119.9522227";
u8 data_len,datastr[20],send_jason[200];

bool warning;					//示警判断
bool k;							//按键判断，1按下，0无
bool get_mes=0;					//ec20数据获取 1为接收开，0为关
char *stry;
char manager_id[10];
char picture[30];
char identity[10];
char *start_index = 0;
char *end_index = 0;
char count = 0;	
int open;						//舵机开启标志位0关 1开	bool类型只有0和1，其他会爆栈，程序跑飞
int ec,se,jian;					//计数判断
u32 AD_LUX;
int Lux; 
float power;					//电池电量
float pitch,roll,yaw; 			//欧拉角
float distance;

//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	

/* EC20发送 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define EC20_SEND_TASK_PRIO                  1       /* EC20发送消息到服务器，优先级最高 */
#define EC20_SEND_STK_SIZE                   512    /* 堆栈大小 */
OS_STK EC20_SEND_TASK_STK[EC20_SEND_STK_SIZE];       /* 任务堆栈 */
void EC20_Send_task(void *pdata);                    /* 任务函数 */

/* EC20获取 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define EC20_GET_TASK_PRIO                  2       /* EC20获取小程序信息 */
#define EC20_GET_STK_SIZE                   128     /* 堆栈大小 */
OS_STK EC20_GET_TASK_STK[EC20_GET_STK_SIZE];        /* 任务堆栈 */
void EC20_Get_task(void *pdata);                    /* 任务函数 */

/* MPU6050 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define MPU6050_TASK_PRIO                  3       /* MPU6050 */
#define MPU6050_STK_SIZE                   128     /* 堆栈大小 */
OS_STK MPU6050_TASK_STK[MPU6050_STK_SIZE];         /* 任务堆栈 */
void Mpu6050_task(void *pdata);                    /* 任务函数 */

/* 舵机 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define SERVO_TASK_PRIO                  4       /* 舵机 */
#define SERVO_STK_SIZE                   128     /* 堆栈大小 */
OS_STK SERVO_TASK_STK[SERVO_STK_SIZE];           /* 任务堆栈 */
void Servo_task(void *pdata);                    /* 任务函数 */

/* 电量检测 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define BATTERY_TASK_PRIO                  5       /* 电量检测 */
#define BATTERY_STK_SIZE                   128     /* 堆栈大小 */
OS_STK BATTERY_TASK_STK[BATTERY_STK_SIZE];         /* 任务堆栈 */
void Battery_task(void *pdata);                    /* 任务函数 */

/* 光强检测 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define LIGHT_TASK_PRIO                  6       /* 光强检测 */
#define LIGHT_STK_SIZE                   128     /* 堆栈大小 */
OS_STK LIGHT_TASK_STK[LIGHT_STK_SIZE];           /* 任务堆栈 */
void Light_task(void *pdata);                    /* 任务函数 */

/* 蜂鸣器报警和红LED闪烁 任务 配置
 * 包括: 任务优先级 堆栈大小 等
 */
#define BELED_TASK_PRIO                  7       /* 蜂鸣器报警和红LED闪烁，优先级最低 */
#define BELED_STK_SIZE                   128     /* 堆栈大小 */
OS_STK BELED_TASK_STK[BELED_STK_SIZE];           /* 任务堆栈 */
void Beled_task(void *pdata);                    /* 任务函数 */

void ucosll_init(void)
{
	OSInit();   
	OSTaskCreateExt((void(*)(void *) )start_task,               /* 任务函数 */
					(void *          )0,                        /* 传递给任务函数的参数 */
					(OS_STK *        )&START_TASK_STK[START_STK_SIZE - 1], /* 任务堆栈栈顶 */
					(INT8U           )START_TASK_PRIO,          /* 任务优先级 */
					(INT16U          )START_TASK_PRIO,          /* 任务ID，这里设置为和优先级一样 */
					(OS_STK *        )&START_TASK_STK[0],       /* 任务堆栈栈底 */
					(INT32U          )START_STK_SIZE,           /* 任务堆栈大小 */
					(void *          )0,                        /* 用户补充的存储区 */
					(INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP); /* 任务选项,为了保险起见，所有任务都保存浮点寄存器的值 */
	OSStart();	  	 
}

//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	pdata = pdata;
    OS_ENTER_CRITICAL();            /* 进入临界区(关闭中断) */
    
	/* EC20发送任务 */
    OSTaskCreateExt((void(*)(void *) )EC20_Send_task,
                    (void *          )0,						//传递一个空指针,EC20_Send_task不需要参数传入
                    (OS_STK *        )&EC20_SEND_TASK_STK[EC20_SEND_STK_SIZE - 1],
                    (INT8U           )EC20_SEND_TASK_PRIO,
                    (INT16U          )EC20_SEND_TASK_PRIO,
                    (OS_STK *        )&EC20_SEND_TASK_STK[0],
                    (INT32U          )EC20_SEND_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
    /* EC20获取任务 */
    OSTaskCreateExt((void(*)(void *) )EC20_Get_task,
                    (void *          )0,
                    (OS_STK *        )&EC20_GET_TASK_STK[EC20_GET_STK_SIZE - 1],
                    (INT8U           )EC20_GET_TASK_PRIO,
                    (INT16U          )EC20_GET_TASK_PRIO,
                    (OS_STK *        )&EC20_GET_TASK_STK[0],
                    (INT32U          )EC20_GET_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
    /* MPU6050任务 */
    OSTaskCreateExt((void(*)(void *) )Mpu6050_task,
                    (void *          )0,											
                    (OS_STK *        )&MPU6050_TASK_STK[MPU6050_STK_SIZE - 1],
                    (INT8U           )MPU6050_TASK_PRIO,
                    (INT16U          )MPU6050_TASK_PRIO,
                    (OS_STK *        )&MPU6050_TASK_STK[0],
                    (INT32U          )MPU6050_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* 舵机任务 */
    OSTaskCreateExt((void(*)(void *) )Servo_task,
                    (void *          )0,											
                    (OS_STK *        )&SERVO_TASK_STK[SERVO_STK_SIZE - 1],
                    (INT8U           )SERVO_TASK_PRIO,
                    (INT16U          )SERVO_TASK_PRIO,
                    (OS_STK *        )&SERVO_TASK_STK[0],
                    (INT32U          )SERVO_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* 电量检测任务 */
    OSTaskCreateExt((void(*)(void *) )Battery_task,
                    (void *          )0,											
                    (OS_STK *        )&BATTERY_TASK_STK[BATTERY_STK_SIZE - 1],
                    (INT8U           )BATTERY_TASK_PRIO,
                    (INT16U          )BATTERY_TASK_PRIO,
                    (OS_STK *        )&BATTERY_TASK_STK[0],
                    (INT32U          )BATTERY_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* 光强检测任务 */
    OSTaskCreateExt((void(*)(void *) )Light_task,
                    (void *          )0,											
                    (OS_STK *        )&LIGHT_TASK_STK[LIGHT_STK_SIZE - 1],
                    (INT8U           )LIGHT_TASK_PRIO,
                    (INT16U          )LIGHT_TASK_PRIO,
                    (OS_STK *        )&LIGHT_TASK_STK[0],
                    (INT32U          )LIGHT_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);
	/* 蜂鸣器报警和红LED闪烁任务 */
    OSTaskCreateExt((void(*)(void *) )Beled_task,
                    (void *          )0,											
                    (OS_STK *        )&BELED_TASK_STK[BELED_STK_SIZE - 1],
                    (INT8U           )BELED_TASK_PRIO,
                    (INT16U          )BELED_TASK_PRIO,
                    (OS_STK *        )&BELED_TASK_STK[0],
                    (INT32U          )BELED_STK_SIZE,
                    (void *          )0,
                    (INT16U          )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP);	
					
					
    OS_EXIT_CRITICAL();             /* 退出临界区(开中断) */
    OSTaskSuspend(START_TASK_PRIO); /* 挂起开始任务 */
}
/**
 * @brief       EC20发送任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void EC20_Send_task(void *p_arg)
{
    while (1)
    {
		OSTimeDly(2500);
		Clear_Buffer(3);
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
		OSTimeDly(100);
		printf(send_jason);
		memset(manager_id,'\0', sizeof(manager_id));
		memset(picture,'\0', sizeof(picture));
		memset(identity,'\0', sizeof(identity));
		Clear_Buffer(3);
		
		OSTimeDly(2500);
    }
}

/**
 * @brief       EC20获取任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void EC20_Get_task(void *p_arg)
{
    while (1)
    {
		stry=strstr((const char*)RxBuffer3,(const char*)"+QMTRECV: 0,0");
		if(stry!=NULL)
		{
			if((strstr((const char*)RxBuffer3,(const char*)"{\"id\":\"1\"}")!=NULL)&&(open==0))	
			{
				get_mes=1;
			}
			else if(strstr((const char*)RxBuffer3,(const char*)"{\"id\":\"0\"}")!=NULL)
			{
				open=0;		
				Servo_SetAngle(10);		//0关闭	90度
				LED_Red=0;
				get_mes=0;
			}
			
		}Clear_Buffer(3);
        OSTimeDly(10);
    }
}

/**
 * @brief       MPU6050任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Mpu6050_task(void *p_arg)
{
    while (1)
    {
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
		mpu_dmp_get_data(&pitch,&roll,&yaw); //计算得到俯仰角、横滚角、航向角

		if(((pitch>10)||(pitch<-10))||((roll>10)||(roll<-10)))
			warning=1;
		else
			warning=0;
		OSTimeDly(10);
    }
}

/**
 * @brief       舵机任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Servo_task(void *p_arg)
{
    while (1)
    {
		k=KEY_Scan(0);
		if((get_mes==1)&&(k==1))
		{
			open=1;		//开
			Servo_SetAngle(PWM_Open);	
			sprintf(identity,"Weixin");
			get_mes=0;
			count++;
		}
		else if((open==0)&&(k==1))
		{
			Uart1_SendStr("OK\r\n");
		}
		else if((open==1)&&(k==1))
		{
			open=0;		//关
			Servo_SetAngle(PWM_Close);
		}
		if (open==0)
		{
			if(strstr((const char*)RxBuffer1,(const char*)"Unknown")!=NULL)
			{
				sprintf(identity,"Unknown");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer1,"Unknown");
				end_index   = strstr(RxBuffer1,".jpg");
				strncat(picture, &RxBuffer1[start_index-RxBuffer1], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
				Clear_Buffer(1);
			
				open=1;		//开
				Servo_SetAngle(PWM_Open);
				count++;				
			}
			else if(strstr((const char*)RxBuffer1,(const char*)"fan")!=NULL)
			{
				sprintf(identity,"Admin");
				sprintf(manager_id,"fan");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer1,"fan");
				end_index   = strstr(RxBuffer1,".jpg");
				strncat(picture, &RxBuffer1[start_index-RxBuffer1], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
				Clear_Buffer(1);
				
				open=1;		//开
				Servo_SetAngle(PWM_Open);	
				count++;
			}
			else if(strstr((const char*)RxBuffer1,(const char*)"xzf")!=NULL)
			{
				sprintf(identity,"Admin");
				sprintf(manager_id,"xzf");
				memset(picture,'\0', sizeof(picture));
				start_index = strstr(RxBuffer1,"xzf");
				end_index   = strstr(RxBuffer1,".jpg");
				strncat(picture, &RxBuffer1[start_index-RxBuffer1], end_index - start_index + 4);  // 将源字符串中指定范围内的字符拼接到目标字符串
				Clear_Buffer(4);
				
				open=1;		//开
				Servo_SetAngle(PWM_Open);	
				count++;
			}
		}
		OSTimeDly(10);
    }
}

/**
 * @brief       电量检测任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
 */
void Battery_task(void *p_arg)
{
    while (1)
    {
		Clear_Buffer(2);
		Uart2_SendStr("\x01\x04");
		Uart2_Send00("\x00");
		Uart2_SendStr("\x01");
		Uart2_Send00("\x00");
		Uart2_SendStr("\x01\x60\x0A");
		
		OSTimeDly(100);
		
		if((RxBuffer2[0]=='\x01')&&(RxBuffer2[1]=='\x04')&&(RxBuffer2[2]=='\x02'))
		{
			power = RxBuffer2[3]*256 + RxBuffer2[4];
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
void Light_task(void *p_arg)
{
    while (1)
    {
		AD_LUX=Get_Adc_Average(ADC_Channel_5,20);				//获取ADC值
		Lux=(4050-AD_LUX) / 10;
//		Lux=(int)(39810*pow(2.71828,-0.01534*AD_LUX)+3467*pow(2.71828,-0.002379*AD_LUX));
		if(Lux<=0)	Lux=0;
		
		if(Lux<100.0)  	LED_Bule = 1;			//当光强小于100时，点亮灯带
		else			LED_Bule = 0;
		
		if(get_mes==1)	LED_Red=~LED_Red;
		OSTimeDly(10);
    }
}

/**
 * @brief       蜂鸣器报警和红LED闪烁任务
 * @param       p_arg : 传入参数(未用到)
 * @retval      无
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
				OSTimeDly(1);
				BEEP=1;
				OSTimeDly(1);
			}
		}
		else
		{
			LED_Red=0;
		}
		OSTimeDly(100);
    }
}

