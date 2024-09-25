/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Task.c
 * ����   :������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Task.h"
/*ȫ�ֱ���*/
DroneFlightControl FlightControl;      //������״̬����
DroneRTInfo RT_Info;                   //������ʵʱ����
DroneErrangle Errangle_Info;           //������ƽ��У׼����
DroneTargetInfo Target_Info;           //������Ŀ���ȫ�ֱ���
RemoteControl RockerControl;           //�ֱ�����ȫ�ֱ���
Remote_Control  Flight_Remote_Control; //ң������������
Controller Control_Info;               //ң��������ȫ�ֱ���
OffsetInfo OffsetData;                 //��У׼����ȫ�ֱ���
Data_Combine DataCombineflag;      		 //�����ں��õ�������ȫ�ֱ���
SensorData Sensor_Info;                //��λ����������
Thrust UAVThrust;											 //������Ť������
Throttle Throttle_Info;								 //������Űٷֱ�
/*���Ʋ���*/
PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalPosX,OriginalPosY,OriginalPosZ,
                    OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
                        OriginalFlowX,OriginalFlowY,OriginalFlowVelX,OriginalFlowVelY,
												 OriginalAccZ;
PIDPara PID_ParaInfo;
/*�ںϲ���*/
KalmanFilter XAxis,YAxis,ZAxis,Barometer;


/**
 * @Description IMU���� 500HZ
 */
