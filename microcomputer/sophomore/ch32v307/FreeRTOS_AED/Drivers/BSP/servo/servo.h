#ifndef USER_SERVO_H_
#define USER_SERVO_H_

#include "./SYSTEM/sys/sys.h"

/* TIMX PWM������� */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOD
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_Pin_12
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE); }while(0)   /* PD��ʱ��ʹ�� */
#define GTIM_TIMX_PWM_CLK_ENABLE()          do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); }while(0)     /* TIM4 ʱ��ʹ�� */

/* TIMX REMAP����
 * ��Ϊ����LED0����PD12��, ����ͨ������TIM4����ӳ�书��, ���ܽ�TIM4_CH1�����PD12��
 */
#define GTIM_TIMX_PWM_CHY_GPIO_REMAP()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);\
                                                GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);\
                                            }while(0)       /* ͨ��REMAP����, �ú������Ǳ����, ������Ҫʵ�� */

#define GTIM_TIMX_PWM                       TIM4

void TIM4_PWMOut_Init( u16 arr, u16 psc );

#endif /* USER_SERVO_H_ */
