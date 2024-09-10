#ifndef __EC20_H
#define __EC20_H

#include "usart.h"

void EC20_Init(void);
void EC20Send_StrData(char *bufferdata);
void EC20Send_HexData(char *bufferdata);	
void EC20Send_RecAccessMode(void);
void  MQTT_Init(void);
void Read_GPS(u8 *lat,u8 *lon);
u8 Mqtt_Savedata(u8 *t_payload,float wind,u8 *lon,u8 *lat,float gyrox,float gyroy,float gyroz,
                        u8 temperature,u8 humidity,u8 *SN,u8 sp02,u8 hr);
#endif
