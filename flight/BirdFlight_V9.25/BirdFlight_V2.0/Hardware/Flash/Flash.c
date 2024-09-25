/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Flash.c
 * ����   :�ڲ�Flash�����ļ�
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Flash.h"

FlashData flashData;
//��ȡָ����ַ�İ���(16λ����) 
//faddr:����ַ 
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  
//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}

//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
//         д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
//         д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
//         û����Ҫ����,��������������Ȳ�����,Ȼ����������д. 
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//�Ƿ���ַ
	FLASH_Unlock();									//���� 
  FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���
 		
	addrx=WriteAddr;				//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ
	if(addrx<0X1FFF0000)			//ֻ�����洢��,����Ҫִ�в�������!!
	{
		while(addrx<endaddr)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V֮��!!
				if(status!=FLASH_COMPLETE)break;	//����������
			}else addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//д����
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//д������
			{ 
				break;	//д���쳣
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
	FLASH_Lock();//����
} 

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(4λ)��
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
}

//����ǰ����д��flash
void Write_config(void)
{																
	u32 *ptr = &flashData.isGood;
	flashData.pidPara=PID_ParaInfo;
	flashData.Offset_Data = OffsetData;
	flashData.ControlData = Control_Info;
//	flashData.Errangle=Errangle_Info;
	STMFLASH_Write(0X080E0004,ptr,sizeof(flashData));   //0X080E0004
}

