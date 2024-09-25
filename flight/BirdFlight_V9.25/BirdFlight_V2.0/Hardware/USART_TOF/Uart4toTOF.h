#ifndef _UART4TOTOF_H
#define _UART4TOTOF_H

#include "stm32f4xx.h"
#include "DronePara.h"
#include "Task.h"
#include <string.h>
#include <os.h>


extern _Data_Rx TOF_rx; 
void Uart4toTOF_Init(u32 Bound);
void Uart4_tx(uint8_t *data,uint16_t size);

#endif




