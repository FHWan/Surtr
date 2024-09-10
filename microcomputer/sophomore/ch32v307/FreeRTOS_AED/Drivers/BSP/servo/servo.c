#include "./BSP/servo/servo.h"

// 初始化GPIO、TIM、PWM，使用见下面main函数
void TIM4_PWMOut_Init( u16 arr, u16 psc ) {
    GPIO_InitTypeDef gpio_init_struct;
    TIM_TimeBaseInitTypeDef timx_pwm_chy_handle;
    TIM_OCInitTypeDef timx_oc_pwm_chy;

    GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();                         /* 使能PWM的IO时钟  */
    GTIM_TIMX_PWM_CLK_ENABLE();                                  /* 使能TIMx时钟 */
    GTIM_TIMX_PWM_CHY_GPIO_REMAP();                              /* 使能AFIO复用功能时钟，TIM4部分重映射  TIM4_CH1->PD12  */

    gpio_init_struct.GPIO_Pin = GTIM_TIMX_PWM_CHY_GPIO_PIN;      /* PD12 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;                /* 复用推挽输出 */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;              /* IO速度50M */
    GPIO_Init(GTIM_TIMX_PWM_CHY_GPIO_PORT, &gpio_init_struct);   /* 初始化GPIO */

    timx_pwm_chy_handle.TIM_Period = arr;                        /* 设置自动重装载值 */
    timx_pwm_chy_handle.TIM_Prescaler =psc;                      /* 设置预分频系数 */
    timx_pwm_chy_handle.TIM_ClockDivision = TIM_CKD_DIV1;        /* 时钟分频因子  */
    timx_pwm_chy_handle.TIM_CounterMode = TIM_CounterMode_Up;    /* 向上计数模式 */
    TIM_TimeBaseInit(GTIM_TIMX_PWM, &timx_pwm_chy_handle);       /* 定时器初始化 */

    timx_oc_pwm_chy.TIM_OCMode = TIM_OCMode_PWM2;                /* PWM模式2 */
    timx_oc_pwm_chy.TIM_OutputState = TIM_OutputState_Enable;    /* 比较输出使能 */
    timx_oc_pwm_chy.TIM_OCPolarity = TIM_OCPolarity_High;        /* 输出比较极性高  */
    TIM_OC1Init(GTIM_TIMX_PWM, &timx_oc_pwm_chy);                /* 初始化TIMx OC1 */

    TIM_OC1PreloadConfig(GTIM_TIMX_PWM, TIM_OCPreload_Enable);   /* 使能TIMx在CCR1上的预装载寄存器 */

    TIM_Cmd(GTIM_TIMX_PWM, ENABLE);                              /* 使能TIMx */
}
