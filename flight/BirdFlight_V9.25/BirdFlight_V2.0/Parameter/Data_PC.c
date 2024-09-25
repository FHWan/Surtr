/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Data_PC.c
 * 描述   :上传PC端数据格式
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Data_PC.h"

void sendParaInfo(void)
{
	u8 paraToPC[207];
	u8 floatToHex[4];	

	paraToPC[0]=0X55;
	paraToPC[1]=0XAA;
	paraToPC[2]=0XF1;

	/* Pitch PidPara */
	FloatToByte(PID_ParaInfo.Pitch.Kp,floatToHex);
	arrycat(paraToPC,3,floatToHex,4);
	FloatToByte(PID_ParaInfo.Pitch.Ki,floatToHex);
	arrycat(paraToPC,7,floatToHex,4);
	FloatToByte(PID_ParaInfo.Pitch.Kd,floatToHex);
	arrycat(paraToPC,11,floatToHex,4);

	/* Roll PidPara */
	FloatToByte(PID_ParaInfo.Roll.Kp,floatToHex);
	arrycat(paraToPC,15,floatToHex,4);
	FloatToByte(PID_ParaInfo.Roll.Ki,floatToHex);
	arrycat(paraToPC,19,floatToHex,4);
	FloatToByte(PID_ParaInfo.Roll.Kd,floatToHex);
	arrycat(paraToPC,23,floatToHex,4);
	
	/* ratePitch PidPara */
	FloatToByte(PID_ParaInfo.PitchRate.Kp,floatToHex);
	arrycat(paraToPC,27,floatToHex,4);
	FloatToByte(PID_ParaInfo.PitchRate.Ki,floatToHex);
	arrycat(paraToPC,31,floatToHex,4);
	FloatToByte(PID_ParaInfo.PitchRate.Kd,floatToHex);
	arrycat(paraToPC,35,floatToHex,4);

	/* rateRoll PidPara */
	FloatToByte(PID_ParaInfo.RollRate.Kp,floatToHex);
	arrycat(paraToPC,39,floatToHex,4);
	FloatToByte(PID_ParaInfo.RollRate.Ki,floatToHex);
	arrycat(paraToPC,43,floatToHex,4);
	FloatToByte(PID_ParaInfo.RollRate.Kd,floatToHex);
	arrycat(paraToPC,47,floatToHex,4);

	/* Yaw PidPara */
	FloatToByte(PID_ParaInfo.Yaw.Kp,floatToHex);
	arrycat(paraToPC,51,floatToHex,4);
	FloatToByte(PID_ParaInfo.Yaw.Ki,floatToHex);
	arrycat(paraToPC,55,floatToHex,4);
	FloatToByte(PID_ParaInfo.Yaw.Kd,floatToHex);
	arrycat(paraToPC,59,floatToHex,4);
	
	/* rateYaw PidPara */
	FloatToByte(PID_ParaInfo.YawRate.Kp,floatToHex);
	arrycat(paraToPC,63,floatToHex,4);
	FloatToByte(PID_ParaInfo.YawRate.Ki,floatToHex);
	arrycat(paraToPC,67,floatToHex,4);
	FloatToByte(PID_ParaInfo.YawRate.Kd,floatToHex);
	arrycat(paraToPC,71,floatToHex,4);
	
	/* Height PidPara */
	FloatToByte(PID_ParaInfo.PosZ.Kp,floatToHex);
	arrycat(paraToPC,75,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosZ.Ki,floatToHex);
	arrycat(paraToPC,79,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosZ.Kd,floatToHex);
	arrycat(paraToPC,83,floatToHex,4);

	/* VelHeight PidPara */
	FloatToByte(PID_ParaInfo.VelZ.Kp,floatToHex);
	arrycat(paraToPC,87,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelZ.Ki,floatToHex);
	arrycat(paraToPC,91,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelZ.Kd,floatToHex);
	arrycat(paraToPC,95,floatToHex,4);
	
	/* PositionX PidPara */
	FloatToByte(PID_ParaInfo.PosX.Kp,floatToHex);
	arrycat(paraToPC,99,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosX.Ki,floatToHex);
	arrycat(paraToPC,103,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosX.Kd,floatToHex);
	arrycat(paraToPC,107,floatToHex,4);
	
	/* PositionY PidPara */
	FloatToByte(PID_ParaInfo.PosY.Kp,floatToHex);
	arrycat(paraToPC,111,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosY.Ki,floatToHex);
	arrycat(paraToPC,115,floatToHex,4);
	FloatToByte(PID_ParaInfo.PosY.Kd,floatToHex);
	arrycat(paraToPC,119,floatToHex,4);
	
	/* SpeedX PidPara */
	FloatToByte(PID_ParaInfo.VelX.Kp,floatToHex);
	arrycat(paraToPC,123,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelX.Ki,floatToHex);
	arrycat(paraToPC,127,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelX.Kd,floatToHex);
	arrycat(paraToPC,131,floatToHex,4);
	
	/* SpeedY PidPara */
	FloatToByte(PID_ParaInfo.VelY.Kp,floatToHex);
	arrycat(paraToPC,135,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelY.Ki,floatToHex);
	arrycat(paraToPC,139,floatToHex,4);
	FloatToByte(PID_ParaInfo.VelY.Kd,floatToHex);
	arrycat(paraToPC,143,floatToHex,4);
	
	/* FlowX PidPara */
	FloatToByte(PID_ParaInfo.FlowX.Kp,floatToHex);
	arrycat(paraToPC,147,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowX.Ki,floatToHex);
	arrycat(paraToPC,151,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowX.Kd,floatToHex);
	arrycat(paraToPC,155,floatToHex,4);
	
	/* FlowY PidPara */
	FloatToByte(PID_ParaInfo.FlowY.Kp,floatToHex);
	arrycat(paraToPC,159,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowY.Ki,floatToHex);
	arrycat(paraToPC,163,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowY.Kd,floatToHex);
	arrycat(paraToPC,167,floatToHex,4);
	
	/* FlowVelX PidPara */
	FloatToByte(PID_ParaInfo.FlowVelX.Kp,floatToHex);
	arrycat(paraToPC,171,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowVelX.Ki,floatToHex);
	arrycat(paraToPC,175,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowVelX.Kd,floatToHex);
	arrycat(paraToPC,179,floatToHex,4);
	
	/* FlowVelY PidPara */
	FloatToByte(PID_ParaInfo.FlowVelY.Kp,floatToHex);
	arrycat(paraToPC,183,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowVelY.Ki,floatToHex);
	arrycat(paraToPC,187,floatToHex,4);
	FloatToByte(PID_ParaInfo.FlowVelY.Kd,floatToHex);
	arrycat(paraToPC,191,floatToHex,4);
	
	/* AccZ PidPara */
	FloatToByte(PID_ParaInfo.AccZ.Kp,floatToHex);
	arrycat(paraToPC,195,floatToHex,4);
	FloatToByte(PID_ParaInfo.AccZ.Ki,floatToHex);
	arrycat(paraToPC,199,floatToHex,4);
	FloatToByte(PID_ParaInfo.AccZ.Kd,floatToHex);
	arrycat(paraToPC,203,floatToHex,4);
	

		Uart3_tx(paraToPC,207);
		
}


