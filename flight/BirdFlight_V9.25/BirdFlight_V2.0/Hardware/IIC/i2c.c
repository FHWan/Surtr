#include "i2c.h"

void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//MS5611
	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	IIC_SCL=1;
	IIC_SDA=1;
}


void IIC_Start(void)
{
	SDA_OUT();     
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=0;
}	  

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(4);							   	
}

u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
	    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
		  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
  	SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
      IIC_SDA=(txd&0x80)>>7;
      txd<<=1; 	  
			delay_us(2);   
			IIC_SCL=1;
			delay_us(2); 
			IIC_SCL=0;	
			delay_us(2);
    }	 
} 	    
   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
      IIC_SCL=0; 
      delay_us(2);
		  IIC_SCL=1;
      receive<<=1;
      if(READ_SDA)receive++;   
		  delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();    
    return receive;
}
