/******************* (C) COPYRIGHT 2015-20~~ Xiluna Tech ************************
 * 作者    ：Xiluna Tech
 * 文件名  ：main.c
 * 描述    ：主循环
 * 官网    ：http://xiluna.com/
 * 公众号  ：XilunaTech
*********************************************************************************/
#include "Head_File.h"
#define START_TASK_PRIO 3						                     // 任务优先级
#define START_STK_SIZE 1024						                   // 任务堆栈大小
OS_TCB StartTaskTCB;							                       // 任务控制块
CPU_STK START_TASK_STK[START_STK_SIZE];					         // 任务堆栈
void start_task(void *p_arg);						                 // 任务函数

//IMU任务
#define IMU_TASK_PRIO 4						
#define IMU_STK_SIZE 1024						
OS_TCB IMUTaskTCB;				
CPU_STK IMU_TASK_STK[IMU_STK_SIZE];					
void IMU_task(void *p_arg);

//姿态环任务
#define Attitude_TASK_PRIO 5						
#define Attitude_STK_SIZE 1024						
OS_TCB AttitudeTaskTCB;							
CPU_STK Attitude_TASK_STK[Attitude_STK_SIZE];					
void Attitude_task(void *p_arg);

//融合任务
#define Combine_TASK_PRIO 7					
#define Combine_STK_SIZE 512					
OS_TCB CombineTaskTCB;							
CPU_STK Combine_TASK_STK[Combine_STK_SIZE];					
void Combine_task(void *p_arg);

//位置环任务
#define Position_TASK_PRIO 6						
#define Position_STK_SIZE 512						
OS_TCB PositionTaskTCB;							
CPU_STK Position_TASK_STK[Position_STK_SIZE];					
void Position_task(void *p_arg);

//TOF任务
#define TOF_TASK_PRIO 9					
#define TOF_STK_SIZE 512						
OS_TCB TOFTaskTCB;							
CPU_STK TOF_TASK_STK[TOF_STK_SIZE];					
void TOF_task(void *p_arg);

//VIO任务
#define VIO_TASK_PRIO 8				
#define VIO_STK_SIZE 512						
OS_TCB VIOTaskTCB;							
CPU_STK VIO_TASK_STK[VIO_STK_SIZE];
void VIO_task(void *p_arg);

//PPM遥控数据接收任务
#define PPM_TASK_PRIO 14				
#define PPM_STK_SIZE 256						
OS_TCB PPMTaskTCB;							
CPU_STK PPM_TASK_STK[PPM_STK_SIZE];
void PPM_task(void *p_arg);

//光流数据接收任务
#define Flow_TASK_PRIO 10						
#define Flow_STK_SIZE	512						
OS_TCB FlowTaskTCB;							
CPU_STK Flow_TASK_STK[Flow_STK_SIZE];					
void Flow_task(void *p_arg);

//DataDeal任务
#define DataDeal_TASK_PRIO 12						
#define DataDeal_STK_SIZE 512						
OS_TCB DataDealTaskTCB;							
CPU_STK DataDeal_TASK_STK[DataDeal_STK_SIZE];					
void DataDeal_task(void *p_arg);


//Usart1toPC任务
#define Usart1toPC_TASK_PRIO 11					
#define Usart1toPC_STK_SIZE 512						
OS_TCB Usart1toPCTaskTCB;							
CPU_STK Usart1toPC_TASK_STK[Usart1toPC_STK_SIZE];					
void Usart1toPC_task(void *p_arg);

//电池电压任务
#define Battery_TASK_PRIO 13						
#define Battery_STK_SIZE 512						
OS_TCB BatteryTaskTCB;							
CPU_STK Battery_TASK_STK[Battery_STK_SIZE];					
void Battery_task(void *p_arg);



/**
 * @Description 主函数启动操作系统
 */	
int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	Systick_Init(168);																					// 时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);							// 中断分组配置
	delay_ms(1000);
	Load_config();                                          		// 配置用户信息
	Adc_Batteryinit();                                      		// 电池电压ADC初始化
	SPI3_Configuration();  																			// SPI3初始化
	IMU_HardwareInit();                                     		// IMU各个传感器寄存器配置
	PWM_Init();                                               	// pwm定时器初始化
	Uart4toTOF_Init(115200);                                    // MiNiTOF传感器串口打开
//	Uart4toTOF_Init(9600);                                      // Laser传感器串口打开
//	EXTIX_Init();
//	LED_Init();
	//	Timer5_Timinginit();                                    		// MS5611记录时间定时器