/*上传实时信息*/
void sendRTInfo(void)
{
  float temp;
	u8 floatToHex[4];		
	u8 dataToPC[55];	

	dataToPC[0]=0X55;
	dataToPC[1]=0XAA;
	dataToPC[2]=0XF0;
		
  temp = RT_Info.Pitch ;//- Errangle_Info.fixedErroPitch;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,3,floatToHex,4);

	temp = RT_Info.Roll ;// - Errangle_Info.fixedErroRoll;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,7,floatToHex,4);
	
	temp = RT_Info.VioYaw;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,11,floatToHex,4);
	
	temp = RT_Info.Height;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,15,floatToHex,4);

	temp = RT_Info.batteryVoltage;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,19,floatToHex,4);
	
	temp = RT_Info.Height_V * 100;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,23,floatToHex,4);
	
	temp = RT_Info.PointX;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,27,floatToHex,4);
	
	temp = RT_Info.PointY;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,31,floatToHex,4);
	
	temp = RT_Info.FlowX_V*100 ;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,35,floatToHex,4);
	
	temp = RT_Info.FlowY_V*100 ;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,39,floatToHex,4);
	
	temp = Sensor_Info.FixFlowX*100 ;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,43,floatToHex,4);
	
	temp = RT_Info.VioPosition_X*100 ;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,47,floatToHex,4);
	
	temp = RT_Info.VioPosition_Y*100;
	FloatToByte(temp,floatToHex);
	arrycat(dataToPC,51,floatToHex,4);
	

		Uart3_tx(dataToPC,55);
	}

