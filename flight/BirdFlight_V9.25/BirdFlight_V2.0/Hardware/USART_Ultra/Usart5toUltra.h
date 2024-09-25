#ifndef __USART5TOULTRA_H
#define __USART5TOULTRA_H

#include "stm32f4xx.h"
#include "DronePara.h"
#include <string.h>
#include <os.h>
#include "Task.h"

void Uart5toUltra_Init(u32 Bound);
void ReceiveUltraData(void);
void SendStopflag(void);

extern uint16_t ReceiveHeight;

#endif
