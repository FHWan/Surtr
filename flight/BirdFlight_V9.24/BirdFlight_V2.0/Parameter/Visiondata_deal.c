/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :Visiondata_deal.c
 * 描述   :处理视觉发来的数据
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "Visiondata_deal.h"

void Vision_datadeal(_Data_Rx rx)
{
	int16_t tmp =0;
	int i;
//	static  int FlowX_Array[7];
//  static  int FlowY_Array[7];
	u8 HexToFloat[4];
	if(rx.len==16 && rx.buf[0]==0x55 && rx.buf[1]==0xAA)
	{
		/*接收视觉模块发来的信息*/
		if(rx.buf[2]==0x00){
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			
			DataCombineflag = Data_Headmode;
		}
		else if(rx.buf[2]==0x10)
		{	
			//需转化为实际以米为单位的坐标信息 摄像头视角为74.2 这里不考虑相机的旋转引起的位移变化
			/* Target_Roll */
			tmp = ((int16_t)rx.buf[3]<<8) + rx.buf[4];
			Sensor_Info.Raspberry_Xaxis = ( ((float)tmp - 80) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(-RT_Info.Pitch * 0.0174f ) ;

			/* Target_Pitch */
			tmp = ((int16_t)rx.buf[5]<<8) + rx.buf[6];
			Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 60) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f );
			
			/*高度数据 超声波 */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* 修改融合参数 */
			DataCombineflag = Data_Point;
		}
		/* 光流数据 */
		else if(rx.buf[2]==0x20)
		{ 
//		  tmp =  ( (int16_t)rx.buf[3]<<8 ) + rx.buf[4];			
//			Sensor_Info.FlowVelX = ( ( (float) Median_Filter(tmp,7,FlowX_Array) ) *0.1f  * RT_Info.Height * 0.112f ) / 0.304f ;
//			tmp = ( (int16_t)rx.buf[5]<<8 ) + rx.buf[6];
//			Sensor_Info.FlowVelY = ( ( (float)Median_Filter(tmp,7,FlowY_Array) )  *0.1f  * RT_Info.Height * 0.112f ) / 0.304f ;
			tmp =  ( (int16_t)rx.buf[3]<<8 ) + rx.buf[4];		
			Sensor_Info.FlowVelX = ( ( (float) tmp )  *0.1f  * RT_Info.Height * 0.1125f ) / 0.304f  ;
			tmp = ( (int16_t)rx.buf[5]<<8 ) + rx.buf[6];
			Sensor_Info.FlowVelY = ( ( (float) tmp )  *0.1f  * RT_Info.Height * 0.1125f ) / 0.304f   ;
			
			/*高度数据 超声波 */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* 修改融合参数 */
			DataCombineflag = Data_Flow;
		}
		/*  巡线数据 */
		else if(rx.buf[2]==0x30)
		{
				tmp =  ( (int)rx.buf[3]<<8 ) + rx.buf[4];
				Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 60) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f ) ;
				tmp =  ( (int)rx.buf[5]<<8 ) + rx.buf[6];
				Target_Info.BlackLineYaw =  (float)tmp;
				tmp =  ( (int)rx.buf[7]<<8 ) + rx.buf[8];
				Sensor_Info.FlowVelX = ( (float)tmp  *0.1f  * RT_Info.Height * 0.1125f ) / 0.304f ;
				/*高度数据 超声波 */
				for(i=0;i<4;i++)
				{
					HexToFloat[i]=rx.buf[11+i];
				}
				Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
				DataCombineflag = Data_Follow;               
		}
		
		else if(rx.buf[2]==0x40)
		{
			//需转化为实际以米为单位的坐标信息 摄像头视角为74.2 这里不考虑相机的旋转引起的位移变化
			/* Target_Roll */
			tmp = ((int16_t)rx.buf[5]<<8) + rx.buf[6];
			Sensor_Info.Raspberry_Xaxis = ( ((float)tmp - 160) * RT_Info.Height * 0.1125f ) / 0.304f +  RT_Info.Height* 100 * tan(-RT_Info.Pitch * 0.0174f ) ;

			/* Target_Pitch */
			tmp = ((int16_t)rx.buf[7]<<8) + rx.buf[8];
			Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 120) * RT_Info.Height * 0.1125f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f );
			
			/*高度数据 超声波 */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* 修改融合参数 */
			DataCombineflag = Data_Point;
		}	
	}
}




