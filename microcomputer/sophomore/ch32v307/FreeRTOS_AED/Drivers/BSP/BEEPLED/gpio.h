#ifndef __BEEP_H
#define __BEEP_H	 

#include "./SYSTEM/sys/sys.h"

#define KEY0        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define KEY0_PRES   1

void BEEPLED_Init(void);//≥ı ºªØ
u8 KEY_Scan(u8 mode);

#endif

