/* 上传遥控器数据 */
void sendRemoteControlData(void)
{
	int16_t temp;
	unsigned char temp1;
	u8 intToHex[2];		
	u8 dataToPC[128];	
	u8 i=0;
	
	dataToPC[0]=0X55;
	dataToPC[1]=0XAA;
	dataToPC[2]=0XF2;
		
	temp = Control_Info.CH1;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,3,intToHex,2);
	
	temp = Control_Info.CH2;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,5,intToHex,2);
	
	temp = Control_Info.CH3;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,7,intToHex,2);
	
	temp = Control_Info.CH4;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,9,intToHex,2);
	
	temp = Control_Info.CH5;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,11,intToHex,2);
	
	temp = Control_Info.CH6;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,13,intToHex,2);
	
  temp = Control_Info.CH7;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,15,intToHex,2);
	
	
	temp1 =  Flight_Remote_Control.CH5_Mode1;
	arrycat(dataToPC,17,&temp1,1);
	temp1 =  Flight_Remote_Control.CH5_Mode2;
	arrycat(dataToPC,18,&temp1,1);
	temp1 =  Flight_Remote_Control.CH5_Mode3;
	arrycat(dataToPC,19,&temp1,1);
	
	temp1 =  Flight_Remote_Control.CH6_Mode1;
	arrycat(dataToPC,20,&temp1,1);
	temp1 =  Flight_Remote_Control.CH6_Mode2;
	arrycat(dataToPC,21,&temp1,1);
	
	temp1 =  Flight_Remote_Control.CH7_Mode1;
	arrycat(dataToPC,22,&temp1,1);
	temp1 =  Flight_Remote_Control.CH7_Mode2;
	arrycat(dataToPC,23,&temp1,1);
	
	temp = Flight_Remote_Control.SafeThrottle;
	IntToByte(temp,intToHex);
	arrycat(dataToPC,24,intToHex,2);
	
	
	for(i=0;i<26;i++)
	{
		dataToPC[26]+=dataToPC[i];
	}
	
		Uart3_tx(dataToPC,27);
}


/*上传磁校准数据*/
void sendRTOffset(void)
{
    int temp;
    unsigned char dataToPC[16];

    dataToPC[0]=0X55;
    dataToPC[1]=0XAA;
    dataToPC[2]=0X25;

    temp = Mag_minx;
    dataToPC[3] = temp & 0x00ff ;
    dataToPC[4] = (temp  & 0xff00 ) >>8 ;

    temp = Mag_maxx;
    dataToPC[5] = temp & 0x00ff;
    dataToPC[6] = (temp  & 0xff00 ) >>8;

    temp = Mag_miny;
    dataToPC[7] =  temp & 0x00ff;
    dataToPC[8] = (temp  & 0xff00 ) >>8;

    temp = Mag_maxy;
    dataToPC[9] =  temp & 0x00ff;
    dataToPC[10] = (temp  & 0xff00 ) >>8;

    temp = Mag_minz;
    dataToPC[11] =  temp & 0x00ff;
    dataToPC[12] = (temp  & 0xff00 ) >>8;

    temp = Mag_maxz;
    dataToPC[13] =  temp & 0x00ff;
    dataToPC[14] = (temp  & 0xff00 ) >>8;

    dataToPC[15] = 0xAA;

			Uart3_tx(dataToPC,27);

}