void IMU_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		/*��ȡIMU�����Ƕ�*/
		IMU_getInfo();
		OSTimeDlyHMSM(0,0,0,2,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

/*
 * @Description ��̬������ 500HZ
 */
void Attitude_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	CPU_SR_ALLOC();
	unsigned int fly_Pretime = 0;
	float PreparationPitch = 0;
  float PreparationRoll = 0;
	bool PreparationFlag = true;
	FlightControl.ControlStart = false;
	//DataCombineflag = Data_Follow;
	while(1){
		OS_CRITICAL_ENTER();																				// �����ٽ���
		if(FlightControl.OnOff==Drone_On  && ( (Sensor_Info.TofHeight >= 0.01f) || (RT_Info.VioVel_Z!=0) ) ){
			/*�ж��Ƿ�Ϊ�������ģʽ*/
			if(FlightControl.DroneMode == Drone_Mode_4Axis){						
				/*Ԥ�ɳ���*/
				if(fly_Pretime<500){
					fly_Pretime++;
					PreparationPitch += (RT_Info.Pitch - Errangle_Info.fixedErroPitch);
          PreparationRoll += (RT_Info.Roll - Errangle_Info.fixedErroRoll);
					PWM_OUTPUT(150,150,150,150);
				}
				else{
					if(PreparationFlag){
							PreparationPitch /= 500;
							PreparationRoll /= 500;
							PreparationFlag = false;
							Target_Info.Yaw = 0;
						  RT_Info.FlowX =0 ;
              RT_Info.FlowY =0 ;
							FlightControl.ControlStart = true;
					}
					if(FlightControl.ControlStart){
						Attitude_control(PreparationPitch,PreparationRoll);
						/*��������*/
						Safety_Protection();						
					}
				}
			}
			else{
				Attitude_control(0,0);
			}
		}
		else{
			/* �������� */
			PreparationFlag = true;
			PreparationPitch = 0;
			PreparationRoll = 0;
			fly_Pretime = 0;
			OriginalPitchRate.iOut = 0;
			OriginalRollRate.iOut = 0;
			OriginalYaw.iOut = 0;
			OriginalVelZ.iOut = 0;
			OriginalAccZ.iOut = 0;
			OriginalVelX.iOut = 0;
			OriginalVelY.iOut = 0;
			OriginalFlowVelX.iOut =0;
			OriginalFlowVelY.iOut =0;
			OriginalVelX.iOut =0;
			OriginalVelY.iOut =0;
			Target_Info.Height = 1.0f; //�ָ���ʼ��Ĭ��Ŀ��߶�
			Target_Info.Pitch = 0.0f; //�ָ���ʼ��Ĭ��Ŀ�긩��
			Target_Info.Roll = 0.0f; //�ָ���ʼ��Ĭ��Ŀ�귭��		
			Target_Info.Yaw = 0.0f;			
			Target_Info.RoutePlanX = 0.0f;
			Target_Info.RoutePlanY = 0.0f;
			Target_Info.RoutePlanZ = 1.0f;
			Target_Info.PositionX =0;
			Target_Info.PositionY =0;
			RT_Info.VioHeartbeat =0;
			FlightControl.LaunchFlag = true; //��һ����ɱ�־λ
			RT_Info.VioAbnormal = false;
			Flight_Remote_Control.FlightControlMode = VIOCruise ;
			DataCombineflag = Data_Follow;
			FlightControl.landFlag =0;
			FlightControl.ControlStart = false;
			FlightControl.poshold = 0;
			FlightControl.setTargetPos = 0;
//			Sensor_Info.FlowX=0;
//			Sensor_Info.FlowY=0;
			PWM_OUTPUT(0,0,0,0);
		}
		OS_CRITICAL_EXIT();																					// �˳��ٽ���
		OSTimeDlyHMSM(0,0,0,2,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

/**
 * @Description �ں����� 200HZ
 */
void Combine_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		/* ����׷�� */
		if(DataCombineflag == Data_Point){
				/*��������ϵ�ļ��ٶ�X����  ��Ӧ �����X�������� */
				POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
				RT_Info.PointX = XAxis.Axis_Pos;
				RT_Info.PointX_V = XAxis.Axis_Vel;

				/*��������ϵ�ļ��ٶ�Y����  ��Ӧ �����Y�������� */
				POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
				RT_Info.PointY = YAxis.Axis_Pos;
				RT_Info.PointY_V = YAxis.Axis_Vel;
		}
		/* Ѱ���� */
		else if(DataCombineflag == Data_Follow)
    {
//         /*��������ϵ�ļ��ٶ�Y����  ��Ӧ�����Y�������� */
//         POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
//         RT_Info.PointY = YAxis.Axis_Pos;
//         RT_Info.PointY_V = YAxis.Axis_Vel;
//         OpticalFlow_Estimation(Sensor_Info.FlowVelX /100,Sensor_Info.FlowVelY /100,RT_Info.AccX,-RT_Info.AccY);
//         RT_Info.FlowY += RT_Info.FlowY_V * 0.005f;
    }
		/* �������ݵĿ������˲��ں� */
		POS_KalmanFilter(&ZAxis,Sensor_Info.TofHeight,RT_Info.accZaxis);
		RT_Info.Height = ZAxis.Axis_Pos;
		RT_Info.Height_V = ZAxis.Axis_Vel;
		
		
//			//		/* ��ѹ�����ݵĿ������˲��ں� */
//			POS_KalmanFilter(&Barometer,Sensor_Info.TofHeight,RT_Info.accZaxis);
//	//		RT_Info.Barometer = Barometer.Axis_Pos;
//	//		RT_Info.Barometer_V = Barometer.Axis_Vel;
//			RT_Info.Barometer = Barometer.Axis_Pos;
//			RT_Info.Barometer_V = Barometer.Axis_Vel;
		
		
//			/* T265���ݵĿ������˲��ں� */
//			if( DataCombineflag == Data_Follow)
//			{
//				POS_KalmanFilter(&ZAxis,RT_Info.VioPosition_Z,RT_Info.accZaxis);
//				RT_Info.Height = ZAxis.Axis_Pos;
//				RT_Info.Height_V =  ZAxis.Axis_Vel;
////				RT_Info.Height_V = RT_Info.VioVel_Z;
//			}
//			else
//			{
////					RT_Info.Height = RT_Info.Barometer;
////					RT_Info.Height_V = RT_Info.Barometer_V;
//			}

			POS_KalmanFilter(&XAxis,Sensor_Info.FlowX,-RT_Info.AccX);
			RT_Info.FlowX = XAxis.Axis_Pos;
			RT_Info.FlowX_V = XAxis.Axis_Vel;

			/*��������ϵ�ļ��ٶ�Y����  ��Ӧ �����Y�������� */
			POS_KalmanFilter(&YAxis,-Sensor_Info.FlowY,-RT_Info.AccY);
			RT_Info.FlowY = YAxis.Axis_Pos;
			RT_Info.FlowY_V = YAxis.Axis_Vel;	
		
//		/* ��ѹ�����ݵĿ������˲��ں� */
//		POS_KalmanFilter(&Barometer,Sensor_Info.MS5611_Zaxis,RT_Info.accZaxis);
////		RT_Info.Barometer = Barometer.Axis_Pos;
////		RT_Info.Barometer_V = Barometer.Axis_Vel;
//		RT_Info.Height = Barometer.Axis_Pos;
//		RT_Info.Height_V = Barometer.Axis_Vel;
		
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

/**
 * @Description λ�ÿ��� 200HZ
 */
void Position_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	float Climbing = 0.002f;
  float Declining = 0.002f;
	Target_Info.Height = 1.0f;
	while(1)
	{
		if(FlightControl.DroneMode == Drone_Mode_4Axis  &&  FlightControl.OnOff==Drone_On  && FlightControl.ControlStart == true){
			Position_control(DataCombineflag,Climbing,Declining);
			if(RT_Info.VioHeartbeat >=100)
			{
					DataCombineflag = Data_Flow;
					RT_Info.VioAbnormal = true;
					FlightControl.poshold = 1;
					FlightControl.setTargetPos = 0;
					Target_Info.Yaw = RT_Info.Yaw;
					Target_Info.RoutePlanZ = 0.6f;
//					Target_Info.PositionX = 0;
//					Target_Info.PositionY = 0;
				  if(RT_Info.VioHeartbeat >=1500)
					{
						//FlightControl.landFlag=1;
					}

			}
			RT_Info.VioHeartbeat ++;
		}
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}



/**
 * @Description ң������������
 */
OS_SEM PPM_proc;
void PPM_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	OSSemCreate ((OS_SEM*)&PPM_proc,
								(CPU_CHAR*)"PPM_proc",
									(OS_SEM_CTR)1,
										(OS_ERR*)&err);
	while(1)
	{
		OSSemPend(&PPM_proc,0,OS_OPT_PEND_BLOCKING,0,&err);
		PPM_dataDeal();
	}
}


/**
 * @Description Flow���ݽ���
 */
OS_SEM FLOW_proc;
void Flow_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	static _Data_Rx Flow_data;
	//�����������ļ�
	OSSemCreate ((OS_SEM*)&FLOW_proc,
								(CPU_CHAR*)"FLOW_proc",
									(OS_SEM_CTR)1,
										(OS_ERR*)&err);
	while(1)
	{	
		OSSemPend (&FLOW_proc,0,OS_OPT_PEND_BLOCKING,0,&err);
		memcpy(Flow_data.buf,Flow_rx.buf,sizeof(Flow_rx.buf));
		Flow_data.len = Flow_rx.len;
		Flow_datadeal(Flow_data);
	}
}

/**
 * @Description VIO���ݽ���
 */
OS_SEM VIO_proc;
void VIO_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	static _Vio_Rx t265_data;
	//�����������ļ�
	OSSemCreate ((OS_SEM*)&VIO_proc,
								(CPU_CHAR*)"VIO_proc",
									(OS_SEM_CTR)1,
										(OS_ERR*)&err);
	while(1)
	{
		OSSemPend (&VIO_proc,0,OS_OPT_PEND_BLOCKING,0,&err);
		memcpy(t265_data.buf,t265_Rx.buf,sizeof(t265_Rx.buf));
		t265_data.len = t265_Rx.len;
		T265_DataDeal(t265_data);
	}
}


