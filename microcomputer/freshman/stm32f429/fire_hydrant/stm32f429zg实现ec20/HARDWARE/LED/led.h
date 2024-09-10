#ifndef _LED_H
#define _LED_H
#include "sys.h"


#define LED0 PBout(1)   //LED0
#define LED1 PBout(0)   //LED1
#define BEEP PDout(11)	//BEEP

void LED_Init(void);
void BEEP_MY(void);
#endif
