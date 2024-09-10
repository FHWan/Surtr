#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"
#include "./BSP/adc/adc.h"
#include "./BSP/BEEPLED/gpio.h"
#include "./BSP/servo/servo.h"
#include "./BSP/MPU6050/MPU6050.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     /* 中断优先级分组2 */
    delay_init(144);                                    /* 延时初始化 */
    usart_init(9600);       //初始化USART1 TX PA9  RX PA10    电量计 电量计反面从左到右 TX RX GND (SET)
    usart2_init(115200);    //初始化USART2 TX PA2  RX PA3   EC20
    usart3_init(115200);    //初始化USART3 TX PB10 RX PB11     人脸识别
    delay_ms(1000);
    while(MPU_Init())       //初始化MPU6050    PB6 SCL   PB7 SDA
        delay_ms(200);
    ADC_Function_Init();    //初始化ADC1通道4,光强 PA4
    BEEPLED_Init();         //初始化蜂鸣器和灯        PE0蜂鸣器    PB0白光     PB1红光     PA1按键连3v
    TIM4_PWMOut_Init( 100-1, 14400-1 );           //初始化舵机PD12
    TIM_SetCompare1(TIM4,85);    //关闭
    my_mem_init(SRAMIN);                                /* 初始化内部SRAM内存池 */
    freertos_demo();                                    /* 运行FreeRTOS例程 */
}


