#ifndef __IOI2C_H
#define __IOI2C_H
#include "sys.h" 
   	   		   

//#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=0x00008000;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=0x00003000;}
//	 
//#define IIC_SCL    PBout(10) //SCL
//#define IIC_SDA    PBout(11) //SDA
//#define READ_SDA   PBin(11)  
#define SDA_IN()  {GPIOD->MODER&=~(3<<(9*2));GPIOD->MODER|=0<<9*2;}	//PB9输入模式
#define SDA_OUT() {GPIOD->MODER&=~(3<<(9*2));GPIOD->MODER|=1<<9*2;} //PB9输出模式
//IO操作函数	 
#define IIC_SCL    PDout(10) //SCL
#define IIC_SDA    PDout(9) //SDA	 
#define READ_SDA   PDin(9)  //输入SDA 

void IIC_Init(void);                			 
void IIC_Start(void);				
void IIC_Stop(void);	  			
void IIC_Send_Byte(uint8_t txd);			
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void); 				
void IIC_Ack(void);					
void IIC_NAck(void);				

int32_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
int32_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);

#endif

//------------------End of File----------------------------
