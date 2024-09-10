#include "led.h"

  GPIO_InitTypeDef GPIO_Initure;
void BEEP_MY(void)
{
  
    __HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOD时钟
	
    GPIO_Initure.Pin=GPIO_PIN_11; //PD11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);	//PD11置1 
}
