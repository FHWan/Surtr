#include "IICSoft.h"

/*��ʼ��IIC*/
void IIC_Init( void )
{			
GPIO_InitTypeDef  GPIO_InitStructure;

	delay_init();
	/*ʱ�ӳ�ʼ��*/
  RCC_APB2PeriphClockCmd( IIC_RCC, ENABLE );

	/*����IO*/
  GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN | IIC_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( IIC_GPIO, &GPIO_InitStructure );
	
	/*���������ߺ�ʱ����*/
	IIC_SCL = 1;
	IIC_SDA = 1;
}
/*--------------------------------------------------*/

/*����IIC��ʼ�ź�*/
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

/*����IICֹͣ�ź�*/
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
 * �ȴ�Ӧ���źŵ���
 * ����ֵ��1������Ӧ��ʧ��
 *         0������Ӧ��ɹ�
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

/*����ACKӦ��*/
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

/*������ACKӦ��*/	    
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
 * IIC����һ���ֽ�
 * ���شӻ�����Ӧ��
 * 1����Ӧ��
 * 0����Ӧ��	
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
 * ��1���ֽ�
 * ack = 1ʱ������ACK
 * ack = 0������nACK   
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
 * IICдһ���ֽ�
 * ucSlaveAddress �ӻ���ַ
 * ucREGAddressAddress 	�Ĵ�����ַ
 * ucDdata				д������
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
 * IIC��һ���ֽ�
 * ucSlaveAddress �ӻ���ַ
 * ucREGAddressAddress 	�Ĵ�����ַ
 * ����ֵ  ��ȡ���ĵ�����
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
 * IICд�����ֽ�
 * ucSlaveAddress �ӻ���ַ
 * ucREGAddressAddress 	�Ĵ�����ַ
 * ucLength д�����ݳ���
 * ucData   д������ָ��
 * ����ֵ  0 �ɹ�
 * 				 1 ʧ��
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
 * IIC��ȡ����ֽ�
 * ucSlaveAddress �ӻ���ַ
 * ucREGAddressAddress 	�Ĵ�����ַ
 * ucLength ��ȡ���ݳ���
 * ucData   ��Ŷ�ȡ����ָ��
 * ����ֵ  0 �ɹ�
 * 				 1 ʧ��
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




