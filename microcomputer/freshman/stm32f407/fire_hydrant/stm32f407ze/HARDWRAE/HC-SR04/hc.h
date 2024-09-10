#ifndef __HC_H
#define __HC_H	
#include "sys.h"


//��ʱ��4����
void hcsr04_NVIC(void);

//IO�ڳ�ʼ�� ��������ʼ��
void Hcsr041Init(void);
void Hcsr042Init(void);
//�򿪶�ʱ��4
static void OpenTimerForHc(void);

//�رն�ʱ��4
static void CloseTimerForHc(void);

//��ʱ��4���ж�
void TIM4_IRQHandler(void);

//��ȡ��ʱ��4������ֵ
u32 GetEchoTimer(void);

//ͨ����ʱ��4������ֵ�������
float Hcsr041GetLength(void);
float Hcsr042GetLength(void);

#define TRIG1_Send  PAout(0)

#define ECHO1_Reci  PAin(1) 

#endif

