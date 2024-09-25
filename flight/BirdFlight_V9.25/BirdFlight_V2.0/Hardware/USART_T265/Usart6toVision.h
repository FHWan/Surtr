#ifndef _USART6TOVISION_H
#define _USART6TOVISION_H

#include "stm32f4xx.h"
#include "DronePara.h"
#include <string.h>
#include <os.h>
#include "Task.h"
void Usart6_tx(uint8_t *data,uint16_t size);
void Usart6toVision_Init(u32 Bound);

extern _Vio_Rx t265_Rx;

#endif 