//	IIC_Init();                                                 // iic总线初始化
//	MS5611_Init();                                              // MS5611气压计初始化
	TIM1_Cap_Init(0XFFFF,168);	                                // 捕获PPM遥控信号
	Bluetooth_init();                                       		// 蓝牙串口 默认使用
	Usart6toVision_Init(230400);                               // Usart6接收T265数据
//	Usart6toLaserArray_Init(115200);                            // Usart6接收激光面阵数据 
	Usart5toFlow_Init(19200);                                   // Usart5接收光流数据
	KalmanFilter_Init(&XAxis,&YAxis,&ZAxis,&Barometer);					// KalmanFilter参数初始化
	Set_Cutoff_Frequency(200.0f, 50.0f,&VIO_Parameter);          // VIO速度巴特沃斯参数初始化
	Set_Cutoff_Frequency(200.0f, 25.0f,&RotateX_Parameter);       //光流旋转X巴特沃斯参数初始化
	Set_Cutoff_Frequency(200.0f, 25.0f,&RotateY_Parameter);       //光流旋转Y巴特沃斯参数初始化
	Set_Cutoff_Frequency(200.0f, 25.0f,&RotateZ_Parameter);       //光流旋转Z巴特沃斯参数初始化
	Set_Cutoff_Frequency(25.0f, 2.0f,&FlowX_Parameter);          // 光流速度巴特沃斯参数初始化
	Set_Cutoff_Frequency(25.0f, 2.0f,&FlowY_Parameter);          // 光流速度巴特沃斯参数初始化
	Set_Cutoff_Frequency(25.0f, 1.2f,&RotateFlowX_Parameter);       //光流旋转X巴特沃斯参数初始化
	Set_Cutoff_Frequency(25.0f, 1.2f,&RotateFlowY_Parameter);       //光流旋转Y巴特沃斯参数初始化
//	Set_Cutoff_Frequency(200, 10,&Flow_Parameter);              // 光流速度巴特沃斯参数初始化
//	WaitBaroInitOffset();																		    // 等待气压初始化高度完成  
//	General_Gpioinit();                                     		// 通用GPIO初始化     
    Flight_Remote_Control.FlightHeadingMode = Heading;
	DataCombineflag = Data_Follow;//Data_Flow;
	RT_Info.VioAbnormal = false;
	OSInit(&err);																								// 初始化UCOSIII
	OS_CRITICAL_ENTER();																				// 进入临界区
	OSTaskCreate(																								// 创建开始任务
		(OS_TCB*)&StartTaskTCB,																		// 任务控制块
		(CPU_CHAR*)"start task", 																	// 任务名字
		(OS_TASK_PTR)start_task, 																	// 任务函数
		(void*)0,																									// 传递给任务函数的参数
		(OS_PRIO)START_TASK_PRIO,																	// 任务优先级
		(CPU_STK*)&START_TASK_STK[0],															// 任务堆栈基地址
		(CPU_STK_SIZE)START_STK_SIZE/10,													// 任务堆栈深度限位
		(CPU_STK_SIZE)START_STK_SIZE,															// 任务堆栈大小
		(OS_MSG_QTY)0,																						// 任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
		(OS_TICK)0,																								// 当使能时间片轮转时的时间片长度，为0时为默认长度，
		(void*)0,																									// 用户补充的存储区
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,					// 任务选项
		(OS_ERR*)&err																							// 存放该函数错误时的返回值
		);
	OS_CRITICAL_EXIT();																					// 退出临界区
	OSStart(&err);																							// 开启UCOSIII
	while(1);
}

/**
 * @Description 开始任务函数
 */
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);											// 统计任务
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN											// 如果使能了测量中断关闭时间
	CPU_IntDisMeasMaxCurReset();	
#endif
	//默认打开
