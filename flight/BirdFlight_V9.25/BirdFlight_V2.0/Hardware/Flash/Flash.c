/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Flash.c
 * 描述   :内部Flash配置文件
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Flash.h"

FlashData flashData;
//读取指定地址的半字(16位数据) 
//faddr:读地址 
//返回值:对应数据.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  
//获取某个地址所在的flash扇区
//addr:flash地址
//返回值:0~11,即addr所在的扇区
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

//从指定地址开始写入指定长度的数据
//特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
//         写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
//         写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
//         没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写. 
//该函数对OTP区域也有效!可以用来写OTP区!
//OTP区域地址范围:0X1FFF7800~0X1FFF7A0F
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//非法地址
	FLASH_Unlock();									//解锁 
  FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存
 		
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	if(addrx<0X1FFF0000)			//只有主存储区,才需要执行擦除操作!!
	{
		while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
				if(status!=FLASH_COMPLETE)break;	//发生错误了
			}else addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//写数据
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(4位)数
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
}

//将当前配置写入flash
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
	
	if(flashData.isGood==0xA55A5AA5)//首地址正确
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
	else//第一次读写或首地址错误
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


