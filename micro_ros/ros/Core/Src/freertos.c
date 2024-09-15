/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include <motor/motor.h>				//电机
#include <oled/oled.h>					//oled显示�?
#include <JY61P/jy61p.h>				//jy61p姿�?�测�?
#include <encoder/encoder.h>			//编码�?
#include <Robotic_arm/robotic_arm.h>	//机械�?
#include <Kinematics/Kinematics.h>		//odom里程计测�?

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <micro_ros_utilities/type_utilities.h>
#include <micro_ros_utilities/string_utilities.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
#include <std_msgs/msg/string.h>
#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/detail/header__struct.h>
#include <nav_msgs/msg/detail/odometry__struct.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */
typedef struct PID {
		float  Kp;         //  Proportional Const  P系数
		float  Ki;           //  Integral Const      I系数
		float  Kd;         //  Derivative Const    D系数

		float  PrevError ;          //  Error[-2]
		float  LastError;          //  Error[-1]
		float  Error;              //  Error[0 ]
		float  DError;            //pid->Error - pid->LastError
		float  SumError;           //  Sums of Errors

		float  output;

		float  Integralmax;      //积分项的�?大�??
		float  outputmax;        //输出项的�?大�??
} PID;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);vTaskDelete(NULL);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
char en1[20];
char en2[20];
extern int start_sign = 0;
int oled_begin_flag = 0;
#define STRING_LEN 200
#define pi 3.14159
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

rcl_publisher_t hx_publisher;//测试�?
std_msgs__msg__Int32  hx_send_msg;
rcl_subscription_t hx_subscriber;
rclc_executor_t hx_executor;
std_msgs__msg__Int32 hx_get_msg;

rcl_publisher_t imu_publisher;//imu数据
std_msgs__msg__String imu_send_msg;
char string_memory[STRING_LEN];

rcl_publisher_t arm_publisher;//机械臂控�?
std_msgs__msg__String  arm_send_msg;
rcl_subscription_t arm_subscriber;
rclc_executor_t arm_executor;
std_msgs__msg__String arm_get_msg;
char arm_getdata[100];

rcl_subscription_t cmd_subscriber;//键盘控制
rclc_executor_t cmd_executor;
geometry_msgs__msg__Twist cmd_get_msg;
rcl_publisher_t odom_publisher;   // 用于发布机器人的里程计信息（Odom�?
nav_msgs__msg__Odometry odom_msg; // 机器人的里程计信�?

