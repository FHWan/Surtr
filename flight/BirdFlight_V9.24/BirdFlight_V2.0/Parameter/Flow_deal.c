/******************** (C) COPYRIGHT 2015-2019 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Flow_deal.c
 * 描述   :处理光流发来的数据
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Flow_deal.h"

Butter_Parameter FlowX_Parameter;
Butter_BufferData  flowX_filter_buf[3];
Butter_Parameter FlowY_Parameter;
Butter_BufferData  flowY_filter_buf[3];
Butter_Parameter RotateFlowX_Parameter;
Butter_BufferData  RotateFlowX_filter_buf[3];
Butter_Parameter RotateFlowY_Parameter;
Butter_BufferData  RotateFlowY_filter_buf[3];

void Flow_datadeal(_Data_Rx rx)
{
	uint8_t Check_sum = 0;	
	static int16_t tmpX,tmpY =0;
	float ZaixsScale = 1.0f;
	float RotateScale = 230.0f;
	float RotateX,RotateY =0;
	float FlowTime =0;
	
	//优象光流
	if(rx.buf[0]==0xfe  && rx.buf[1]==0x0A && rx.buf[13]==0x55 )
	{
		if(rx.buf[10]==0xf5)
		{
				tmpX = ( (rx.buf[3]<<8) + rx.buf[2] ) ;		
				tmpY = ( (rx.buf[5]<<8) + rx.buf[4] ) ;
			  FlowTime = (float)( (int16_t)(rx.buf[7]<<8) + rx.buf[6])/1000000;
			
//				if(RT_Info.Height <= 0.2f)		ZaixsScale = 0.1f;
//				else if(RT_Info.Height <= 0.3f)	ZaixsScale = 0.15f;
//				else if(RT_Info.Height <= 0.4f)	ZaixsScale = 0.2f;
//				else if(RT_Info.Height <= 0.5f)	ZaixsScale = 0.25f;
//				else if(RT_Info.Height <= 0.6f)	ZaixsScale = 0.3f;
//				else if(RT_Info.Height <= 1.0f)	ZaixsScale = 0.35f;
//				else 	ZaixsScale = 0.4f;

				ZaixsScale = RT_Info.Height;
			
				/* 新光流摸快 */			
				Sensor_Info.FlowVelX = LPButterworth((float)tmpY,&flowX_filter_buf[0],&FlowX_Parameter) ;
				Sensor_Info.FlowVelY = -LPButterworth((float)tmpX,&flowY_filter_buf[0],&FlowY_Parameter) ; 
			
			
				RotateX = RotateScale *  Limits_data(  ((LPButterworth(RT_Info.GyroX,&RotateFlowX_filter_buf[0],&RotateFlowX_Parameter) )* PI/180) ,3.0f,-3.0f);
				RotateY = RotateScale *  Limits_data(  ((LPButterworth(RT_Info.GyroY,&RotateFlowY_filter_buf[0],&RotateFlowY_Parameter)) * PI/180) ,3.0f,-3.0f);
				
				RT_Info.LPFTest1 = RotateX;
				RT_Info.LPFTest2 = RotateY;
			
				Sensor_Info.FixFlowX = ( Sensor_Info.FlowVelX - RotateX ) /10000 /FlowTime *ZaixsScale ;
				Sensor_Info.FixFlowY = ( Sensor_Info.FlowVelY - RotateY ) /10000 /FlowTime *ZaixsScale ;
				
				Sensor_Info.FlowX += Sensor_Info.FixFlowX * FlowTime;
				Sensor_Info.FlowY += Sensor_Info.FixFlowY * FlowTime;			
		}
		else
		{
			  Sensor_Info.FixFlowX =0;
				Sensor_Info.FixFlowY =0;
		}
	}
}
