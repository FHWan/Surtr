#ifndef __DHT11_H
#define __DHT11_H 
#include "ch32v30x.h"

#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)



u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
void DHT11_IO_IN(void);
void DHT11_IO_OUT(void);
#endif