int cmd_getFlag = 0;
float ratio = 3.0f ;   //转换比例，执行�?�度调整比例48.78f
float D = 0.205f ;    //两轮间距，单位是m 0.205f
float linear_temp=0,angular_temp=0;
float left_speed=0,right_speed=0;
float left_output=0,right_output=0;
PID speedpid;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 5000 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for imuTask */
osThreadId_t imuTaskHandle;
uint32_t imuTaskBuffer[ 256 ];
osStaticThreadDef_t imuTaskControlBlock;
const osThreadAttr_t imuTask_attributes = {
  .name = "imuTask",
  .cb_mem = &imuTaskControlBlock,
  .cb_size = sizeof(imuTaskControlBlock),
  .stack_mem = &imuTaskBuffer[0],
  .stack_size = sizeof(imuTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for motorTask */
osThreadId_t motorTaskHandle;
uint32_t motorTaskBuffer[ 256 ];
osStaticThreadDef_t motorTaskControlBlock;
const osThreadAttr_t motorTask_attributes = {
  .name = "motorTask",
  .cb_mem = &motorTaskControlBlock,
  .cb_size = sizeof(motorTaskControlBlock),
  .stack_mem = &motorTaskBuffer[0],
  .stack_size = sizeof(motorTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for oledTask */
osThreadId_t oledTaskHandle;
uint32_t oledTaskBuffer[ 256 ];
osStaticThreadDef_t oledTaskControlBlock;
const osThreadAttr_t oledTask_attributes = {
  .name = "oledTask",
  .cb_mem = &oledTaskControlBlock,
  .cb_size = sizeof(oledTaskControlBlock),
  .stack_mem = &oledTaskBuffer[0],
  .stack_size = sizeof(oledTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);

void micro_ros_init(void);
void hx_ros_init(void);
void imu_ros_init(void);
void arm_ros_init(void);
void cmd_ros_init(void);
void odom_getandsend(void);

void PID_oled(void);//oled PID测试
void odom_oled(void);//oled 里程计测�?

float PID_Incremental_Calc(PID *pid, float Target_val, float Actual_val)
{
	pid->Error = Target_val- Actual_val;

	pid->output  +=  pid->Kp* ( pid->Error - pid->LastError )+
					 pid->Ki* pid->Error +
					 pid->Kd* ( pid->Error +  pid->PrevError - 2*pid->LastError);

	pid->PrevError = pid->LastError;
	pid->LastError = pid->Error;

	if(pid->output > pid->outputmax )    pid->output = pid->outputmax;
	if(pid->output < - pid->outputmax )  pid->output = -pid->outputmax;

	return pid->output ;   //输出为pwm�?
}

//PID初始�?
void PID_Init(PID *pid, float Kp , float Ki , float Kd , float Limit_value)
{
	pid->Kp= Kp;
	pid->Ki= Ki;
	pid->Kd= Kd;

	pid->PrevError =pid->LastError = pid->Error =pid->SumError= pid->output =  0;
	pid->Integralmax = pid->outputmax  = Limit_value;
}

#include "stdio.h"
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

void Uart6_SendStr(char*SendBuf)//串口6打印数据(这个无法发�??0x00)
{
	while(*SendBuf)
	{
	  while((USART6->SR&0X40)==0);//等待发�?�完�???
    USART6->DR = (unsigned char) *SendBuf;
		SendBuf++;
	}
}
// Implementation example:
void subscription_callback(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
//  printf("msg Received: %d\r\n", hx_get_msg.data);
}

void subscription_callback_arm(const void * msgin)//机械臂控�???
{
  // Cast received message to used type
  const std_msgs__msg__String * msg = (const std_msgs__msg__String *)msgin;
//  printf("arm Received: %s\r\n",arm_getdata);
}

void subscription_callback_cmd(const void * msgin)//键盘控制
{
  // Cast received message to used type
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
  cmd_getFlag = 1;
//  printf("\r\nlinear:  x: %lf\r\n"
//		     "         y: %lf\r\n"
//			 "         z: %lf\r\n", cmd_get_msg.linear.x
//								  , cmd_get_msg.linear.y
//								  , cmd_get_msg.linear.z);
//  printf("\r\nangular: x: %lf\r\n"
//			 "         y: %lf\r\n"
//		  	 "         z: %lf\r\n", cmd_get_msg.angular.x
//								  , cmd_get_msg.angular.y
//								  , cmd_get_msg.angular.z);
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartImuTask(void *argument);
void StartMotorTask(void *argument);
void StartOledTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of imuTask */
  imuTaskHandle = osThreadNew(StartImuTask, NULL, &imuTask_attributes);

  /* creation of motorTask */
  motorTaskHandle = osThreadNew(StartMotorTask, NULL, &motorTask_attributes);

  /* creation of oledTask */
  oledTaskHandle = osThreadNew(StartOledTask, NULL, &oledTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

//	Uart6_SendStr("{#000P1500T1000!#001P1300T1000!#002P1020T1000!#003P1100T1000!#004P1500T1000!}");//机械臂初始位�???
	Uart6_SendStr("{#000P1500T1000!#001P2500T1000!#002P0500T1000!#003P0800T1000!#004P1500T1000!}");
	micro_ros_init();

	// micro-ROS app
	hx_ros_init();//测试�???
	imu_ros_init();
	arm_ros_init();
	cmd_ros_init();

	start_sign = 1;
	for(;;)
	{
		if (!rmw_uros_epoch_synchronized()){
			rmw_uros_sync_session(100);
			// 如果时间同步成功，则将当前时间设置为MicroROS代理的时间，并输出调试信息�??
//			delay(10);
		}
		//test
//		RCSOFTCHECK(rcl_publish(&hx_publisher, &hx_send_msg, NULL));//测试�???
//		hx_send_msg.data++;

		//imu
		sprintf(imu_send_msg.data.data, "'\n'acc: %f/%f/%f"
									    "'\n'gyr: %f/%f/%f"
									    "'\n'ang: %f/%f/%f", acc_x, acc_y, acc_z
														   , gyro_x, gyro_y, gyro_z
														   , angle_x, angle_y, angle_z);
		imu_send_msg.data.size = strlen(imu_send_msg.data.data);
		RCSOFTCHECK(rcl_publish(&imu_publisher, &imu_send_msg, NULL));

		//odom
		odom_getandsend();

		rclc_executor_spin_some(&hx_executor, RCL_MS_TO_NS(10));
		rclc_executor_spin_some(&arm_executor, RCL_MS_TO_NS(10));
		rclc_executor_spin_some(&cmd_executor, RCL_MS_TO_NS(10));
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartImuTask */
/**
* @brief Function implementing the imuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartImuTask */
void StartImuTask(void *argument)
{
  /* USER CODE BEGIN StartImuTask */
  /* Infinite loop */
  for(;;)
  {
	get_data();//JY61P获取数据
	if(arm_getdata[0] != '\0'){
		Uart6_SendStr(arm_getdata);
		memset(arm_getdata, 0, sizeof(arm_getdata));
	}
    osDelay(10);
  }
  /* USER CODE END StartImuTask */
}

/* USER CODE BEGIN Header_StartMotorTask */
/**
* @brief Function implementing the motorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotorTask */
void StartMotorTask(void *argument)
{
  /* USER CODE BEGIN StartMotorTask */
  /* Infinite loop */
  int nomsg = 0;
  for(;;)
  {
	  if(cmd_getFlag == 1){
		  angular_temp = cmd_get_msg.angular.z ; //获取/cmd_vel的角速度,rad/s
		  linear_temp = cmd_get_msg.linear.x ;   //获取/cmd_vel的线速度.m/s
		  //将转换好的小车�?�度分量为左右轮速度
		  left_speed = (linear_temp - 0.5f*angular_temp*D *10)*ratio ;//运动学�?�解
		  right_speed = (linear_temp + 0.5f*angular_temp*D *10)*ratio ;

		  if(left_speed > 4.5)		left_speed =  4.5;
		  else if(left_speed < -4.5)	left_speed = -4.5;
		  if(right_speed > 5)		right_speed =  4.5;
		  else if(right_speed < -4.5)	right_speed = -4.5;

	      left_output = PID_Incremental_Calc(&speedpid, left_speed, motor1.speed);
	      right_output = PID_Incremental_Calc(&speedpid, right_speed, motor2.speed);

		  left_motor_control(left_speed * 22.2);
		  right_motor_control(right_speed * 22.2);

//		  left_motor_control(left_output);
//		  right_motor_control(right_output);

		  nomsg = 0;
		  cmd_getFlag = 0;
	  }
	  else{
		  nomsg ++;
		  if(nomsg >= 100){
			  left_output = left_speed = right_output = right_speed = 0;
			  left_motor_control(0);
			  right_motor_control(0);
		  }
	  }
    osDelay(5);
  }
  /* USER CODE END StartMotorTask */
}

/* USER CODE BEGIN Header_StartOledTask */
/**
* @brief Function implementing the oledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOledTask */
void StartOledTask(void *argument)
{
  /* USER CODE BEGIN StartOledTask */
  /* Infinite loop */
  for(;;)
  {
	  if(start_sign == 1){
		  PID_oled();
//		  odom_oled();
	  }
    osDelay(50);
  }
  /* USER CODE END StartOledTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void micro_ros_init(void){
	 printf("hello mirco_ros\r\n");
		  rmw_uros_set_custom_transport(
		    true,
		    (void *) &huart2,
		    cubemx_transport_open,
		    cubemx_transport_close,
		    cubemx_transport_write,
		    cubemx_transport_read);

		  rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
		  freeRTOS_allocator.allocate = microros_allocate;
		  freeRTOS_allocator.deallocate = microros_deallocate;
		  freeRTOS_allocator.reallocate = microros_reallocate;
		  freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

		  if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
		      printf("Error on default allocators (line %d)\n", __LINE__);
		  }

		  allocator = rcl_get_default_allocator();

		  //create init_options
		  rclc_support_init(&support, 0, NULL, &allocator);

		  // create node
		  rclc_node_init_default(&node, "cubemx_node", "", &support);
}

void hx_ros_init(void){
	// create publisher
	rclc_publisher_init_default(
	&hx_publisher,
	&node,
	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
	"cubemx_publisher");
	hx_send_msg.data = 0;

	const char * subscriber_name = "hx_topic";
	// Initialize a reliable subscriber
	rcl_ret_t rc = rclc_subscription_init_default(
	  &hx_subscriber, &node,
	  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32), subscriber_name);
	if (RCL_RET_OK != rc) {
		 printf("Error subscription_init (line %d) (ret %d)\r\n", __LINE__,rc);
		 while(1){
			 NVIC_SystemReset();
			 osDelay(200);
		 }
	}
	RCCHECK(rclc_executor_init(&hx_executor, &support.context, 1, &allocator));
	RCCHECK(rclc_executor_add_subscription(&hx_executor, &hx_subscriber, &hx_get_msg, &subscription_callback, ON_NEW_DATA));
}

void imu_ros_init(void){
	imu_send_msg.data.data = &string_memory[0];
	imu_send_msg.data.size = 0;
	imu_send_msg.data.capacity = STRING_LEN;

	// create publisher
	rclc_publisher_init_default(
	&imu_publisher,
	&node,
	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
	"imu_publisher");
}

void arm_ros_init(void){
	arm_get_msg.data.data = &arm_getdata[0];
	arm_get_msg.data.size = 0;
	arm_get_msg.data.capacity = 100;

	const char * arm_subscriber_name = "arm_topic";
	// Initialize a reliable subscriber
	rcl_ret_t rc_arm = rclc_subscription_init_default(
	  &arm_subscriber, &node,
	  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), arm_subscriber_name);
	if (RCL_RET_OK != rc_arm) {
		 printf("Error subscription_init (line %d) (ret %d)\n", __LINE__,rc_arm);
		 while(1){
			 osDelay(200);
		 }
	}
	RCCHECK(rclc_executor_init(&arm_executor, &support.context, 1, &allocator));
	RCCHECK(rclc_executor_add_subscription(&arm_executor, &arm_subscriber, &arm_get_msg, &subscription_callback_arm, ON_NEW_DATA));

//	Uart6_SendStr("{#000P2000T1000!#001P1140T1000!#002P0500T1000!#003P1780T1000!#004P1500T1000!}");//机械臂初始位�???
}

void cmd_ros_init(void){
	odom_msg.header.frame_id = micro_ros_string_utilities_set(odom_msg.header.frame_id, "odom");
	odom_msg.child_frame_id = micro_ros_string_utilities_set(odom_msg.child_frame_id, "base_link");

	// create publisher
	rclc_publisher_init_default(
	&odom_publisher,
	&node,
	ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry),
	"odom");

	const char * cmd_subscriber_name = "cmd_vel";
	// Initialize a reliable subscriber
	rcl_ret_t rc_cmd = rclc_subscription_init_default(
	  &cmd_subscriber, &node,
	  ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), cmd_subscriber_name);
	if (RCL_RET_OK != rc_cmd) {
		 printf("Error subscription_init (line %d) (ret %d)\n", __LINE__,rc_cmd);
		 while(1){
			 osDelay(200);
		 }
	}
	RCCHECK(rclc_executor_init(&cmd_executor, &support.context, 1, &allocator));
	RCCHECK(rclc_executor_add_subscription(&cmd_executor, &cmd_subscriber, &cmd_get_msg, &subscription_callback_cmd, ON_NEW_DATA));

	PID_Init(&speedpid, 20, 10, 0, 99.9);//P I D 速度�?�?
}

unsigned long previousMillis = 0; // 上一次打印的时间
unsigned long interval = 50;      // 间隔时间，单位为毫秒
void odom_getandsend(void){
    // 用于获取当前的时间戳，并将其存储在消息的头部�?
    int64_t stamp = rmw_uros_epoch_millis();
    // 获取机器人的位置和�?�度信息，并将其存储在一个ROS消息（odom_msg）中
    odom_t odom = *get_odom();
    odom_msg.header.stamp.sec = (int32_t)(stamp / 1000); // 秒部�?
    odom_msg.header.stamp.nanosec = (uint32_t)((stamp % 1000) * 1000000); // 纳秒部分
    odom_msg.pose.pose.position.x = odom.x;
    odom_msg.pose.pose.position.y = odom.y;
    odom_msg.pose.pose.orientation.w = odom.quaternion.w;
    odom_msg.pose.pose.orientation.x = odom.quaternion.x;
    odom_msg.pose.pose.orientation.y = odom.quaternion.y;
    odom_msg.pose.pose.orientation.z = odom.quaternion.z;

    odom_msg.twist.twist.angular.z = odom.angular_speed;
    odom_msg.twist.twist.linear.x = odom.linear_speed;

    rcl_publish(&odom_publisher, &odom_msg, NULL);
}

void PID_oled(void){
	if(oled_begin_flag == 0){
		OLED_ShowString(0, 0, "lspeed:", 16, 0);
		OLED_ShowString(70, 0, "rspeed:", 16, 0);
		oled_begin_flag = 1;
	}

	if(motor1.speed >= 0){
	  OLED_ShowChar(0, 2, ' ', 16, 0);
	  OLED_Showdecimal(10, 2, motor1.speed, 1, 4, 16, 0);
	}else{
	  OLED_ShowChar(0, 2, '-', 16, 0);
	  OLED_Showdecimal(10, 2, -motor1.speed, 1, 4, 16, 0);
	}
	if(left_speed >= 0){
	  OLED_ShowChar(0, 4, ' ', 16, 0);
	  OLED_Showdecimal(10, 4, left_speed, 1, 4, 16, 0);
	}else{
	  OLED_ShowChar(0, 4, '-', 16, 0);
	  OLED_Showdecimal(10, 4, -left_speed, 1, 4, 16, 0);
	}
	if(left_output >= 0){
	  OLED_ShowChar(0, 6, ' ', 16, 0);
	  OLED_Showdecimal(10, 6, left_output, 2, 3, 16, 0);
	}else{
	  OLED_ShowChar(0, 6, '-', 16, 0);
	  OLED_Showdecimal(10, 6, -left_output, 2, 3, 16, 0);
	}


	if(motor2.speed >= 0){
	  OLED_ShowChar(70, 2, ' ', 16, 0);
	  OLED_Showdecimal(80, 2, motor2.speed, 1, 4, 16, 0);
	}else{
	  OLED_ShowChar(70, 2, '-', 16, 0);
	  OLED_Showdecimal(80, 2, -motor2.speed, 1, 4, 16, 0);
	}
	if(right_speed >= 0){
	  OLED_ShowChar(70, 4, ' ', 16, 0);
	  OLED_Showdecimal(80, 4, right_speed, 1, 4, 16, 0);
	}else{
	  OLED_ShowChar(70, 4, '-', 16, 0);
	  OLED_Showdecimal(80, 4, -right_speed, 1, 4, 16, 0);
	}
	if(right_output >= 0){
	  OLED_ShowChar(70, 6, ' ', 16, 0);
	  OLED_Showdecimal(80, 6, right_output, 2, 3, 16, 0);
	}else{
	  OLED_ShowChar(70, 6, '-', 16, 0);
	  OLED_Showdecimal(80, 6, -right_output, 2, 3, 16, 0);
	}
}

void odom_oled(void){
	if(oled_begin_flag == 0){
		OLED_ShowString(0, 0, "linear:", 16, 0);
		OLED_ShowString(70, 0, "angle :", 16, 0);
		oled_begin_flag = 1;
	}

	if(line_speed >= 0){
	  OLED_ShowChar(0, 2, ' ', 16, 0);
	  OLED_Showdecimal(10, 2, line_speed, 1, 4, 16, 0);
	}else{
	  OLED_ShowChar(0, 2, '-', 16, 0);
	  OLED_Showdecimal(10, 2, -line_speed, 1, 4, 16, 0);
	}

	if(angle_speed >= 0){
	  OLED_ShowChar(70, 2, ' ', 16, 0);
	  OLED_Showdecimal(80, 2, angle_speed, 2, 3, 16, 0);
	}else{
	  OLED_ShowChar(70, 2, '-', 16, 0);
	  OLED_Showdecimal(80, 2, -angle_speed, 2, 3, 16, 0);
	}

}
/* USER CODE END Application */

