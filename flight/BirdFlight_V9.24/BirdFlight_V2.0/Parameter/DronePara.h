#ifndef __DRONWPARA_H
#define __DRONWPARA_H

#include "stm32f4xx.h"
#include <stdbool.h>
#define TX_LEN  207
#define RX_LEN  512
#define Gravity_acceleration  9.81f

//定义姿态数据来源
#define VIO_Attitude
//#define IMU_Attitude

//定义机型
#define Model330
#ifdef Model330
    #define ARM_Length 0.165
    #define Drone_Mass 1.25f
    #define Drag_Coeff 0.016f
    //转动惯量设置  转动惯量 = M*R^2  对于质点而言。这里无法测得转动惯量大小，变为一个可调参数设置
    #define Inertia_Wx    0.002f
    #define Inertia_Wy    0.002f
    #define Inertia_Wz    0.004f
#else
    #define ARM_Length 0.105f
    #define Drone_Mass 0.64f
    #define Drag_Coeff 0.016f
    //转动惯量设置  转动惯量 = M*R^2  对于质点而言。这里无法测得转动惯量大小，变为一个可调参数设置
    #define Inertia_Wx    0.001f
    #define Inertia_Wy    0.001f
    #define Inertia_Wz    0.002f
#endif

typedef struct {
    float x;
    float y;
    float z;
} Vector3f_t;


typedef enum{
  Drone_Mode_None=0,
  Drone_Mode_RatePitch, //姿态内环
  Drone_Mode_RateRoll,
  Drone_Mode_Pitch,     //姿态外环
  Drone_Mode_Roll,
  Drone_Mode_4Axis,     //四轴飞行
}DroneFlightMode_TypeDef;

typedef enum
{  
	Drone_Off  = 0x00,//起飞或者调试打开电机
  Drone_On   = 0x01,//关闭电机
  Drone_Land = 0x02,//降落	
}DroneFlightOnOff_TypeDef;

typedef enum
{  
	Report_SET      = 0x01,
  Report_RESET    = 0x00, 		 	
}DroneReportSW_TypeDef;

typedef enum{
	Not_TakingOff   = 0x00,   
	Complete_TakingOff  = 0x01,
}DroneTakeOff_TypeDef;

typedef enum{
	ArmPowerOFF  = 0x00,   
	ArmPowerON  = 0x01,
}ArmPowerStatus_TypeDef;

typedef struct
{
	DroneFlightOnOff_TypeDef OnOff;
	DroneFlightMode_TypeDef DroneMode;
	DroneReportSW_TypeDef ReportSW;
	DroneTakeOff_TypeDef TakeOff;
	ArmPowerStatus_TypeDef  ArmPower;
	int landFlag;
	bool LaunchFlag;
	bool ControlStart;
	unsigned char poshold;    //设置目标位置标志位
	unsigned char setTargetPos;  //设置目标位置标志位
}DroneFlightControl;

typedef enum
{
	Data_Headmode = 0,
	Data_Headfree = 1,
	Data_Point = 2,
	Data_Flow = 3,
	Data_Follow = 4,
}Data_Combine;

typedef struct{
    //滤波时间
    float Merge_t;

    //参数
    float Q_Position;
    float Q_Velocity;
    float Q_Bias;
    float R_Position;

    //状态
    float Axis_Pos;
    float Axis_Vel;
    float Axis_Bias;
    float Axis_Err;
    float AxisPCt_0;
    float AxisPCt_1;
    float AxisPCt_2;
    float AxisE;
    char AxisC_0;
    float AxisK_0;
    float AxisK_1;
    float AxisK_2;
    float Axist_0;
    float Axist_1;
    float Axist_2;
    float AxisPdot[9];
    float AxisPP[3][3];
}KalmanFilter;


typedef struct
{
	float Pitch;
	float Roll;
	float Yaw;
	float RateRoll;
	float RatePitch;
	float RateYaw;
	float Height;
	float VelHeight;
	float AccHeight;
	float RemotePitch;
	float RemoteRoll;
	float BlackLineV;
  float BlackLineYaw;
	/*  载体期望运动加速度，用于转换到期望姿态 */
	float DesiredAccelerationX;
	float DesiredAccelerationY;
	float DesiredAccelerationZ;
	/* 路径规划中的期望位置 */
	float RoutePlanX;
	float RoutePlanY;
	float RoutePlanZ;
	/* 上一次路径规划中的期望位置 */
	float LastRoutePlanX;
	float LastRoutePlanY;
	float LastRoutePlanZ;	
	/* 期望定点位置 */
	float PositionX;
	float PositionY;
	float PositionZ;
	
	unsigned char PointCnt;
	
	unsigned char FlightBackFlag;
}DroneTargetInfo;

