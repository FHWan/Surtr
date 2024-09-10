#ifndef __EC20_H
#define __EC20_H
#include "sys.h"
#include "delay.h"
#include "usart.h"
void  EC20_Init(void);
void EC20Send_StrData(char *bufferdata);
void EC20Send_HexData(char *bufferdata);	
void EC20Send_RecAccessMode(void);
void  MQTT_Init(void);
void Read_GPS(u8 *lat,u8 *lon);
u8 Mqtt_Savedata(u8 *t_payload,
				 char *identity,
				 char *picture,
				 char *manager_id,
				 u8 *lon,u8 *lat,
				 float pitch,float roll,float yaw,
				 float power,
			     int count,
				 int warning,
			     int open,
				 int Lux
);
#endif

