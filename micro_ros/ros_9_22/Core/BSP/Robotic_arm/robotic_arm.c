/*
 * robotic_arm.c
 *
 *  Created on: Sep 7, 2024
 *      Author: Lenovo
 */
#include <Robotic_arm/robotic_arm.h>
#include <string.h>
uint8_t rx_buff_arm;
char armdata[20];

void CopeSerialData_arm(unsigned char ucData_arm)
{
	static unsigned char ucRxBuffer_arm[30];
	static unsigned char ucRxCnt_arm = 0;

	ucRxBuffer_arm[ucRxCnt_arm++]=ucData_arm;	//将收到的数据存入缓冲区中
//	if (ucRxBuffer_arm[0]!=0x23) //数据头不对，则重新开始寻找0x23数据头
//	{
//		ucRxCnt_arm=0;
//		return;
//	}
	if(ucData_arm>=30) ucData_arm =0;
	if (ucRxBuffer_arm[ucRxCnt_arm-1] != 0x21) {return;}//数据尾不为0x21，则返回
	else
	{
		memcpy(armdata,&ucRxBuffer_arm[0],ucRxCnt_arm-1);
		ucRxCnt_arm=0;//清空缓存区
	}
}