typedef struct
{
	float error;
	float lasterror;
	float differential;
	float differentialFliter;
	float pOut;
  float iOut;
	float dOut;
	float value;//PID控制输出
	
}PIDOut;

typedef struct
{
	float Kp;
	float Ki;
	float	Kd;
}PID;


typedef struct
{
    PID Pitch;
    PID Roll;
    PID Yaw;

    PID PitchRate;
    PID RollRate;
    PID YawRate;

    PID PosX;
    PID PosY;
    PID PosZ;

    PID VelX;
    PID VelY;
    PID VelZ;

    PID AccZ;

    PID FlowX;
    PID FlowY;
    PID FlowVelX;
    PID FlowVelY;
}PIDPara;

/*校准数据*/
typedef struct
{
	bool MagOffseting;
	int16_t MagX;
	int16_t MagY;
	int16_t MagZ;
	float GyroX;
	float GyroY;
	float GyroZ;
	float AccX;
	float AccY;
	float AccZ;
	float AccXScale;
	float AccYScale;
	float AccZScale;
}OffsetInfo;


/* 平地误差数据 */
typedef struct
{
	float fixedErroPitch;
	float fixedErroRoll;
}DroneErrangle;


typedef enum
{  
	Auto       = 0x01 ,   //自稳模式
  AltHold    = 0x02 ,	  //定高
	PosHold    = 0x03 ,   //定点
	RTL        = 0x04 ,   //返航模式
	NoGPS      = 0x05 ,   //无GPS定位模式
	VIOPosHold = 0x06,   //VIO定点模式
	VIOCruise  = 0x07,   //VIO巡逻模式
}FlightMode;

typedef enum
{  
	Heading       = 0x01 ,   //有头模式
  Headless      = 0x02 ,	 //无头模式
}HeadingMode;

typedef enum
{  
	On       = 0x01 ,  //开
  Off      = 0x02 ,	 //关
}Switch;


/*手柄遥控信息*/
typedef struct{
    float XaxisPos;  //手柄pitch控制
    float YaxisPos;   //手柄roll控制
    float ZaxisPos;   //手柄高度上的速度控制
    float Navigation;  //手柄航向控制
}RemoteControl;


/*遥控器数据与控制模式*/
typedef struct
{
	FlightMode FlightControlMode; //遥控飞行模式
	HeadingMode FlightHeadingMode ; //遥控飞行有头无头模式设置
	FlightMode CH5_Mode1;   //第五通道的模式1
	FlightMode CH5_Mode2;   //第五通道的模式2
	FlightMode CH5_Mode3;   //第五通道的模式3
	HeadingMode CH6_Mode1;   //第六通道的模式1
	HeadingMode CH6_Mode2;   //第六通道的模式2
	Switch CH7_Mode1;   //第七通道的模式1
	Switch CH7_Mode2;   //第七通道的模式2
	int SafeThrottle;   //遥控器失控保护油门
	unsigned char TakeOff_Flag; //起飞标志位
}Remote_Control;


/*遥控信息*/
typedef struct
{
	int CH1;// 通道1 副翼
	int CH2;// 通道2 升降舵
	int CH3;// 通道3 油门
	int CH4;// 通道4 方向舵
	int CH5;// 通道5 飞行模式
	int CH6;// 通道6 有头无头设置
	int CH7;// 通道7 失控保护
	int CH8;// 通道8
	
	int CH1_Max ,CH1_Min ,CH1_Mid ; // 通道1 最大最小和回中值
	int CH2_Max ,CH2_Min ,CH2_Mid ; // 通道2 最大最小和回中值
	int CH3_Max ,CH3_Min ,CH3_Mid ; // 通道3 最大最小和回中值
	int CH4_Max ,CH4_Min ,CH4_Mid ; // 通道4 最大最小和回中值
	int CH5_Max ,CH5_Min ,CH5_Mid ; // 通道5 最大最小和回中值
	int CH6_Max ,CH6_Min ,CH6_Mid; // 通道6 最大最小值和回中值
	int CH7_Max ,CH7_Min ,CH7_Mid; // 通道7 最大最小值和回中值
	int CH8_Max ,CH8_Min ,CH8_Mid; // 通道7 最大最小值和回中值
}Controller;


typedef enum
{  
	Lift     = 0x01 ,   //升降
  Hover    = 0x02 ,		//悬停
}Remote_Control_Status;

typedef enum
{  
	Sonar       = 0x01 ,   //声呐
//  Barometer   = 0x02 ,	 //气压计
}Height_Data_Switching;

