#ifndef __USART3TOBLUETOOTH_H
#define __USART3TOBLUETOOTH_H

#include "stm32f4xx.h"
#include "DronePara.h"
#include <string.h>
#include <os.h>
#include "Task.h"

extern _Data_Rx Bluetooth_rx; 

void Usart3toBluetooth_Init(u32 Bound);

void Uart3_tx(uint8_t *data,uint16_t size);

#endif 
