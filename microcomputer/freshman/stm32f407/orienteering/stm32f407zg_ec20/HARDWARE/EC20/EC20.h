#ifndef __EC20_H
#define __EC20_H
#include "sys.h"
#include "delay.h"
#include "usart.h"
void  EC20_Init(void);
void EC20Send_RecAccessMode(void);
void  MQTT_Init(void);
void Clear_Buffer(void);
void Read_GPS(u8 *lat,u8 *lon);
u8 Mqtt_Savedata(u8 *t_payload,u8 *HR,u8 *SPO2,u8 *lon,u8 *lat,u8 temperature,u8 humidity,float pitch,float roll,float yaw,float wind,char* card_ID);
#endif
