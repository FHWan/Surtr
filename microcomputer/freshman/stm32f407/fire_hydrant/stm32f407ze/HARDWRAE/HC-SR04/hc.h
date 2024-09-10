#ifndef __HC_H
#define __HC_H	
#include "sys.h"


//定时器4设置
void hcsr04_NVIC(void);

//IO口初始化 及其他初始化
void Hcsr041Init(void);
void Hcsr042Init(void);
//打开定时器4
static void OpenTimerForHc(void);

//关闭定时器4
static void CloseTimerForHc(void);

//定时器4终中断
void TIM4_IRQHandler(void);

//获取定时器4计数器值
u32 GetEchoTimer(void);

//通过定时器4计数器值推算距离
float Hcsr041GetLength(void);
float Hcsr042GetLength(void);

#define TRIG1_Send  PAout(0)

#define ECHO1_Reci  PAin(1) 

#endif

