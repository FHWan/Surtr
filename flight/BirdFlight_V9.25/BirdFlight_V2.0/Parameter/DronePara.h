#ifndef __DRONWPARA_H
#define __DRONWPARA_H

#include "stm32f4xx.h"
#include <stdbool.h>
#define TX_LEN  207
#define RX_LEN  512
#define Gravity_acceleration  9.81f

//������̬������Դ
#define VIO_Attitude
//#define IMU_Attitude

//�������
#define Model330
#ifdef Model330
    #define ARM_Length 0.165
    #define Drone_Mass 1.25f
    #define Drag_Coeff 0.016f
    //ת����������  ת������ = M*R^2  �����ʵ���ԡ������޷����ת��������С����Ϊһ���ɵ���������
    #define Inertia_Wx    0.002f
    #define Inertia_Wy    0.002f
    #define Inertia_Wz    0.004f
#else
    #define ARM_Length 0.105f
    #define Drone_Mass 0.64f
    #define Drag_Coeff 0.016f
    //ת����������  ת������ = M*R^2  �����ʵ���ԡ������޷����ת��������С����Ϊһ���ɵ���������
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
  Drone_Mode_RatePitch, //��̬�ڻ�
  Drone_Mode_RateRoll,
  Drone_Mode_Pitch,     //��̬�⻷
  Drone_Mode_Roll,
  Drone_Mode_4Axis,     //�������
}DroneFlightMode_TypeDef;