/**
 * @Description PC���ݽ���
 */
OS_SEM DataDeal_proc;//�ź���
void DataDeal_task(void *p_arg)
{
	static _Data_Rx PC_data;
	OS_ERR err;
	p_arg = p_arg;
	//�����ź���
	OSSemCreate ((OS_SEM*)&DataDeal_proc,
								(CPU_CHAR*)"DataDeal_proc",
									(OS_SEM_CTR)1,
										(OS_ERR*)&err);
	while(1)
	{
		OSSemPend (&DataDeal_proc,0,OS_OPT_PEND_BLOCKING,0,&err);
			memcpy(PC_data.buf,Bluetooth_rx.buf,sizeof(Bluetooth_rx.buf));
			PC_data.len = Bluetooth_rx.len;
			DataStitching(PC_data);		//��������ƴ��
	}
}



/**
 * @Description Usart1toPC���� 20HZ
 */
void Usart1toPC_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		if(FlightControl.ReportSW==Report_SET){
            sendParaInfo();
            FlightControl.ReportSW=Report_RESET;
        }else{
            if(OffsetData.MagOffseting){
                /*�ϴ�У׼����*/
                sendRTOffset();
            }
            else{
                sendRTInfo(); //�ϴ�ʵʱ����
							//	sendRemoteControlData();

            }
        }
				
		if( FlightControl.TakeOff == Complete_TakingOff &&  RT_Info.Height >= 0.1f ){
				SendTakeOffFlag();
			  FlightControl.TakeOff = Not_TakingOff;
		}
		
		
		if(	FlightControl.ArmPower ==	ArmPowerON  &&  RT_Info.CpuTick>=25)
		{
				SendT265StartFlag();
				RT_Info.CpuTick=0;
		}
		else if(FlightControl.ArmPower ==	ArmPowerON  &&  RT_Info.CpuTick<25)
		{				
				RT_Info.CpuTick ++;
		}
		
		OSTimeDlyHMSM(0,0,0,40,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}


