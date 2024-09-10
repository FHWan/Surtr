#ifndef USER_SERVO_H_
#define USER_SERVO_H_

#include "./SYSTEM/sys/sys.h"

/* TIMX PWM输出定义 */
#define GTIM_TIMX_PWM_CHY_GPIO_PORT         GPIOD
#define GTIM_TIMX_PWM_CHY_GPIO_PIN          GPIO_Pin_12
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE); }while(0)   /* PD口时钟使能 */
#define GTIM_TIMX_PWM_CLK_ENABLE()          do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); }while(0)     /* TIM4 时钟使能 */

/* TIMX REMAP设置
 * 因为我们LED0接在PD12上, 必须通过开启TIM4的重映射功能, 才能将TIM4_CH1输出到PD12上
 */
#define GTIM_TIMX_PWM_CHY_GPIO_REMAP()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);\
                                                GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);\
                                            }while(0)       /* 通道REMAP设置, 该函数不是必须的, 根据需要实现 */

#define GTIM_TIMX_PWM                       TIM4

void TIM4_PWMOut_Init( u16 arr, u16 psc );

#endif /* USER_SERVO_H_ */