typedef enum
{  
	Drone_Off  = 0x00,//��ɻ��ߵ��Դ򿪵��
  Drone_On   = 0x01,//�رյ��
  Drone_Land = 0x02,//����	
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
	unsigned char poshold;    //����Ŀ��λ�ñ�־λ
	unsigned char setTargetPos;  //����Ŀ��λ�ñ�־λ
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
    //�˲�ʱ��
    float Merge_t;

    //����
    float Q_Position;
    float Q_Velocity;
    float Q_Bias;
    float R_Position;

    //״̬
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
	/*  ���������˶����ٶȣ�����ת����������̬ */
	float DesiredAccelerationX;
	float DesiredAccelerationY;
	float DesiredAccelerationZ;
	/* ·���滮�е�����λ�� */
	float RoutePlanX;
	float RoutePlanY;
	float RoutePlanZ;
	/* ��һ��·���滮�е�����λ�� */
	float LastRoutePlanX;
	float LastRoutePlanY;
	float LastRoutePlanZ;	
	/* ��������λ�� */
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
	float value;//PID�������
	
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

/*У׼����*/
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


/* ƽ��������� */
typedef struct
{
	float fixedErroPitch;
	float fixedErroRoll;
}DroneErrangle;


typedef enum
{  
	Auto       = 0x01 ,   //����ģʽ
  AltHold    = 0x02 ,	  //����
	PosHold    = 0x03 ,   //����
	RTL        = 0x04 ,   //����ģʽ
	NoGPS      = 0x05 ,   //��GPS��λģʽ
	VIOPosHold = 0x06,   //VIO����ģʽ
	VIOCruise  = 0x07,   //VIOѲ��ģʽ
}FlightMode;

typedef enum
{  
	Heading       = 0x01 ,   //��ͷģʽ
  Headless      = 0x02 ,	 //��ͷģʽ
}HeadingMode;

typedef enum
{  
	On       = 0x01 ,  //��
  Off      = 0x02 ,	 //��
}Switch;


/*�ֱ�ң����Ϣ*/
typedef struct{
    float XaxisPos;  //�ֱ�pitch����
    float YaxisPos;   //�ֱ�roll����
    float ZaxisPos;   //�ֱ��߶��ϵ��ٶȿ���
    float Navigation;  //�ֱ��������
}RemoteControl;


/*ң�������������ģʽ*/
typedef struct
{
	FlightMode FlightControlMode; //ң�ط���ģʽ
	HeadingMode FlightHeadingMode ; //ң�ط�����ͷ��ͷģʽ����
	FlightMode CH5_Mode1;   //����ͨ����ģʽ1
	FlightMode CH5_Mode2;   //����ͨ����ģʽ2
	FlightMode CH5_Mode3;   //����ͨ����ģʽ3
	HeadingMode CH6_Mode1;   //����ͨ����ģʽ1
	HeadingMode CH6_Mode2;   //����ͨ����ģʽ2
	Switch CH7_Mode1;   //����ͨ����ģʽ1
	Switch CH7_Mode2;   //����ͨ����ģʽ2
	int SafeThrottle;   //ң����ʧ�ر�������
	unsigned char TakeOff_Flag; //��ɱ�־λ
}Remote_Control;


/*ң����Ϣ*/
typedef struct
{
	int CH1;// ͨ��1 ����
	int CH2;// ͨ��2 ������
	int CH3;// ͨ��3 ����
	int CH4;// ͨ��4 �����
	int CH5;// ͨ��5 ����ģʽ
	int CH6;// ͨ��6 ��ͷ��ͷ����
	int CH7;// ͨ��7 ʧ�ر���
	int CH8;// ͨ��8
	
	int CH1_Max ,CH1_Min ,CH1_Mid ; // ͨ��1 �����С�ͻ���ֵ
	int CH2_Max ,CH2_Min ,CH2_Mid ; // ͨ��2 �����С�ͻ���ֵ
	int CH3_Max ,CH3_Min ,CH3_Mid ; // ͨ��3 �����С�ͻ���ֵ
	int CH4_Max ,CH4_Min ,CH4_Mid ; // ͨ��4 �����С�ͻ���ֵ
	int CH5_Max ,CH5_Min ,CH5_Mid ; // ͨ��5 �����С�ͻ���ֵ
	int CH6_Max ,CH6_Min ,CH6_Mid; // ͨ��6 �����Сֵ�ͻ���ֵ
	int CH7_Max ,CH7_Min ,CH7_Mid; // ͨ��7 �����Сֵ�ͻ���ֵ
	int CH8_Max ,CH8_Min ,CH8_Mid; // ͨ��7 �����Сֵ�ͻ���ֵ
}Controller;


typedef enum
{  
	Lift     = 0x01 ,   //����
  Hover    = 0x02 ,		//��ͣ
}Remote_Control_Status;

typedef enum
{  
	Sonar       = 0x01 ,   //����
//  Barometer   = 0x02 ,	 //��ѹ��
}Height_Data_Switching;

/*���˻�ʵʱ��Ϣ*/
typedef struct
{
	float Pitch; 					//ʵʱPitch�Ƕ�
	float Roll;						//ʵʱRoll�Ƕ�
  float Yaw;						//ʵʱYaw�Ƕ�
	float HomeYaw;				//���ʱyaw�Ƕ�
	float HeadfreeYaw;    //��ͷģʽ��yaw�Ƕ�
	float Headfreezeta;   //��ͷģʽ��תZeta��
	float ratePitch;
	float rateRoll;
	float rateYaw;
	float accXaxis;
	float accYaxis;
	float accZaxis;
	float Height;					//US100�������߶�
	float Height_V;				//US100�������ٶ�
	float Barometer;      //��ѹ������
	float Barometer_V;    //��ѹ���ٶ�
	float FlowX;					//����λ��X
	float FlowY;          //����λ��Y
	float FlowX_V;				//�����ٶ�X
	float FlowY_V;				//�����ٶ�Y
	float PointX;					//������Xλ��
	float PointY;					//������Yλ��
	float PointX_V;				//������X���ٶ�
	float PointY_V;				//������Y���ٶ�
	float VioPosition_X;  //�Ӿ���̼�X��λ����Ϣ
	float VioPosition_Y;  //�Ӿ���̼�Y��λ����Ϣ
	float VioPosition_Z;  //�Ӿ���̼�Z��λ����Ϣ	
	float VioVel_X;       //�Ӿ���̼�X���ٶ���Ϣ
	float VioVel_Y;  			//�Ӿ���̼�Y���ٶ���Ϣ
	float VioVel_Z;  			//�Ӿ���̼�Z���ٶ���Ϣ	
	float VioPitch;       //�Ӿ���̼Ƽ���ĸ�����
	float VioRoll;        //�Ӿ���̼Ƽ���ķ�����
	float VioYaw;         //�Ӿ���̼Ƽ���ĺ����
	float Quaternion0;    //�Ӿ���̼���Ԫ��
	float Quaternion1;    //�Ӿ���̼���Ԫ��
	float Quaternion2;    //�Ӿ���̼���Ԫ��
	float Quaternion3;    //�Ӿ���̼���Ԫ��
	float batteryVoltage; //��ص���
	float AccX;
	float AccY;
	float AccZ;
	float GyroX;
	float GyroY;
	float GyroZ;
	float MagX;
	float MagY;
	float MagZ;
	int lowPowerFlag;			//�͵�ѹ��־λ
	bool VioAbnormal;  //VIO�쳣��־λ
	int CpuTick;        //ϵͳʱ���ʱ
	int VioHeartbeat;      //VIO������
	float LPFTest1;        //�˲�ǰ���ݲ���
	float LPFTest2;        //�˲�ǰ���ݲ���
	int Key1Status;
	int Key2Status;
	unsigned char AllowLanding;  // ң�������ƽ����־
	Remote_Control_Status  controlStatus;  //רҵң��������״̬
	Height_Data_Switching  heightDataSwitching;  //�߶�������Դ�л�
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
	  unsigned char OffsetPosFlag;  //�������޸�����λ�ñ�־λ
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

