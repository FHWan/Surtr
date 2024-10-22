#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"

//IO方向设置
#define DHT11_IO_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<(9*2);}	//PB12输入模式
#define DHT11_IO_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<(9*2);} 	//PB12输出模式
 
////IO操作函数											   
#define	DHT11_DQ_OUT    PBout(9)//数据端口	PB12
#define	DHT11_DQ_IN     PBin(9) //数据端口	PB12 
   	
u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11  
#endif
