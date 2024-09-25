#ifndef __I2C_H
#define __I2C_H

#include "explore_systick.h"
#include "stm32f4xx.h"

//MS5611
#define SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	
#define SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} 

 
#define IIC_SCL    PBout(6) //SCL

#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  


void IIC_Init(void);                	 
void IIC_Start(void);				
void IIC_Stop(void);	  			
void IIC_Send_Byte(u8 txd);			
u8 IIC_Read_Byte(unsigned char ack);
u8 IIC_Wait_Ack(void); 				
void IIC_Ack(void);					
void IIC_NAck(void);				

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);


#endif
