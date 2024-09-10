#include "stm32f10x.h"                  // Device header
#include "delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Key_Init2(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);
		delay_ms(20);
		KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0);
		delay_ms(20);
		KeyNum = 2;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0);
		delay_ms(20);
		KeyNum = 3;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0);
		delay_ms(20);
		KeyNum = 4;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 0);
		delay_ms(20);
		KeyNum = 5;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0);
		delay_ms(20);
		KeyNum = 6;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0);
		delay_ms(20);
		KeyNum = 7;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0);
		delay_ms(20);
		KeyNum = 8;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) == 0);
		delay_ms(20);
		KeyNum = 9;
	}
	return KeyNum;
}

