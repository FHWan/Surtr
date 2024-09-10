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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     /* �ж����ȼ�����2 */
    delay_init(144);                                    /* ��ʱ��ʼ�� */
    usart_init(9600);       //��ʼ��USART1 TX PA9  RX PA10    ������ �����Ʒ�������� TX RX GND (SET)
    usart2_init(115200);    //��ʼ��USART2 TX PA2  RX PA3   EC20
    usart3_init(115200);    //��ʼ��USART3 TX PB10 RX PB11     ����ʶ��
    delay_ms(1000);
    while(MPU_Init())       //��ʼ��MPU6050    PB6 SCL   PB7 SDA
        delay_ms(200);
    ADC_Function_Init();    //��ʼ��ADC1ͨ��4,��ǿ PA4
    BEEPLED_Init();         //��ʼ���������͵�        PE0������    PB0�׹�     PB1���     PA1������3v
    TIM4_PWMOut_Init( 100-1, 14400-1 );           //��ʼ�����PD12
    TIM_SetCompare1(TIM4,85);    //�ر�
    my_mem_init(SRAMIN);                                /* ��ʼ���ڲ�SRAM�ڴ�� */
    freertos_demo();                                    /* ����FreeRTOS���� */
}


