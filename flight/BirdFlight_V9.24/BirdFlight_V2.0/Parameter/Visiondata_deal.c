/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * ���� 	:Xiluna Tech
 * �ļ��� :Visiondata_deal.c
 * ����   :�����Ӿ�����������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
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
		/*�����Ӿ�ģ�鷢������Ϣ*/
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
			//��ת��Ϊʵ������Ϊ��λ��������Ϣ ����ͷ�ӽ�Ϊ74.2 ���ﲻ�����������ת�����λ�Ʊ仯
			/* Target_Roll */
			tmp = ((int16_t)rx.buf[3]<<8) + rx.buf[4];
			Sensor_Info.Raspberry_Xaxis = ( ((float)tmp - 80) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(-RT_Info.Pitch * 0.0174f ) ;

			/* Target_Pitch */
			tmp = ((int16_t)rx.buf[5]<<8) + rx.buf[6];
			Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 60) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f );
			
			/*�߶����� ������ */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* �޸��ںϲ��� */
			DataCombineflag = Data_Point;
		}
		/* �������� */
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
			
			/*�߶����� ������ */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* �޸��ںϲ��� */
			DataCombineflag = Data_Flow;
		}
		/*  Ѳ������ */
		else if(rx.buf[2]==0x30)
		{
				tmp =  ( (int)rx.buf[3]<<8 ) + rx.buf[4];
				Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 60) * RT_Info.Height * 0.225f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f ) ;
				tmp =  ( (int)rx.buf[5]<<8 ) + rx.buf[6];
				Target_Info.BlackLineYaw =  (float)tmp;
				tmp =  ( (int)rx.buf[7]<<8 ) + rx.buf[8];
				Sensor_Info.FlowVelX = ( (float)tmp  *0.1f  * RT_Info.Height * 0.1125f ) / 0.304f ;
				/*�߶����� ������ */
				for(i=0;i<4;i++)
				{
					HexToFloat[i]=rx.buf[11+i];
				}
				Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
				DataCombineflag = Data_Follow;               
		}
		
		else if(rx.buf[2]==0x40)
		{
			//��ת��Ϊʵ������Ϊ��λ��������Ϣ ����ͷ�ӽ�Ϊ74.2 ���ﲻ�����������ת�����λ�Ʊ仯
			/* Target_Roll */
			tmp = ((int16_t)rx.buf[5]<<8) + rx.buf[6];
			Sensor_Info.Raspberry_Xaxis = ( ((float)tmp - 160) * RT_Info.Height * 0.1125f ) / 0.304f +  RT_Info.Height* 100 * tan(-RT_Info.Pitch * 0.0174f ) ;

			/* Target_Pitch */
			tmp = ((int16_t)rx.buf[7]<<8) + rx.buf[8];
			Sensor_Info.Raspberry_Yaxis = ( ((float)tmp - 120) * RT_Info.Height * 0.1125f ) / 0.304f +  RT_Info.Height* 100 * tan(RT_Info.Roll * 0.0174f );
			
			/*�߶����� ������ */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Sensor_Info.US100_Zaxis = Hex_To_Decimal(HexToFloat,4) * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
			/* �޸��ںϲ��� */
			DataCombineflag = Data_Point;
		}	
	}
}




