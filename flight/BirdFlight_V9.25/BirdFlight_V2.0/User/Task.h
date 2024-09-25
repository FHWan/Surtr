#ifndef __TASK_H
#define __TASK_H
#include "os_app_hooks.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "stm32f4xx.h"
#include "includes.h"
#include "cpu.h"
#include "os.h"
#include "IMU_AHRS.h"
#include "MPU6500.h"
#include "MS5611.h"
#include "i2c.h"
#include "DronePara.h"
#include "Data_PC.h"
#include "Usart6toVision.h"
#include "Usart5toFlow.h"
#include "Data_deal.h"
#include "Visiondata_deal.h"
#include "digital_filter.h"
#include "Adc_Battery.h"
#include "Usart3toBluetooth.h"
#include "General_Gpio.h"
#include "PositionEstimation.h"
#include "SimpleDigitalFiltering.h"
#include "Attitude_control.h"
#include "Position_control.h"
#include "Calibrate.h"
#include "PPM.h"
#include "t265_deal.h"
#include "Uart4toTOF.h"
#include "TofMiniPlus.h"
#include "mathTool.h"
#include "matrix3.h"
#include "MahonyAHRS.h"
#include "Flow_deal.h"
#include <math.h>
#include <stdbool.h>
//信号量
extern OS_SEM DataDeal_proc;
extern OS_SEM FLOW_proc;
extern OS_SEM PPM_proc;
extern OS_SEM TOF_proc;
extern OS_SEM VIO_proc;

//全局外部变量
extern DroneFlightControl FlightControl;     							 
extern DroneRTInfo RT_Info;
extern DroneErrangle Errangle_Info;
extern DroneTargetInfo Target_Info;
extern RemoteControl RockerControl;
extern Controller Control_Info;
extern Remote_Control  Flight_Remote_Control;
extern OffsetInfo OffsetData;  
extern Data_Combine DataCombineflag; 
extern Thrust UAVThrust;											 
extern Throttle Throttle_Info;	           
extern SensorData Sensor_Info; 
//控制参数
extern PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalPosX,OriginalPosY,OriginalPosZ,
                    OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
                        OriginalFlowX,OriginalFlowY,OriginalFlowVelX,OriginalFlowVelY,
													OriginalAccZ;
extern PIDPara PID_ParaInfo;
//融合参数
extern KalmanFilter XAxis,YAxis,ZAxis,Barometer;
extern Butter_Parameter FlowX_Parameter;
extern Butter_Parameter FlowY_Parameter;
extern Butter_Parameter VIO_Parameter;
extern Butter_Parameter RotateX_Parameter;
extern Butter_Parameter RotateY_Parameter;
extern Butter_Parameter RotateZ_Parameter;
extern Butter_Parameter RotateFlowX_Parameter;
extern Butter_Parameter RotateFlowY_Parameter;
//extern Butter_Parameter MiniTof_Parameter;
//extern Butter_Parameter MiniTofVel_Parameter;

#endif 

