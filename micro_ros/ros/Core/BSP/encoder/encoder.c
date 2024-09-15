#include <encoder/encoder.h>

Motor motor1;
Motor motor2;

void Encoder_Init(void)
{
	HAL_TIM_Base_Start_IT(&GAP_TIM);                      		 //开启10ms定时器中断
    HAL_TIM_Encoder_Start(&ENCODER_1_TIM, TIM_CHANNEL_ALL);      //开启编码器定时器左
    HAL_TIM_Encoder_Start(&ENCODER_2_TIM, TIM_CHANNEL_ALL);      //开启编码器定时器右
    __HAL_TIM_ENABLE_IT(&ENCODER_1_TIM,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
    __HAL_TIM_ENABLE_IT(&ENCODER_2_TIM,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
    __HAL_TIM_SET_COUNTER(&ENCODER_1_TIM, 10000);                	 //编码器定时器初始值设定为10000
    __HAL_TIM_SET_COUNTER(&ENCODER_2_TIM, 10000);                	 //编码器定时器初始值设定为10000
//    motor1.CaptureNumber = motor2.CaptureNumber = 0;                  //结构体内容初始化
//    motor1.Direction = motor2.Direction = 0;
//    motor1.speed = motor2.speed = 0;

    motor1.lastCount = motor2.lastCount = 0;                                   //结构体内容初始化
    motor1.totalCount = motor2.totalCount = 0;
    motor1.overflowNum = motor2.overflowNum = 0;
    motor1.speed = motor2.speed = 0;
    motor1.direct = motor2.direct = 0;
}
