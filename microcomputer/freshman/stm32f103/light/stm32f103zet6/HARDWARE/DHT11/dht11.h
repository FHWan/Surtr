#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//DHT11 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////

//IO方向设置
#define DHT11_IO_IN()  {GPIOC->ODR&=~(3<<(13*2));GPIOC->ODR|=0<<13*2;}	//PC13输入模式
#define DHT11_IO_OUT() {GPIOC->ODR&=~(3<<(13*2));GPIOC->ODR|=1<<13*2;} 	//PC13输出模式 
////IO操作函数											   
#define	DHT11_DQ_OUT PCout(13) //数据端口	PC13 
#define	DHT11_DQ_IN  PCin(13)  //数据端口	PC13 

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















