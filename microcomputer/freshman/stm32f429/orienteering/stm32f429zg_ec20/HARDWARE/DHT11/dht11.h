#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"

//IO��������
#define DHT11_IO_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<(9*2);}	//PB12����ģʽ
#define DHT11_IO_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<(9*2);} 	//PB12���ģʽ
 
////IO��������											   
#define	DHT11_DQ_OUT    PBout(9)//���ݶ˿�	PB12
#define	DHT11_DQ_IN     PBin(9) //���ݶ˿�	PB12 
   	
u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11  
#endif
