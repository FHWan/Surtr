#include <motor/motor.h>

void left_motor_control(int speed){
	if(speed == 0){
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);	//设置占空比为0
		return 0;
	}
	else if(speed > 0){
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
	}
	else if(speed < 0){
		speed = -speed;
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	}if(speed >= 100)	speed = 100;

	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,speed);	//设置占空比
}

void right_motor_control(int speed){
	if(speed == 0){
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);	//设置占空比为0
		return 0;
	}
	else if(speed > 0){
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);//使能
	}
	else if(speed < 0){
		speed = -speed;
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);//使能
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	}if(speed >= 100)	speed = 100;

	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,speed);	//设置占空比
}
