/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :Visiondata_deal.c
 * 描述   :处理视觉发来的数据
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "laserArray_deal.h"

void LaserArray_datadeal(_Data_Rx rx)
{
	unsigned char  i;	
	u8 HexToFloat[4];
	static float Laser1[2];
  static float Laser2[2];
	static float Laser3[2];
	static float Laser4[2];
	
	if(rx.len==24 && rx.buf[0]==0x55 && rx.buf[1]==0xAA && rx.buf[23]==0xFF)
	{
		/*接收激光矩阵发来的信息*/
		if(rx.buf[2]==0xEE){
			
			/** zuo **/
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[3+i];
			}		
			Sensor_Info.LaserArray1Status = rx.buf[7];
			if(  ( Sensor_Info.LaserArray1Status & 0xf0) == 0x00 )
			{
				 Sensor_Info.LaserArray1 = Hex_To_Decimal(HexToFloat,4);	
				
					if(Sensor_Info.LaserArray1>=2.5f)
						Sensor_Info.Laser1invalid ++;
					else
						Sensor_Info.Laser1invalid= 0 ;
			}
			else
			{
				 Sensor_Info.LaserArray1 = 10 ;
				 Sensor_Info.Laser1invalid ++;
			}		
		  Sensor_Info.LaserArray1 = Average_Filter(Sensor_Info.LaserArray1,2,Laser1);
			
			/** hou **/		
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[8+i];
			}
			Sensor_Info.LaserArray2Status = rx.buf[12];
			if(  ( Sensor_Info.LaserArray2Status & 0xf0) == 0x00 )
			{
				 Sensor_Info.LaserArray2 = Hex_To_Decimal(HexToFloat,4);	
				
					if(Sensor_Info.LaserArray2 >= 2.5f)
						Sensor_Info.Laser2invalid ++;
					else
						Sensor_Info.Laser2invalid= 0 ;
			}
			else
			{
				 Sensor_Info.LaserArray2 = 10 ;
				 Sensor_Info.Laser2invalid ++;
			}
			Sensor_Info.LaserArray2 = Average_Filter(Sensor_Info.LaserArray2,2,Laser2);
			
			
			/** you **/							
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[13+i];
			}
			Sensor_Info.LaserArray3Status = rx.buf[17];
			if(  ( Sensor_Info.LaserArray3Status & 0xf0) == 0x00 )
			{
				 Sensor_Info.LaserArray3 = Hex_To_Decimal(HexToFloat,4);	
					if(Sensor_Info.LaserArray3>=2.5f)
						Sensor_Info.Laser3invalid ++;
					else
						Sensor_Info.Laser3invalid= 0 ;
			}
			else
			{
				 Sensor_Info.LaserArray3 = 10 ;
				 Sensor_Info.Laser3invalid ++;
			}
			Sensor_Info.LaserArray3 = Average_Filter(Sensor_Info.LaserArray3,2,Laser3);
			
			
			/** qian **/		
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[18+i];
			}
			Sensor_Info.LaserArray4Status = rx.buf[22];
			if(  ( Sensor_Info.LaserArray4Status & 0xf0) == 0x00 )
			{
				 Sensor_Info.LaserArray4 = Hex_To_Decimal(HexToFloat,4);
					if(Sensor_Info.LaserArray4>=2.5f)
						Sensor_Info.Laser4invalid ++;
					else
						Sensor_Info.Laser4invalid= 0 ;				
			}
			else
			{
				 Sensor_Info.LaserArray4 = 10 ;
				 Sensor_Info.Laser4invalid ++;
			}
			Sensor_Info.LaserArray4 = Average_Filter(Sensor_Info.LaserArray4,2,Laser4);
			
			
			if(Sensor_Info.Laser1invalid>=254)
				 Sensor_Info.Laser1invalid =255;
			if(Sensor_Info.Laser2invalid>=254)
				 Sensor_Info.Laser2invalid =255;
			if(Sensor_Info.Laser3invalid>=254)
				 Sensor_Info.Laser3invalid =255;
			if(Sensor_Info.Laser4invalid>=254)
				 Sensor_Info.Laser4invalid =255;
			
			
		}
	}
}