/**
 * @Description TOF���� 
 */
OS_SEM TOF_proc;//�ź���
void TOF_task(void *p_arg)
{
	static _Data_Rx Tof_data;
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	OSSemCreate ((OS_SEM*)&TOF_proc,
								(CPU_CHAR*)"Tof_proc",
									(OS_SEM_CTR)1,
										(OS_ERR*)&err);
	while(1)
	{		
		OSSemPend (&TOF_proc,0,OS_OPT_PEND_BLOCKING,0,&err);
		// �����ٽ���
		OS_CRITICAL_ENTER();
		memcpy(Tof_data.buf,TOF_rx.buf,sizeof(TOF_rx.buf));
		Tof_data.len = TOF_rx.len;
		//TOF���⴫��������
		TOF_DataDeal(Tof_data);
		// �˳��ٽ���
		OS_CRITICAL_EXIT();	
	}
}


/**
 * @Description ��ص�ѹ���� 5HZ
 */
void Battery_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	float Battery_Array[5];
	while(1)
	{
		/* ��ȡ�˲���ĵ�ѹ */
		RT_Info.batteryVoltage = Average_Filter(Get_battery(),5,Battery_Array);
		/* ��ɵ�ѹ�������11.10V �ſ������ */
		if(RT_Info.batteryVoltage<11.10f && (FlightControl.OnOff != Drone_On))
		{
			RT_Info.lowPowerFlag = 1;
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		}
		else 
		{
			/*�����������ѹ����10.60V���Զ�����*/
			if(RT_Info.batteryVoltage < 10.60f)
			{
				FlightControl.landFlag = 1;
			}
			RT_Info.lowPowerFlag = 0;
		}		
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}
