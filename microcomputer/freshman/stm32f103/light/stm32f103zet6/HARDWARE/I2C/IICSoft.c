#include "IICSoft.h"

/*初始化IIC*/
void IIC_Init( void )
{			
GPIO_InitTypeDef  GPIO_InitStructure;

	delay_init();
	/*时钟初始化*/
  RCC_APB2PeriphClockCmd( IIC_RCC, ENABLE );

	/*配置IO*/
  GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN | IIC_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( IIC_GPIO, &GPIO_InitStructure );
	
	/*拉高数据线和时钟线*/
	IIC_SCL = 1;
	IIC_SDA = 1;
}
/*--------------------------------------------------*/

/*产生IIC起始信号*/
static void IIC_Start( void )
{
	SDA_OUT();    
	IIC_SDA = 1;	  	  
	IIC_SCL = 1;
	delay_us( 4 );
 	IIC_SDA = 0;
	delay_us( 4 );
	IIC_SCL = 0;
}	  
/*--------------------------------------------------*/

/*产生IIC停止信号*/
static void IIC_Stop( void )
{
	SDA_OUT();
	IIC_SCL = 0;
	IIC_SDA = 0;
 	delay_us( 4 );
	IIC_SCL = 1; 
	IIC_SDA = 1;
	delay_us( 4 );							   	
}
/*--------------------------------------------------*/

/*
 * 等待应答信号到来
 * 返回值：1，接收应答失败
 *         0，接收应答成功
 */
static uint8_t IIC_Wait_Ack( void )
{
uint8_t ucErrTime = 0;
	SDA_IN();      
	IIC_SDA = 1;delay_us(1);	   
	IIC_SCL = 1;delay_us(1);	 
	while( READ_SDA )
	{
		ucErrTime++;
		if( ucErrTime > 250 )
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;	   
	return 0;  
} 
/*--------------------------------------------------*/

/*产生ACK应答*/
static void IIC_Ack( void )
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	delay_us( 2 );
	IIC_SCL = 1;
	delay_us( 2 );
	IIC_SCL = 0;
}
/*--------------------------------------------------*/

/*不产生ACK应答*/	    
static void IIC_NAck( void )
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	delay_us( 2 );
	IIC_SCL = 1;
	delay_us( 2 );
	IIC_SCL = 0;
}			
/*--------------------------------------------------*/

/*
 * IIC发送一个字节
 * 返回从机有无应答
 * 1，有应答
 * 0，无应答	
 */
void IIC_Send_Byte( uint8_t ucTxData )
{                        
uint8_t t;   
	SDA_OUT(); 	    
	IIC_SCL = 0;
	for( t = 0; t<8; t++ )
	{              
		IIC_SDA = ( ucTxData & 0x80 ) >> 7;
		ucTxData <<= 1; 	  
		delay_us( 2 );   
		IIC_SCL = 1;
		delay_us( 2 ); 
		IIC_SCL = 0;	
		delay_us( 2 );
	}	 
} 	  
/*--------------------------------------------------*/

/*
 * 读1个字节
 * ack = 1时，发送ACK
 * ack = 0，发送nACK   
 */
uint8_t IIC_Read_Byte( uint8_t ucAck )
{
uint8_t ucBit = 0, ucReceive = 0;
	SDA_IN();
  for( ucBit = 0; ucBit < 8; ucBit++ )
	{
		IIC_SCL = 0; 
		delay_us( 2 );
		IIC_SCL = 1;
		ucReceive <<= 1;
		if( READ_SDA )
		{
			ucReceive ++;  
		}			
		delay_us( 1 ); 
  }					 
	if ( !ucAck )
	{
		IIC_NAck();
	}
	else
	{
		IIC_Ack();
	}
  return ucReceive;
}
/*--------------------------------------------------*/

/*
 * IIC写一个字节
 * ucSlaveAddress 从机地址
 * ucREGAddressAddress 	寄存器地址
 * ucDdata				写入数据
 */
uint8_t IIC_Single_Write( uint8_t ucSlaveAddress, uint8_t ucREGAddressAddress, uint8_t ucDdata )		 
{
	IIC_Start();								
	IIC_Send_Byte( ucSlaveAddress << 1 | 0 );
	if( IIC_Wait_Ack() )
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte( ucREGAddressAddress );
	IIC_Wait_Ack();	
	IIC_Send_Byte( ucDdata );
	IIC_Wait_Ack();
	IIC_Stop();
  return 0;
}
/*--------------------------------------------------*/

/*
 * IIC读一个字节
 * ucSlaveAddress 从机地址
 * ucREGAddressAddress 	寄存器地址
 * 返回值  读取到的的数据
 */
uint8_t IIC_Single_Read( uint8_t ucSlaveAddress, uint8_t ucREGAddressAddress )	 
{
uint8_t ucData;
	IIC_Start();
	IIC_Send_Byte( ucSlaveAddress << 1 | 0 );
	IIC_Send_Byte( ucREGAddressAddress );
	IIC_Wait_Ack();	
	IIC_Start();
	IIC_Send_Byte( ucSlaveAddress << 1 | 1 );
	IIC_Wait_Ack();
	ucData = IIC_Read_Byte( 0 );
	IIC_Stop();
	return ucData;
}
/*--------------------------------------------------*/

/*
 * IIC写入多个字节
 * ucSlaveAddress 从机地址
 * ucREGAddressAddress 	寄存器地址
 * ucLength 写入数据长度
 * ucData   写入数据指针
 * 返回值  0 成功
 * 				 1 失败
 */
uint8_t IIC_Write_Len( uint8_t ucSlaveAddress, uint8_t ucREGAddress, uint8_t ucLength, uint8_t *ucData )
{
uint8_t ucTimes; 
  IIC_Start(); 
	IIC_Send_Byte( ( ucSlaveAddress<<1 ) | 0 );
	if( IIC_Wait_Ack() )	
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte( ucREGAddress );	
    IIC_Wait_Ack();		
	for( ucTimes = 0; ucTimes < ucLength; ucTimes++ )
	{
		IIC_Send_Byte( ucData[ ucTimes ] );	
		if( IIC_Wait_Ack() )		
		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
  IIC_Stop();	 
	return 0;	
} 
/*--------------------------------------------------*/

/*
 * IIC读取多个字节
 * ucSlaveAddress 从机地址
 * ucREGAddressAddress 	寄存器地址
 * ucLength 读取数据长度
 * ucData   存放读取数据指针
 * 返回值  0 成功
 * 				 1 失败
 */
uint8_t IIC_Read_Len( uint8_t ucSlaveAddress, uint8_t ucREGAddress, uint8_t ucLength, uint8_t *ucData )
{ 
 	IIC_Start(); 
	IIC_Send_Byte( ( ucSlaveAddress << 1 ) | 0 );
	if( IIC_Wait_Ack() )	
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte( ucREGAddress );	
    IIC_Wait_Ack();		
    IIC_Start();
		IIC_Send_Byte( ( ucSlaveAddress << 1 )|1 );
    IIC_Wait_Ack();		
	while( ucLength )
	{
		if( ucLength == 1 )
		{
			*ucData = IIC_Read_Byte( 0 );
		}
		else 
		{
			*ucData = IIC_Read_Byte( 1 );		
		}			
		ucLength --;
		ucData ++; 
	}    
  IIC_Stop();	
	return 0;	
}
/*--------------------------------------------------*/




