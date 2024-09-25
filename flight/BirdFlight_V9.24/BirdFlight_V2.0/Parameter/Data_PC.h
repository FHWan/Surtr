#ifndef __DATA_PC_H
#define __DATA_PC_H

#include "DronePara.h"
#include "stm32f4xx.h"
#include "Task.h"
#include "Type_conversion.h"
#include "Usart3toBluetooth.h"
void sendParaInfo(void);
void sendRTInfo(void);
void sendRemoteControlData(void);
void sendRTOffset(void);

#endif 