void Load_config(void){
	
	u32 *ptr = &flashData.isGood;
	STMFLASH_Read(0X080E0004,ptr,sizeof(flashData));
	
	if(flashData.isGood==0xA55A5AA5)//�׵�ַ��ȷ
	{		
				PID_ParaInfo.Pitch.Kp=flashData.pidPara.Pitch.Kp ;
        PID_ParaInfo.Pitch.Ki=flashData.pidPara.Pitch.Ki ;
        PID_ParaInfo.Pitch.Kd=flashData.pidPara.Pitch.Kd ;

        PID_ParaInfo.Roll.Kp=flashData.pidPara.Roll.Kp;
        PID_ParaInfo.Roll.Ki=flashData.pidPara.Roll.Ki;
        PID_ParaInfo.Roll.Kd=flashData.pidPara.Roll.Kd;

        PID_ParaInfo.Yaw.Kp=flashData.pidPara.Yaw.Kp;
        PID_ParaInfo.Yaw.Ki=flashData.pidPara.Yaw.Ki;
        PID_ParaInfo.Yaw.Kd=flashData.pidPara.Yaw.Kd;

        PID_ParaInfo.PitchRate.Kp=flashData.pidPara.PitchRate.Kp;
        PID_ParaInfo.PitchRate.Ki=flashData.pidPara.PitchRate.Ki;
        PID_ParaInfo.PitchRate.Kd=flashData.pidPara.PitchRate.Kd;

        PID_ParaInfo.RollRate.Kp=flashData.pidPara.RollRate.Kp;
        PID_ParaInfo.RollRate.Ki=flashData.pidPara.RollRate.Ki;
        PID_ParaInfo.RollRate.Kd=flashData.pidPara.RollRate.Kd;

        PID_ParaInfo.YawRate.Kp=flashData.pidPara.YawRate.Kp;
        PID_ParaInfo.YawRate.Ki=flashData.pidPara.YawRate.Ki;
        PID_ParaInfo.YawRate.Kd=flashData.pidPara.YawRate.Kd;

        PID_ParaInfo.PosX.Kp=flashData.pidPara.PosX.Kp;
        PID_ParaInfo.PosX.Ki=flashData.pidPara.PosX.Ki;
        PID_ParaInfo.PosX.Kd=flashData.pidPara.PosX.Kd;

        PID_ParaInfo.PosY.Kp=flashData.pidPara.PosY.Kp;
        PID_ParaInfo.PosY.Ki=flashData.pidPara.PosY.Ki;
        PID_ParaInfo.PosY.Kd=flashData.pidPara.PosY.Kd;

        PID_ParaInfo.PosZ.Kp=flashData.pidPara.PosZ.Kp;
        PID_ParaInfo.PosZ.Ki=flashData.pidPara.PosZ.Ki;
        PID_ParaInfo.PosZ.Kd=flashData.pidPara.PosZ.Kd;

        PID_ParaInfo.VelX.Kp=flashData.pidPara.VelX.Kp;
        PID_ParaInfo.VelX.Ki=flashData.pidPara.VelX.Ki;
        PID_ParaInfo.VelX.Kd=flashData.pidPara.VelX.Kd;

        PID_ParaInfo.VelY.Kp=flashData.pidPara.VelY.Kp;
        PID_ParaInfo.VelY.Ki=flashData.pidPara.VelY.Ki;
        PID_ParaInfo.VelY.Kd=flashData.pidPara.VelY.Kd;

        PID_ParaInfo.VelZ.Kp=flashData.pidPara.VelZ.Kp;
        PID_ParaInfo.VelZ.Ki=flashData.pidPara.VelZ.Ki;
        PID_ParaInfo.VelZ.Kd=flashData.pidPara.VelZ.Kd;

        PID_ParaInfo.AccZ.Kp=flashData.pidPara.AccZ.Kp;
        PID_ParaInfo.AccZ.Ki=flashData.pidPara.AccZ.Ki;
        PID_ParaInfo.AccZ.Kd=flashData.pidPara.AccZ.Kd;

        PID_ParaInfo.FlowX.Kp=flashData.pidPara.FlowX.Kp;
        PID_ParaInfo.FlowX.Ki=flashData.pidPara.FlowX.Ki;
        PID_ParaInfo.FlowX.Kd=flashData.pidPara.FlowX.Kd;

        PID_ParaInfo.FlowY.Kp=flashData.pidPara.FlowY.Kp;
        PID_ParaInfo.FlowY.Ki=flashData.pidPara.FlowY.Ki;
        PID_ParaInfo.FlowY.Kd=flashData.pidPara.FlowY.Kd;

        PID_ParaInfo.FlowVelX.Kp=flashData.pidPara.FlowVelX.Kp;
        PID_ParaInfo.FlowVelX.Ki=flashData.pidPara.FlowVelX.Ki;
        PID_ParaInfo.FlowVelX.Kd=flashData.pidPara.FlowVelX.Kd;

        PID_ParaInfo.FlowVelY.Kp=flashData.pidPara.FlowVelY.Kp;
        PID_ParaInfo.FlowVelY.Ki=flashData.pidPara.FlowVelY.Ki;
        PID_ParaInfo.FlowVelY.Kd=flashData.pidPara.FlowVelY.Kd;

        OffsetData.MagX = flashData.Offset_Data.MagX;
        OffsetData.MagY = flashData.Offset_Data.MagY;
        OffsetData.MagZ = flashData.Offset_Data.MagZ;

        OffsetData.GyroX = flashData.Offset_Data.GyroX;
        OffsetData.GyroY = flashData.Offset_Data.GyroY;
        OffsetData.GyroZ = flashData.Offset_Data.GyroZ;

        OffsetData.AccX = flashData.Offset_Data.AccX;
        OffsetData.AccY = flashData.Offset_Data.AccY;
        OffsetData.AccZ = flashData.Offset_Data.AccZ;

        OffsetData.AccXScale = flashData.Offset_Data.AccXScale;
        OffsetData.AccYScale = flashData.Offset_Data.AccYScale;
        OffsetData.AccZScale = flashData.Offset_Data.AccZScale;

        Control_Info.CH1_Max = flashData.ControlData.CH1_Max;
        Control_Info.CH1_Min = flashData.ControlData.CH1_Min;
        Control_Info.CH1_Mid = (Control_Info.CH1_Max + Control_Info.CH1_Min)/2;
        Control_Info.CH2_Max = flashData.ControlData.CH2_Max;
        Control_Info.CH2_Min = flashData.ControlData.CH2_Min;
        Control_Info.CH2_Mid = (Control_Info.CH2_Max + Control_Info.CH2_Min)/2;
        Control_Info.CH3_Max = flashData.ControlData.CH3_Max;
        Control_Info.CH3_Min = flashData.ControlData.CH3_Min;
        Control_Info.CH3_Mid = (Control_Info.CH3_Max + Control_Info.CH3_Min)/2;
        Control_Info.CH4_Max = flashData.ControlData.CH4_Max;
        Control_Info.CH4_Min = flashData.ControlData.CH4_Min;
        Control_Info.CH4_Mid = (Control_Info.CH4_Max + Control_Info.CH4_Min)/2;
        Control_Info.CH5_Max = flashData.ControlData.CH5_Max;
        Control_Info.CH5_Min = flashData.ControlData.CH5_Min;
        Control_Info.CH5_Mid = (Control_Info.CH5_Max + Control_Info.CH5_Min)/2;
        Control_Info.CH6_Max = flashData.ControlData.CH6_Max;
        Control_Info.CH6_Min = flashData.ControlData.CH6_Min;
        Control_Info.CH6_Mid = (Control_Info.CH6_Max + Control_Info.CH6_Min)/2;
        Control_Info.CH7_Max = flashData.ControlData.CH7_Max;
        Control_Info.CH7_Min = flashData.ControlData.CH7_Min;
        Control_Info.CH7_Mid = (Control_Info.CH7_Max + Control_Info.CH7_Min)/2;
        Control_Info.CH8_Max = flashData.ControlData.CH8_Max;
        Control_Info.CH8_Min = flashData.ControlData.CH8_Min;
        Control_Info.CH8_Mid = (Control_Info.CH8_Max + Control_Info.CH8_Min)/2;
		
	}
	else//��һ�ζ�д���׵�ַ����
	{
		flashData.isGood=0xA55A5AA5;
		PID_ParaInfo.Pitch.Kp=flashData.pidPara.Pitch.Kp=  -0.06f;
		PID_ParaInfo.Pitch.Ki=flashData.pidPara.Pitch.Ki = 0;
		PID_ParaInfo.Pitch.Kd=flashData.pidPara.Pitch.Kd = 0;

		PID_ParaInfo.Roll.Kp=flashData.pidPara.Roll.Kp = 0.06f;
		PID_ParaInfo.Roll.Ki=flashData.pidPara.Roll.Ki = 0;
		PID_ParaInfo.Roll.Kd=flashData.pidPara.Roll.Kd = 0;

		PID_ParaInfo.Yaw.Kp=flashData.pidPara.Yaw.Kp = 0.03f;
		PID_ParaInfo.Yaw.Ki=flashData.pidPara.Yaw.Ki = 0;
		PID_ParaInfo.Yaw.Kd=flashData.pidPara.Yaw.Kd = 0;

		PID_ParaInfo.PitchRate.Kp=flashData.pidPara.PitchRate.Kp = 160.0f;
		PID_ParaInfo.PitchRate.Ki=flashData.pidPara.PitchRate.Ki = 2.0f;
		PID_ParaInfo.PitchRate.Kd=flashData.pidPara.PitchRate.Kd = 8.0f;

		PID_ParaInfo.RollRate.Kp=flashData.pidPara.RollRate.Kp = 160.0f;
		PID_ParaInfo.RollRate.Ki=flashData.pidPara.RollRate.Ki = 2.0f;
		PID_ParaInfo.RollRate.Kd=flashData.pidPara.RollRate.Kd = 8.0f;

		PID_ParaInfo.YawRate.Kp=flashData.pidPara.YawRate.Kp = 100.0f;
		PID_ParaInfo.YawRate.Ki=flashData.pidPara.YawRate.Ki = 0.2f;
		PID_ParaInfo.YawRate.Kd=flashData.pidPara.YawRate.Kd = 2.0f;

		PID_ParaInfo.PosX.Kp=flashData.pidPara.PosX.Kp = -0.6f;
		PID_ParaInfo.PosX.Ki=flashData.pidPara.PosX.Ki = 0;
		PID_ParaInfo.PosX.Kd=flashData.pidPara.PosX.Kd = 0;

		PID_ParaInfo.PosY.Kp=flashData.pidPara.PosY.Kp = -0.6f;
		PID_ParaInfo.PosY.Ki=flashData.pidPara.PosY.Ki = 0;
		PID_ParaInfo.PosY.Kd=flashData.pidPara.PosY.Kd = 0;

		PID_ParaInfo.PosZ.Kp=flashData.pidPara.PosZ.Kp = 0.95f;
		PID_ParaInfo.PosZ.Ki=flashData.pidPara.PosZ.Ki = 0;
		PID_ParaInfo.PosZ.Kd=flashData.pidPara.PosZ.Kd = 0;

		PID_ParaInfo.VelX.Kp=flashData.pidPara.VelX.Kp = -17.0f;
		PID_ParaInfo.VelX.Ki=flashData.pidPara.VelX.Ki = -0.02f;
		PID_ParaInfo.VelX.Kd=flashData.pidPara.VelX.Kd = 0.0f;

		PID_ParaInfo.VelY.Kp=flashData.pidPara.VelY.Kp = -17.0f;
		PID_ParaInfo.VelY.Ki=flashData.pidPara.VelY.Ki = -0.02f;
		PID_ParaInfo.VelY.Kd=flashData.pidPara.VelY.Kd = 0.0f;

		PID_ParaInfo.VelZ.Kp=flashData.pidPara.VelZ.Kp = 6.0f;
		PID_ParaInfo.VelZ.Ki=flashData.pidPara.VelZ.Ki = 0.05f;
		PID_ParaInfo.VelZ.Kd=flashData.pidPara.VelZ.Kd = 0;

		PID_ParaInfo.AccZ.Kp=flashData.pidPara.AccZ.Kp = 2.5f;
		PID_ParaInfo.AccZ.Ki=flashData.pidPara.AccZ.Ki = 0.05f;
		PID_ParaInfo.AccZ.Kd=flashData.pidPara.AccZ.Kd = 0;

		PID_ParaInfo.FlowX.Kp=flashData.pidPara.FlowX.Kp =-0.4f;
		PID_ParaInfo.FlowX.Ki=flashData.pidPara.FlowX.Ki =0;
		PID_ParaInfo.FlowX.Kd=flashData.pidPara.FlowX.Kd =0;

		PID_ParaInfo.FlowY.Kp=flashData.pidPara.FlowY.Kp =-0.4f;
		PID_ParaInfo.FlowY.Ki=flashData.pidPara.FlowY.Ki =0;
		PID_ParaInfo.FlowY.Kd=flashData.pidPara.FlowY.Kd =0;

		PID_ParaInfo.FlowVelX.Kp=flashData.pidPara.FlowVelX.Kp =-14.0f;
		PID_ParaInfo.FlowVelX.Ki=flashData.pidPara.FlowVelX.Ki =-0.05f;
		PID_ParaInfo.FlowVelX.Kd=flashData.pidPara.FlowVelX.Kd =-0.6f;

		PID_ParaInfo.FlowVelY.Kp=flashData.pidPara.FlowVelY.Kp =-14.0f;
		PID_ParaInfo.FlowVelY.Ki=flashData.pidPara.FlowVelY.Ki =-0.05f;
		PID_ParaInfo.FlowVelY.Kd=flashData.pidPara.FlowVelY.Kd =-0.6f;

		OffsetData.MagX = flashData.Offset_Data.MagX = 0;
		OffsetData.MagY = flashData.Offset_Data.MagY = 0;
		OffsetData.MagZ = flashData.Offset_Data.MagZ = 0;

		OffsetData.GyroX = flashData.Offset_Data.GyroX = 0;
		OffsetData.GyroY = flashData.Offset_Data.GyroY = 0;
		OffsetData.GyroZ = flashData.Offset_Data.GyroZ = 0;

		OffsetData.AccX = flashData.Offset_Data.AccX =0;
		OffsetData.AccY = flashData.Offset_Data.AccY =0;
		OffsetData.AccZ = flashData.Offset_Data.AccZ =0;

		OffsetData.AccXScale = flashData.Offset_Data.AccXScale =1;
		OffsetData.AccYScale = flashData.Offset_Data.AccYScale =1;
		OffsetData.AccZScale = flashData.Offset_Data.AccZScale =1;

		Control_Info.CH1_Max = 1938;
		Control_Info.CH1_Min = 1100;
		Control_Info.CH1_Mid = 1520;
		Control_Info.CH2_Max = 1938;
		Control_Info.CH2_Min = 1100;
		Control_Info.CH2_Mid = 1520;
		Control_Info.CH3_Max = 1938;
		Control_Info.CH3_Min = 1100;
		Control_Info.CH3_Mid = 1520;
		Control_Info.CH4_Max = 1938;
		Control_Info.CH4_Min = 1100;
		Control_Info.CH4_Mid = 1520;
		Control_Info.CH5_Max = 1938;
		Control_Info.CH5_Min = 1100;
		Control_Info.CH5_Mid = 1520;
		Control_Info.CH6_Max = 1938;
		Control_Info.CH6_Min = 1100;
		Control_Info.CH6_Mid = 1520;
		Control_Info.CH7_Max = 1938;
		Control_Info.CH7_Min = 1100;
		Control_Info.CH7_Mid = 1520;
		Control_Info.CH8_Max = 1938;
		Control_Info.CH8_Min = 1100;
		Control_Info.CH8_Mid = 1520;
	
		Write_config();	
	}
}