#if OS_CFG_SCHED_ROUND_ROBIN_EN											// 当使用时间片轮转的时候
	//使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif

	OS_CRITICAL_ENTER();															// 进入临界区
	OSTaskCreate(																			// 创建姿态IMU任务
		(OS_TCB*)&IMUTaskTCB,
		(CPU_CHAR*)"IMU task",
		(OS_TASK_PTR )IMU_task,
		(void*)0,
		(OS_PRIO)IMU_TASK_PRIO,
		(CPU_STK*)&IMU_TASK_STK[0],
		(CPU_STK_SIZE)IMU_STK_SIZE/10,
		(CPU_STK_SIZE)IMU_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建姿态任务
		(OS_TCB*)&AttitudeTaskTCB,
		(CPU_CHAR*)"Attitude task",
		(OS_TASK_PTR )Attitude_task,
		(void*)0,
		(OS_PRIO)Attitude_TASK_PRIO,
		(CPU_STK*)&Attitude_TASK_STK[0],
		(CPU_STK_SIZE)Attitude_STK_SIZE/10,
		(CPU_STK_SIZE)Attitude_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建融合Combine任务
		(OS_TCB*)&CombineTaskTCB,
		(CPU_CHAR*)"Combine task",
		(OS_TASK_PTR )Combine_task,
		(void*)0,
		(OS_PRIO)Combine_TASK_PRIO,
		(CPU_STK*)&Combine_TASK_STK[0],
		(CPU_STK_SIZE)Combine_STK_SIZE/10,
		(CPU_STK_SIZE)Combine_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建位置Position任务
		(OS_TCB*)&PositionTaskTCB,
		(CPU_CHAR*)"Position task",
		(OS_TASK_PTR )Position_task,
		(void*)0,
		(OS_PRIO)Position_TASK_PRIO,
		(CPU_STK*)&Position_TASK_STK[0],
		(CPU_STK_SIZE)Position_STK_SIZE/10,
		(CPU_STK_SIZE)Position_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建光流数据任务
		(OS_TCB*)&FlowTaskTCB,
		(CPU_CHAR*)"Flow task",
		(OS_TASK_PTR )Flow_task,
		(void*)0,
		(OS_PRIO)Flow_TASK_PRIO,
		(CPU_STK*)&Flow_TASK_STK[0],
		(CPU_STK_SIZE)Flow_STK_SIZE/10,
		(CPU_STK_SIZE)Flow_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建PPM遥控数据接收任务
		(OS_TCB*)&PPMTaskTCB,
		(CPU_CHAR*)"PPM task",
		(OS_TASK_PTR )PPM_task,
		(void*)0,
		(OS_PRIO)PPM_TASK_PRIO,
		(CPU_STK*)&PPM_TASK_STK[0],
		(CPU_STK_SIZE)PPM_STK_SIZE/10,
		(CPU_STK_SIZE)PPM_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建VIO数据接收任务
		(OS_TCB*)&VIOTaskTCB,
		(CPU_CHAR*)"VIO task",
		(OS_TASK_PTR )VIO_task,
		(void*)0,
		(OS_PRIO)VIO_TASK_PRIO,
		(CPU_STK*)&VIO_TASK_STK[0],
		(CPU_STK_SIZE)VIO_STK_SIZE/10,
		(CPU_STK_SIZE)VIO_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建数据处理DataDeal任务
		(OS_TCB*)&DataDealTaskTCB,
		(CPU_CHAR*)"DataDeal task",
		(OS_TASK_PTR )DataDeal_task,
		(void*)0,
		(OS_PRIO)DataDeal_TASK_PRIO,
		(CPU_STK*)&DataDeal_TASK_STK[0],
		(CPU_STK_SIZE)DataDeal_STK_SIZE/10,
		(CPU_STK_SIZE)DataDeal_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建数据发送Usart1toPC任务
		(OS_TCB*)&Usart1toPCTaskTCB,
		(CPU_CHAR*)"Usart1toPC task",
		(OS_TASK_PTR )Usart1toPC_task,
		(void*)0,
		(OS_PRIO)Usart1toPC_TASK_PRIO,
		(CPU_STK*)&Usart1toPC_TASK_STK[0],
		(CPU_STK_SIZE)Usart1toPC_STK_SIZE/10,
		(CPU_STK_SIZE)Usart1toPC_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建高度TOF任务
		(OS_TCB*)&TOFTaskTCB,
		(CPU_CHAR*)"TOF task",
		(OS_TASK_PTR )TOF_task,
		(void*)0,
		(OS_PRIO)TOF_TASK_PRIO,
		(CPU_STK*)&TOF_TASK_STK[0],
		(CPU_STK_SIZE)TOF_STK_SIZE/10,
		(CPU_STK_SIZE)TOF_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OSTaskCreate(																			// 创建电池电压Battery任务
		(OS_TCB*)&BatteryTaskTCB,
		(CPU_CHAR*)"Battery task",
		(OS_TASK_PTR )Battery_task,
		(void*)0,
		(OS_PRIO)Battery_TASK_PRIO,
		(CPU_STK*)&Battery_TASK_STK[0],
		(CPU_STK_SIZE)Battery_STK_SIZE/10,
		(CPU_STK_SIZE)Battery_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void*)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
		(OS_ERR*)&err
		);
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);			// 挂起开始任务
	OS_CRITICAL_EXIT();																// 离开临界区 
}



