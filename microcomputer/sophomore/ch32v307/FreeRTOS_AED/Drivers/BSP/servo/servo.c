#include "./BSP/servo/servo.h"

// ��ʼ��GPIO��TIM��PWM��ʹ�ü�����main����
void TIM4_PWMOut_Init( u16 arr, u16 psc ) {
    GPIO_InitTypeDef gpio_init_struct;
    TIM_TimeBaseInitTypeDef timx_pwm_chy_handle;
    TIM_OCInitTypeDef timx_oc_pwm_chy;

    GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();                         /* ʹ��PWM��IOʱ��  */
    GTIM_TIMX_PWM_CLK_ENABLE();                                  /* ʹ��TIMxʱ�� */
    GTIM_TIMX_PWM_CHY_GPIO_REMAP();                              /* ʹ��AFIO���ù���ʱ�ӣ�TIM4������ӳ��  TIM4_CH1->PD12  */

    gpio_init_struct.GPIO_Pin = GTIM_TIMX_PWM_CHY_GPIO_PIN;      /* PD12 */
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;                /* ����������� */
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;              /* IO�ٶ�50M */
    GPIO_Init(GTIM_TIMX_PWM_CHY_GPIO_PORT, &gpio_init_struct);   /* ��ʼ��GPIO */

    timx_pwm_chy_handle.TIM_Period = arr;                        /* �����Զ���װ��ֵ */
    timx_pwm_chy_handle.TIM_Prescaler =psc;                      /* ����Ԥ��Ƶϵ�� */
    timx_pwm_chy_handle.TIM_ClockDivision = TIM_CKD_DIV1;        /* ʱ�ӷ�Ƶ����  */
    timx_pwm_chy_handle.TIM_CounterMode = TIM_CounterMode_Up;    /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(GTIM_TIMX_PWM, &timx_pwm_chy_handle);       /* ��ʱ����ʼ�� */

    timx_oc_pwm_chy.TIM_OCMode = TIM_OCMode_PWM2;                /* PWMģʽ2 */
    timx_oc_pwm_chy.TIM_OutputState = TIM_OutputState_Enable;    /* �Ƚ����ʹ�� */
    timx_oc_pwm_chy.TIM_OCPolarity = TIM_OCPolarity_High;        /* ����Ƚϼ��Ը�  */
    TIM_OC1Init(GTIM_TIMX_PWM, &timx_oc_pwm_chy);                /* ��ʼ��TIMx OC1 */

    TIM_OC1PreloadConfig(GTIM_TIMX_PWM, TIM_OCPreload_Enable);   /* ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ��� */

    TIM_Cmd(GTIM_TIMX_PWM, ENABLE);                              /* ʹ��TIMx */
}
