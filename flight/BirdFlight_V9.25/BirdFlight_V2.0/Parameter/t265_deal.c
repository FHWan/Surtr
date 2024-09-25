/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * ���� 	:Xiluna Tech
 * �ļ��� :t265_deal.c
 * ����   :����t265����������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
******************************************************************************/

#include "t265_deal.h"

Butter_Parameter VIO_Parameter;
Butter_BufferData  VIO_filter_buf[3];
Butter_Parameter RotateX_Parameter;
Butter_BufferData  RotateX_filter_buf[3];
Butter_Parameter RotateY_Parameter;
Butter_BufferData  RotateY_filter_buf[3];
Butter_Parameter RotateZ_Parameter;
Butter_BufferData  RotateZ_filter_buf[3];

/**********************************************************************************************************
*�� �� ��: T265_datadeal
*����˵��: �����Ӿ���̼�����
*��    ��: ��
*�� �� ֵ: Position
**********************************************************************************************************/
void T265_DataDeal(_Vio_Rx rx){
	//����״̬����
	float_union position_x,position_y,position_z,                       //����λ��
								velocity_x,velocity_y,velocity_z,										  //�����ٶ�
									Quaternion0,Quaternion1,Quaternion2,Quaternion3,	  //������̬
										reference_posx,reference_posy,reference_posz, 		//�ο�����
												rpy_yaw;                                       //������̬            
//											reference_velx,reference_vely,reference_velz,   //�ο��ٶ�
//												reference_accx,reference_accy,reference_accz; //�ο����ٶ�
	
	float RotateScale = 0.088f;
	float RotateX,RotateY =0;
	static float LastPosX,LastPosY,LastPosZ;
	unsigned char CheckSum=0;
	
	if(rx.buf[0]==0x55 && rx.buf[1]==0xAA && rx.buf[63]==0xAA){	
		for(unsigned char i=0;i<62;i++)
		{
			CheckSum += rx.buf[i];
		}
		
		if(rx.buf[2] == 0x10 &&  rx.buf[64] == CheckSum ){	
			//X��λ������
			position_x.cv[0] = rx.buf[3];
			position_x.cv[1] = rx.buf[4];
			position_x.cv[2] = rx.buf[5];
			position_x.cv[3] = rx.buf[6];
			//Y��λ������
			position_y.cv[0] = rx.buf[7];
			position_y.cv[1] = rx.buf[8];
			position_y.cv[2] = rx.buf[9];
			position_y.cv[3] = rx.buf[10];
			//Z��λ������
			position_z.cv[0] = rx.buf[11];
			position_z.cv[1] = rx.buf[12];
			position_z.cv[2] = rx.buf[13];
			position_z.cv[3] = rx.buf[14];
			//X���ٶ�����
			velocity_x.cv[0] = rx.buf[15];
			velocity_x.cv[1] = rx.buf[16];
			velocity_x.cv[2] = rx.buf[17];
			velocity_x.cv[3] = rx.buf[18];
			//Y���ٶ�����
			velocity_y.cv[0] = rx.buf[19];
			velocity_y.cv[1] = rx.buf[20];
			velocity_y.cv[2] = rx.buf[21];
			velocity_y.cv[3] = rx.buf[22];	
			//Z���ٶ�����
			velocity_z.cv[0] = rx.buf[23];
			velocity_z.cv[1] = rx.buf[24];
			velocity_z.cv[2] = rx.buf[25];
			velocity_z.cv[3] = rx.buf[26];
			//�Ӿ���̼Ƶ���̬����
			rpy_yaw.cv[0] = rx.buf[27];
			rpy_yaw.cv[1] = rx.buf[28];
			rpy_yaw.cv[2] = rx.buf[29];
			rpy_yaw.cv[3] = rx.buf[30];
			
			RT_Info.VioYaw   =  -rpy_yaw.fvalue *180 /PI;
			
//			Quaternion0.cv[0] = rx.buf[27];
//			Quaternion0.cv[1] = rx.buf[28];
//			Quaternion0.cv[2] = rx.buf[29];
//			Quaternion0.cv[3] = rx.buf[30];
			
			Quaternion1.cv[0] = rx.buf[31];
			Quaternion1.cv[1] = rx.buf[32];
			Quaternion1.cv[2] = rx.buf[33];
			Quaternion1.cv[3] = rx.buf[34];
			
			Quaternion2.cv[0] = rx.buf[35];
			Quaternion2.cv[1] = rx.buf[36];
			Quaternion2.cv[2] = rx.buf[37];
			Quaternion2.cv[3] = rx.buf[38];		
			
			Quaternion3.cv[0] = rx.buf[39];
			Quaternion3.cv[1] = rx.buf[40];
			Quaternion3.cv[2] = rx.buf[41];
			Quaternion3.cv[3] = rx.buf[42];		

	
			RT_Info.VioPosition_X = position_x.fvalue;
			RT_Info.VioPosition_Y = position_y.fvalue;
			RT_Info.VioPosition_Z = position_z.fvalue;
			

			RotateX = RotateScale *  Limits_data(  ((LPButterworth(RT_Info.GyroX,&RotateX_filter_buf[0],&RotateX_Parameter) )* PI/180) ,4.0f,-4.0f);
			RotateY = RotateScale *  Limits_data(  ((LPButterworth(RT_Info.GyroZ,&RotateY_filter_buf[0],&RotateY_Parameter)) * PI/180) ,4.0f,-4.0f);
			
			RT_Info.VioVel_X = LPButterworth((float)velocity_x.fvalue,&VIO_filter_buf[0],&VIO_Parameter) - RotateX;
			RT_Info.VioVel_Y = LPButterworth((float)velocity_y.fvalue,&VIO_filter_buf[1],&VIO_Parameter) + RotateY;
			RT_Info.VioVel_Z = LPButterworth((float)velocity_z.fvalue,&VIO_filter_buf[2],&VIO_Parameter);
			
			
			RT_Info.Quaternion0 = Quaternion0.fvalue;
			RT_Info.Quaternion1 = Quaternion1.fvalue;
			RT_Info.Quaternion2 = Quaternion2.fvalue;
			RT_Info.Quaternion3 = Quaternion3.fvalue;
										
			if(LastPosX!= RT_Info.VioPosition_X  && LastPosY!= RT_Info.VioPosition_Y  && LastPosZ!= RT_Info.VioPosition_Z )
					RT_Info.VioHeartbeat =0;
			
			LastPosX = RT_Info.VioPosition_X;
			LastPosY = RT_Info.VioPosition_Y;
			LastPosZ = RT_Info.VioPosition_Z;


																		
			if(rx.buf[43] == 0x20  && RT_Info.VioAbnormal == false  &&  FlightControl.landFlag==0)
			{
					//������λ������
					reference_posx.cv[0] = rx.buf[44];
					reference_posx.cv[1] = rx.buf[45];
					reference_posx.cv[2] = rx.buf[46];
					reference_posx.cv[3] = rx.buf[47];

					reference_posy.cv[0] = rx.buf[48];
					reference_posy.cv[1] = rx.buf[49];
					reference_posy.cv[2] = rx.buf[50];
					reference_posy.cv[3] = rx.buf[51];

					reference_posz.cv[0] = rx.buf[52];
					reference_posz.cv[1] = rx.buf[53];
					reference_posz.cv[2] = rx.buf[54];
					reference_posz.cv[3] = rx.buf[55];
							
					Target_Info.RoutePlanX =reference_posx.fvalue;
					Target_Info.RoutePlanY =reference_posy.fvalue;
					Target_Info.RoutePlanZ =reference_posz.fvalue;
			}		
			
			
			FlightControl.ArmPower =	ArmPowerOFF;
			
			// ����·��Ѳ����ɺ��յ����������
			if(rx.buf[62]==0xA5)
			{
				  FlightControl.landFlag=1;
			}		
		}
		
		else if(rx.buf[2]==0xFF 	){		
				FlightControl.ArmPower =	ArmPowerON;	
		}		
	}
}



/**********************************************************************************************************
*�� �� ��: SendTakeOffFlag
*����˵��: ������ɱ�־���߶�ARM������
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void SendTakeOffFlag(void){
	u8 dataToARM[11] = "Departures\n";	
	Usart6_tx(dataToARM,sizeof(dataToARM));
}


/**********************************************************************************************************
*�� �� ��: SendT265StartFlag
*����˵��: ��������˫Ŀ�Ӿ�������߶�ARM������
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void SendT265StartFlag(void){
	u8 dataToARM[9] = "Start265\n";	
	Usart6_tx(dataToARM,sizeof(dataToARM));
}



/**********************************************************************************************************
*�� �� ��: RestartT265
*����˵��: ��������˫Ŀ�Ӿ�������߶�ARM������
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void RestartT265(void){
	u8 dataToARM[11] = "Refresh265\n";	
	Usart6_tx(dataToARM,sizeof(dataToARM));
}

