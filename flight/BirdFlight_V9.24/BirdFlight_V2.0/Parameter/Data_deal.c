/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Data_deal.c
 * ����   :����PC����������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Data_deal.h"


Acce_Unit acce_sample[6]={0};//����6�У�����6�����������


int sumCheck(_Data_Rx rx)
{
	int i=0;
	unsigned char sum;
	for(i=0;i<rx.len-1;i++)
	{
		sum^=rx.buf[i];
	}
	if(sum==rx.buf[rx.len-1])
		return 1;
	else 
		return 0;
}

static u8 firstdata[16];
static u8 secdata[16];

Acce_Unit new_offset={
  0,0,0,
};
Acce_Unit new_scales={
  1.0,1.0,1.0,
};

_Data_Rx Stitchingdata;
//��������ƴ��
void DataStitching(_Data_Rx rx)
{
	static u8 i,firstlen;
	static u8 BluetoothStitch[16];
	static u8 stitchingflag = 0;
	/*�ڶ�֡����*/
	if(rx.len!=16 && stitchingflag == 1 && rx.buf[0]!=0x55 && rx.buf[1]!=0xAA)
	{
		memcpy(secdata,rx.buf,sizeof(rx.buf));
		for(i = firstlen;i<(rx.len + firstlen);i++)
		{
			BluetoothStitch[i] = secdata[i-firstlen];
		}
		Stitchingdata.len = sizeof(BluetoothStitch);
		stitchingflag = 0;
		memcpy(Stitchingdata.buf,BluetoothStitch,sizeof(BluetoothStitch));
		DataDeal(Stitchingdata);
	}
	/*��һ֡����*/
	else if(rx.len<=16 && rx.buf[0]==0x55)
	{
		memcpy(firstdata,rx.buf,sizeof(rx.buf));
		for(i = 0;i<rx.len;i++)
		{
			BluetoothStitch[i] = firstdata[i];
		}
		firstlen = 	rx.len;	
		stitchingflag = 1;
	}
	/*ʹ�ñʼǱ��Դ���������Ҫ���ݵ�ƴ��*/
	else if(rx.len==16 && rx.buf[0]==0x55 && rx.buf[1]==0xAA)
	{
		DataDeal(rx);
	}
}
void DataDeal(_Data_Rx rx)
{
	u8 HexToFloat[4];
	float pidParaTemp[3];
	u8 i,j;
	/*���п���ָ�� */
	if( rx.len==16 && rx.buf[0]==0x55 && rx.buf[1]==0xAA )
	{
		if(rx.buf[2]==0xff  && RT_Info.lowPowerFlag==0) //���˻����� �͵�ѹģʽ�²����������ź� 
		{
			if(rx.buf[3]==0)
			{
					FlightControl.OnOff = Drone_Off;
					OriginalPitchRate.iOut = 0;
					OriginalRollRate.iOut = 0;
					OriginalYaw.iOut = 0;
					OriginalVelZ.iOut = 0;
					OriginalAccZ.iOut = 0;
					OriginalVelX.iOut = 0;
					OriginalVelY.iOut = 0;
					OriginalFlowVelX.iOut =0;
					OriginalFlowVelY.iOut =0;
					Target_Info.Height = 1.0f; //�ָ���ʼ��Ĭ��Ŀ��߶�
					Target_Info.Pitch = 0.0f; //�ָ���ʼ��Ĭ��Ŀ�긩��
					Target_Info.Roll = 0.0f; //�ָ���ʼ��Ĭ��Ŀ�귭��	
					Target_Info.Yaw = 0.0f;				
					Target_Info.RoutePlanX = 0.0f;
					Target_Info.RoutePlanY = 0.0f;
					FlightControl.ArmPower =	ArmPowerON;
					Flight_Remote_Control.FlightControlMode =  VIOCruise;
					RestartT265();
					RT_Info.CpuTick=0;
					delay_ms(5);
			}
			
			else if(rx.buf[3]==1)
			{					
				FlightControl.DroneMode=Drone_Mode_4Axis;				
				FlightControl.OnOff = Drone_On;
				FlightControl.TakeOff = Complete_TakingOff;
			}
			else if(rx.buf[3]==2)	//��������		
			{
				FlightControl.landFlag=1;
			}						
		}
		/*����Ŀ��Ƕ�----��������ɵ�ʱ��������*/
		else if(rx.buf[2]==0x01 && FlightControl.DroneMode!=Drone_Mode_4Axis ) 
		{
			/*  Target_Pitch */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[3+i];
			}
			Target_Info.Pitch = Hex_To_Decimal(HexToFloat,4); 
			/*  Target_Roll */
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[7+i];
			}
			Target_Info.Roll = Hex_To_Decimal(HexToFloat,4);								
			/*  Target_Yaw */					
			for(i=0;i<4;i++)
			{
				HexToFloat[i]=rx.buf[11+i];
			}
			Target_Info.Yaw = Hex_To_Decimal(HexToFloat,4); 
		}	
		else if(rx.buf[2]==0x02) //ѡ��ʵ�����ģʽͬʱ���û�����
		{
			switch(rx.buf[3])
			{
					case 0:
							FlightControl.DroneMode=Drone_Mode_None;
							break;
					case 1:
							FlightControl.DroneMode=Drone_Mode_RatePitch;
							break;
					case 2:
							FlightControl.DroneMode=Drone_Mode_RateRoll;
							break;
					case 3:
							FlightControl.DroneMode=Drone_Mode_Pitch;
							break;
					case 4:
							FlightControl.DroneMode=Drone_Mode_Roll;
							break;
					case 5:
							FlightControl.DroneMode=Drone_Mode_4Axis;
							break;
					default:
							break;
			}
		}
		else if(rx.buf[2]==0x03) //��ȡPID
		{
			FlightControl.ReportSW=Report_SET;					
		}	
		
		/*����Ŀ��Rate*/
		else if(rx.buf[2]==0x04){
				for(i=0;i<4;i++)
				{
					HexToFloat[i]=rx.buf[3+i];
				}
				Target_Info.RatePitch = Hex_To_Decimal(HexToFloat,4)/2;
				for(i=0;i<4;i++)
				{
					HexToFloat[i]=rx.buf[7+i];
				}
				Target_Info.RateRoll = Hex_To_Decimal(HexToFloat,4)/2;
		}
		/*���������й������ֱ���ֵ(pitch roll)*/
		else if(rx.buf[2]==0x05){			
				RockerControl.XaxisPos =  -(float)( (int16_t)( ( (int16_t)rx.buf[4]<<8 ) + rx.buf[3] ) );
        RockerControl.YaxisPos = -(float)( (int16_t)(( (int16_t)rx.buf[6]<<8 ) + rx.buf[5]) );
        RockerControl.Navigation = (float)( (int16_t)(( (int16_t)rx.buf[8]<<8 ) + rx.buf[7]) );
        RockerControl.ZaxisPos = (float)( (int16_t)(( (int16_t)rx.buf[10]<<8 ) + rx.buf[9]) );
		}
		/*���������й������ֱ���ֵ(height yaw)*/
		else if(rx.buf[2]==0x06){
//				for(i=0;i<4;i++)
//				{
//					HexToFloat[i]=rx.buf[3+i];
//				}			
//				RockerControl.Navigation = Hex_To_Decimal(HexToFloat,4);
//				for(i=0;i<4;i++)
//				{
//					HexToFloat[i]=rx.buf[7+i];
//				}	
//				RockerControl.ZaxisPos = Hex_To_Decimal(HexToFloat,4);
		}			
		/*����Pitch��PID*/	
		else if(rx.buf[2] == 0x07)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.Pitch.Kp=pidParaTemp[0];
			PID_ParaInfo.Pitch.Ki=pidParaTemp[1];
			PID_ParaInfo.Pitch.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}				
		/*����Roll��PID*/					
		else if(rx.buf[2] == 0x08)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}     
			PID_ParaInfo.Roll.Kp=pidParaTemp[0];
			PID_ParaInfo.Roll.Ki=pidParaTemp[1];
			PID_ParaInfo.Roll.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		/*����Yaw��PID*/					
		else if(rx.buf[2] == 0x09)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.Yaw.Kp=pidParaTemp[0];
			PID_ParaInfo.Yaw.Ki=pidParaTemp[1];
			PID_ParaInfo.Yaw.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		/*����Height��PID*/					
		else if(rx.buf[2] == 0x0A)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.PosZ.Kp=pidParaTemp[0];
			PID_ParaInfo.PosZ.Ki=pidParaTemp[1];
			PID_ParaInfo.PosZ.Kd=pidParaTemp[2];
			Write_config();		
			FlightControl.ReportSW=Report_SET;
		} 
	 /*����ratePitch��PID*/					
		else if(rx.buf[2] == 0x0B)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}
			PID_ParaInfo.PitchRate.Kp=pidParaTemp[0];
			PID_ParaInfo.PitchRate.Ki=pidParaTemp[1];
			PID_ParaInfo.PitchRate.Kd=pidParaTemp[2];
			Write_config();
			FlightControl.ReportSW=Report_SET;
		}
	 /*����rateRoll��PID*/					
		else if(rx.buf[2] == 0x0C)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.RollRate.Kp=pidParaTemp[0];
			PID_ParaInfo.RollRate.Ki=pidParaTemp[1];
			PID_ParaInfo.RollRate.Kd=pidParaTemp[2];
			Write_config();
			FlightControl.ReportSW=Report_SET;
		}
		/*����rateYaw��PID*/					
		else if(rx.buf[2] == 0x0D)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			} 
			PID_ParaInfo.YawRate.Kp=pidParaTemp[0];
			PID_ParaInfo.YawRate.Ki=pidParaTemp[1];
			PID_ParaInfo.YawRate.Kd=pidParaTemp[2];
			Write_config();			
			FlightControl.ReportSW=Report_SET;
		}
		/*����VelZ��PID*/					
		else if(rx.buf[2] == 0x0E)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}
			PID_ParaInfo.VelZ.Kp=pidParaTemp[0];
			PID_ParaInfo.VelZ.Ki=pidParaTemp[1];
			PID_ParaInfo.VelZ.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		/*����AccZ��PID*/					
		else if(rx.buf[2] == 0x0F)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}
			PID_ParaInfo.AccZ.Kp=pidParaTemp[0];
			PID_ParaInfo.AccZ.Ki=pidParaTemp[1];
			PID_ParaInfo.AccZ.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		/*����PositionX��PID*/					
		else if(rx.buf[2] == 0x12)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.PosX.Kp=pidParaTemp[0];
			PID_ParaInfo.PosX.Ki=pidParaTemp[1];
			PID_ParaInfo.PosX.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		/*����PositionY��PID*/					
		else if(rx.buf[2] == 0x13)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.PosY.Kp=pidParaTemp[0];
			PID_ParaInfo.PosY.Ki=pidParaTemp[1];
			PID_ParaInfo.PosY.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		/*����SpeedX��PID*/					
		else if(rx.buf[2] == 0x14)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.VelX.Kp=pidParaTemp[0];
			PID_ParaInfo.VelX.Ki=pidParaTemp[1];
			PID_ParaInfo.VelX.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		/*����SpeedY��PID*/					
		else if(rx.buf[2] == 0x15)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.VelY.Kp=pidParaTemp[0];
			PID_ParaInfo.VelY.Ki=pidParaTemp[1];
			PID_ParaInfo.VelY.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}		
		
		/*����FlowX��PID*/					
		else if(rx.buf[2] == 0x16)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.FlowX.Kp=pidParaTemp[0];
			PID_ParaInfo.FlowX.Ki=pidParaTemp[1];
			PID_ParaInfo.FlowX.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		
		/*����FlowVelX��PID*/					
		else if(rx.buf[2] == 0x17)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.FlowVelX.Kp=pidParaTemp[0];
			PID_ParaInfo.FlowVelX.Ki=pidParaTemp[1];
			PID_ParaInfo.FlowVelX.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		
		/*����FlowY��PID*/					
		else if(rx.buf[2] == 0x18)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.FlowY.Kp=pidParaTemp[0];
			PID_ParaInfo.FlowY.Ki=pidParaTemp[1];
			PID_ParaInfo.FlowY.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		
		/*����FlowVelY��PID*/					
		else if(rx.buf[2] == 0x19)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					HexToFloat[j]=rx.buf[3+j+i*4];
				}
				pidParaTemp[i]=Hex_To_Decimal(HexToFloat,4);
			}  
			PID_ParaInfo.FlowVelY.Kp=pidParaTemp[0];
			PID_ParaInfo.FlowVelY.Ki=pidParaTemp[1];
			PID_ParaInfo.FlowVelY.Kd=pidParaTemp[2];
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}
		
		/*������У׼*/
		else if(rx.buf[2]==0x30)
		{
				OffsetData.GyroX  = RT_Info.GyroX ;
				OffsetData.GyroY  = RT_Info.GyroY ;
				OffsetData.GyroZ  = RT_Info.GyroZ ;
				Write_config();	
		}		
		
		/*ƫ�ýǶ�*/
		else if(rx.buf[2] == 0x32)
		{
			Errangle_Info.fixedErroPitch = RT_Info.Pitch;
			Errangle_Info.fixedErroRoll = RT_Info.Roll;
			Write_config();	
			FlightControl.ReportSW=Report_SET;
		}	
		
	  /*���ٶ�У׼*/
		/*��һ��ɿ�ƽ�ţ�Z�����������Ϸ���Z axis is about 1g,X��Y is about 0g*/
		/*�ڶ���ɿ�ƽ�ţ�X�����������Ϸ���X axis is about 1g,Y��Z is about 0g*/
		/*������ɿ�ƽ�ţ�X�����������·���X axis is about -1g,Y��Z is about 0g*/
		/*������ɿ�ƽ�ţ�Y�����������·���Y axis is about -1g,X��Z is about 0g*/
		/*������ɿ�ƽ�ţ�Y�����������Ϸ���Y axis is about 1g,X��Z is about 0g*/
		/*������ɿ�ƽ�ţ�Z�����������·���Z axis is about -1g,X��Y is about 0g*/
		else if(rx.buf[2]==0x31)
		{
				unsigned char Pretime =0 ;
				static int16_t AccData[6] ={0};
				static float PreparationAccX,PreparationAccY,PreparationAccZ =0;
				
				if(rx.buf[3]==0x01)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);
					}
					acce_sample[0].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[0].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[0].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;
				}
				else if(rx.buf[3]==0x02)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);
					}
					acce_sample[5].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[5].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[5].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;					
				}
				else if(rx.buf[3]==0x03)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);
					}
					acce_sample[2].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[2].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[2].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;					
				}
				else if(rx.buf[3]==0x04)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);						
					}
					acce_sample[1].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[1].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[1].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;					
				}
				else if(rx.buf[3]==0x05)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);						
					}
					acce_sample[3].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[3].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[3].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;					
				}
				else if(rx.buf[3]==0x06)
				{
					while( Pretime < 100)
					{
							Pretime ++;
							MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
							PreparationAccX += (float)AccData[0] /4096.0f ;
							PreparationAccY += (float)AccData[1] /4096.0f ;
							PreparationAccZ += (float)AccData[2] /4096.0f ;
							delay_ms(4);
					}
					acce_sample[4].x = PreparationAccX /100 *GRAVITY_MSS;
					acce_sample[4].y = PreparationAccY /100 *GRAVITY_MSS;
					acce_sample[4].z = PreparationAccZ /100 *GRAVITY_MSS;
					PreparationAccX = PreparationAccY = PreparationAccZ =0;				
				}
				else if(rx.buf[3]==0xFF)
				{				
					Calibrate_accel(acce_sample,&new_offset,&new_scales);
					OffsetData.AccX = new_offset.x;
					OffsetData.AccY = new_offset.y;
					OffsetData.AccZ = new_offset.z;
					OffsetData.AccXScale = new_scales.x ;
					OffsetData.AccYScale = new_scales.y ;
					OffsetData.AccZScale = new_scales.z ;			
					Write_config();
					delay_ms(4);
				}

		}
		
		else if(rx.buf[2]==0x33) //У׼������
		{
			if(rx.buf[3]==1)
			{
				OffsetData.MagOffseting = true;
				LSM303_Start_Calib();
			}
			else if (rx.buf[3]==2)
			{
				OffsetData.MagOffseting = false;
				LSM303_Save_Calib();
				Write_config();	
			}
		}
	}
}