/*无人机实时信息*/
typedef struct
{
	float Pitch; 					//实时Pitch角度
	float Roll;						//实时Roll角度
  float Yaw;						//实时Yaw角度
	float HomeYaw;				//起飞时yaw角度
	float HeadfreeYaw;    //无头模式下yaw角度
	float Headfreezeta;   //无头模式旋转Zeta角
	float ratePitch;
	float rateRoll;
	float rateYaw;
	float accXaxis;
	float accYaxis;
	float accZaxis;
	float Height;					//US100超声波高度
	float Height_V;				//US100超声波速度
	float Barometer;      //气压计数据
	float Barometer_V;    //气压计速度
	float FlowX;					//光流位置X
	float FlowY;          //光流位置Y
	float FlowX_V;				//光流速度X
	float FlowY_V;				//光流速度Y
	float PointX;					//点数据X位移
	float PointY;					//点数据Y位移
	float PointX_V;				//点数据X的速度
	float PointY_V;				//点数据Y的速度
	float VioPosition_X;  //视觉里程计X轴位置信息
	float VioPosition_Y;  //视觉里程计Y轴位置信息
	float VioPosition_Z;  //视觉里程计Z轴位置信息	
	float VioVel_X;       //视觉里程计X轴速度信息
	float VioVel_Y;  			//视觉里程计Y轴速度信息
	float VioVel_Z;  			//视觉里程计Z轴速度信息	
	float VioPitch;       //视觉里程计计算的俯仰角
	float VioRoll;        //视觉里程计计算的翻滚角
	float VioYaw;         //视觉里程计计算的航向角
	float Quaternion0;    //视觉里程计四元数
	float Quaternion1;    //视觉里程计四元数
	float Quaternion2;    //视觉里程计四元数
	float Quaternion3;    //视觉里程计四元数
	float batteryVoltage; //电池电量
	float AccX;
	float AccY;
	float AccZ;
	float GyroX;
	float GyroY;
	float GyroZ;
	float MagX;
	float MagY;
	float MagZ;
	int lowPowerFlag;			//低电压标志位
	bool VioAbnormal;  //VIO异常标志位
	int CpuTick;        //系统时间计时
	int VioHeartbeat;      //VIO心跳包
	float LPFTest1;        //滤波前数据测试
	float LPFTest2;        //滤波前数据测试
	int Key1Status;
	int Key2Status;
	unsigned char AllowLanding;  // 遥控器控制降落标志
	Remote_Control_Status  controlStatus;  //专业遥控器控制状态
	Height_Data_Switching  heightDataSwitching;  //高度数据来源切换
	unsigned char LaserArray;
	unsigned char LaserMode;
	float LaserDistance;
}DroneRTInfo;


typedef struct{
    float PitchThrust;
    float RollThrust;
    float YawThrust;
    float HeightThrust;
    float Gravity_Acceleration;
		float f1;
		float f2;
		float f3;
		float f4;
		float t1;
		float t2;
		float t3;
		float t4;
		float PaddleEffect;
}Thrust;

typedef struct
{
	int M1;
	int M2;
	int M3;
	int M4;
}Throttle;



typedef struct{
    float US100_Zaxis;
		float MS5611_Zaxis;
    float Raspberry_Xaxis;
    float Raspberry_Yaxis;
    float VIO_Xaxis;
    float VIO_Yaxis;
    float VIO_Zaxis;
    float FlowVelX;
    float FlowVelY;
		float FlowX;
    float FlowY;
		float FixFlowX;
		float FixFlowY;
		float TofHeight;
	
	
	  float LaserArray1;
	  unsigned char LaserArray1Status;
		float LaserArray2;
	  unsigned char LaserArray2Status;
		float LaserArray3;
	  unsigned char LaserArray3Status;
		float LaserArray4;
	  unsigned char LaserArray4Status;
	  unsigned char OffsetPosFlag;  //激光阵修复期望位置标志位
	  unsigned char Laser1invalid;
		unsigned char Laser2invalid;
		unsigned char Laser3invalid;
		unsigned char Laser4invalid;
}SensorData;

typedef struct {
	u32 isGood;
	PIDPara pidPara;
	DroneErrangle Errangle;
	OffsetInfo Offset_Data;
	Controller ControlData;
}FlashData;

typedef struct
{
	unsigned int len;
	unsigned char buf[512];
}_Data_Rx;

typedef struct
{
	unsigned int len;
	unsigned char buf[65];
}_Vio_Rx;

typedef union{
	float fvalue;
	unsigned char cv[4];
}float_union;



#endif

