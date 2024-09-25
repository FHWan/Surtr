/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :Position.c
 * 描述   :位置融合函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include "PositionEstimation.h"

const float KalmanFilter_Unit[4][7] =
{  //Q_Position      Q_Velocity      Q_Bias         R_Position     AxisC_0    AxisPP        Merge_t
	 {   0.02,            0.04,         0.01,          0.01,           1,         1.0,         0.005   },//xaxis
	 {   0.02,            0.04,         0.01,          0.01,           1,         1.0,         0.005   },//yaxis
	 {   0.08,            0.01,         0.01,           0.01,           1,         1.0,        0.005   },//zaxis
	 {   0.08,            0.01,         0.01,           0.01,           1,         1.0,        0.005  },//Barometer
};

/*
 *
 *  KalmanFilter 参数初始化
 *
 */
void KalmanFilter_Init(KalmanFilter *XAXIS,KalmanFilter *YAXIS,KalmanFilter *ZAXIS , KalmanFilter *BAROMETER){

    XAXIS->Q_Position = KalmanFilter_Unit[0][0];
    XAXIS->Q_Velocity = KalmanFilter_Unit[0][1];
    XAXIS->Q_Bias = KalmanFilter_Unit[0][2];
    XAXIS->R_Position = KalmanFilter_Unit[0][3];
    XAXIS->AxisC_0 = KalmanFilter_Unit[0][4];
    XAXIS->AxisPP[0][0] = KalmanFilter_Unit[0][5];
    XAXIS->AxisPP[1][1] = KalmanFilter_Unit[0][5];
    XAXIS->AxisPP[2][2] = KalmanFilter_Unit[0][5];
    XAXIS->Merge_t = KalmanFilter_Unit[0][6];

    YAXIS->Q_Position = KalmanFilter_Unit[1][0];
    YAXIS->Q_Velocity = KalmanFilter_Unit[1][1];
    YAXIS->Q_Bias = KalmanFilter_Unit[1][2];
    YAXIS->R_Position = KalmanFilter_Unit[1][3];
    YAXIS->AxisC_0 = KalmanFilter_Unit[1][4];
    YAXIS->AxisPP[0][0] = KalmanFilter_Unit[1][5];
    YAXIS->AxisPP[1][1] = KalmanFilter_Unit[1][5];
    YAXIS->AxisPP[2][2] = KalmanFilter_Unit[1][5];
    YAXIS->Merge_t = KalmanFilter_Unit[1][6];

    ZAXIS->Q_Position = KalmanFilter_Unit[2][0];
    ZAXIS->Q_Velocity = KalmanFilter_Unit[2][1];
    ZAXIS->Q_Bias = KalmanFilter_Unit[2][2];
    ZAXIS->R_Position = KalmanFilter_Unit[2][3];
    ZAXIS->AxisC_0 = KalmanFilter_Unit[2][4];
    ZAXIS->AxisPP[0][0] = KalmanFilter_Unit[2][5];
    ZAXIS->AxisPP[1][1] = KalmanFilter_Unit[2][5];
    ZAXIS->AxisPP[2][2] = KalmanFilter_Unit[2][5];
    ZAXIS->Merge_t = KalmanFilter_Unit[2][6];
		
		BAROMETER->Q_Position = KalmanFilter_Unit[3][0];
    BAROMETER->Q_Velocity = KalmanFilter_Unit[3][1];
    BAROMETER->Q_Bias = KalmanFilter_Unit[3][2];
    BAROMETER->R_Position = KalmanFilter_Unit[3][3];
    BAROMETER->AxisC_0 = KalmanFilter_Unit[3][4];
    BAROMETER->AxisPP[0][0] = KalmanFilter_Unit[3][5];
    BAROMETER->AxisPP[1][1] = KalmanFilter_Unit[3][5];
    BAROMETER->AxisPP[2][2] = KalmanFilter_Unit[3][5];
    BAROMETER->Merge_t = KalmanFilter_Unit[3][6];
}


void POS_KalmanFilter(KalmanFilter *KalmanFilter_Input,float Position,float Acceleration){
    //v(k+1) = v(k)+[a(k)-bias(k)]*dt
    KalmanFilter_Input->Axis_Vel +=(Acceleration - KalmanFilter_Input->Axis_Bias)*KalmanFilter_Input->Merge_t;
    //Height(k+1) = Height(k) + 1/2[a(k)-bias(k)]dt^2 + v(k)dt
    KalmanFilter_Input->Axis_Pos +=(Acceleration - KalmanFilter_Input->Axis_Bias)*(KalmanFilter_Input->Merge_t)
                   *(KalmanFilter_Input->Merge_t)/2 + KalmanFilter_Input->Axis_Vel*KalmanFilter_Input->Merge_t;

    KalmanFilter_Input->AxisPdot[0] = KalmanFilter_Input->Q_Position+KalmanFilter_Input->AxisPP[0][1]+KalmanFilter_Input->AxisPP[1][0]+(KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[2][0]/2-KalmanFilter_Input->AxisPP[0][2]/2)*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[1] = KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[0][2]-(KalmanFilter_Input->AxisPP[2][1]/2+KalmanFilter_Input->AxisPP[1][2])*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[2] = KalmanFilter_Input->AxisPP[1][2]-KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t/2;
    KalmanFilter_Input->AxisPdot[3] = KalmanFilter_Input->AxisPP[1][1]-KalmanFilter_Input->AxisPP[2][0]-(KalmanFilter_Input->AxisPP[2][1]+KalmanFilter_Input->AxisPP[1][2]/2)*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[4] = KalmanFilter_Input->Q_Velocity-KalmanFilter_Input->AxisPP[2][1]-KalmanFilter_Input->AxisPP[1][2]+KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPdot[5] = -KalmanFilter_Input->AxisPP[2][2];
    KalmanFilter_Input->AxisPdot[6] = KalmanFilter_Input->AxisPP[2][1]-KalmanFilter_Input->AxisPP[2][2]*KalmanFilter_Input->Merge_t/2;
    KalmanFilter_Input->AxisPdot[7] = -KalmanFilter_Input->AxisPP[2][2];
    KalmanFilter_Input->AxisPdot[8] = KalmanFilter_Input->Q_Bias;

    KalmanFilter_Input->AxisPP[0][0] += KalmanFilter_Input->AxisPdot[0]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[0][1] += KalmanFilter_Input->AxisPdot[1]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[0][2] += KalmanFilter_Input->AxisPdot[2]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][0] += KalmanFilter_Input->AxisPdot[3]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][1] += KalmanFilter_Input->AxisPdot[4]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[1][2] += KalmanFilter_Input->AxisPdot[5]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][0] += KalmanFilter_Input->AxisPdot[6]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][1] += KalmanFilter_Input->AxisPdot[7]*KalmanFilter_Input->Merge_t;
    KalmanFilter_Input->AxisPP[2][2] += KalmanFilter_Input->AxisPdot[8]*KalmanFilter_Input->Merge_t;

    KalmanFilter_Input->AxisPCt_0 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][0];
    KalmanFilter_Input->AxisPCt_1 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[1][0];
    KalmanFilter_Input->AxisPCt_2 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[2][0];

    KalmanFilter_Input->AxisE = KalmanFilter_Input->R_Position + KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPCt_0;

    KalmanFilter_Input->AxisK_0 = KalmanFilter_Input->AxisPCt_0/KalmanFilter_Input->AxisE;
    KalmanFilter_Input->AxisK_1 = KalmanFilter_Input->AxisPCt_1/KalmanFilter_Input->AxisE;
    KalmanFilter_Input->AxisK_2 = KalmanFilter_Input->AxisPCt_2/KalmanFilter_Input->AxisE;

    KalmanFilter_Input->Axis_Err = Position - KalmanFilter_Input->Axis_Pos;
    KalmanFilter_Input->Axis_Pos += KalmanFilter_Input->AxisK_0 * KalmanFilter_Input->Axis_Err;
    KalmanFilter_Input->Axis_Vel += KalmanFilter_Input->AxisK_1 * KalmanFilter_Input->Axis_Err;
    KalmanFilter_Input->Axis_Bias += KalmanFilter_Input->AxisK_2 * KalmanFilter_Input->Axis_Err;

    KalmanFilter_Input->Axist_0 = KalmanFilter_Input->AxisPCt_0;
    KalmanFilter_Input->Axist_1 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][1];
    KalmanFilter_Input->Axist_2 = KalmanFilter_Input->AxisC_0 * KalmanFilter_Input->AxisPP[0][2];

    KalmanFilter_Input->AxisPP[0][0] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[0][1] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[0][2] -= KalmanFilter_Input->AxisK_0*KalmanFilter_Input->Axist_2;
    KalmanFilter_Input->AxisPP[1][0] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[1][1] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[1][2] -= KalmanFilter_Input->AxisK_1*KalmanFilter_Input->Axist_2;
    KalmanFilter_Input->AxisPP[2][0] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_0;
    KalmanFilter_Input->AxisPP[2][1] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_1;
    KalmanFilter_Input->AxisPP[2][2] -= KalmanFilter_Input->AxisK_2*KalmanFilter_Input->Axist_2;

}




/* kalman滤波融合光流数据和加速计数据  主要参照卡尔曼线性滤波的五条黄金公式*/
/* X(k|k-1)=AX(k-1|k-1)+BU(k) */
/* P(k|k-1)=AP(k-1|k-1)A'+Q */
/* X(k|k)= X(k|k-1)+Kg(k)(Z(k)-HX(k|k-1)) */
/* Kg(k)= P(k|k-1)H'/(HP(k|k-1)H'+R) */
/* P(k|k)=(I-Kg(k)H)P(k|k-1) */
/* 卡尔曼滤波详解可参考：
		https://wenku.baidu.com/view/3c42b7733186bceb18e8bb29.html*/

void OpticalFlow_Estimation(float flow_x,float flow_y,float Accx,float Accy)
{
 //周期获取
    static float OpticalFlow_dt;
    OpticalFlow_dt = 0.005f;
    static float accel_bias[3] = {0.0f,0.0f,0.0f};  //机体坐标系下的加速度偏移量
    float accel_now[3] = {0.0f,0.0f,0.0f};

    //加速度除去偏移量
    accel_now[0] -= accel_bias[0];
    accel_now[1] -= accel_bias[1];

    /* x轴kf融合 */
    static float OpticalFlowx_Velocity;
    static float Q_OpticalFlowxVelocity = 0.05,Q_xbias = 0.1;
    static float R_OpticalFlowx = 0.01;
    static float OpticalFlowx_Velocityerr,OpticalFlowxbias;
    static float OpticalFlowxPCt_0 = 0,OpticalFlowxPCt_1 = 0,OpticalFlowxE = 0;
    static float OpticalFlowxK_0 = 0,OpticalFlowxK_1 = 0,OpticalFlowxt_0 = 0,OpticalFlowxt_1 = 0;
    static char OpticalFlowxC_0 = 1;
    static float OpticalFlowxPdot[4],OpticalFlowxP[2][2];

    OpticalFlowx_Velocity += (Accx - OpticalFlowxbias) * OpticalFlow_dt;

    OpticalFlowxPdot[0] = Q_OpticalFlowxVelocity - OpticalFlowxP[0][1] - OpticalFlowxP[1][0];
    OpticalFlowxPdot[1] =   -OpticalFlowxP[1][1];
    OpticalFlowxPdot[2] =   -OpticalFlowxP[1][1];
    OpticalFlowxPdot[3] = Q_xbias;

    OpticalFlowxP[0][0] += OpticalFlowxPdot[0] * OpticalFlow_dt;
    OpticalFlowxP[0][1] += OpticalFlowxPdot[1] * OpticalFlow_dt;
    OpticalFlowxP[1][0] += OpticalFlowxPdot[2] * OpticalFlow_dt;
    OpticalFlowxP[1][1] += OpticalFlowxPdot[3] * OpticalFlow_dt;

    OpticalFlowxPCt_0 = OpticalFlowxC_0 * OpticalFlowxP[0][0];
    OpticalFlowxPCt_1 = OpticalFlowxC_0 * OpticalFlowxP[1][0];
    OpticalFlowxE = R_OpticalFlowx + OpticalFlowxC_0 * OpticalFlowxPCt_0;
    OpticalFlowxK_0 = OpticalFlowxPCt_0 / OpticalFlowxE;
    OpticalFlowxK_1 = OpticalFlowxPCt_1 / OpticalFlowxE;

    OpticalFlowx_Velocityerr = flow_x - OpticalFlowx_Velocity;
    OpticalFlowx_Velocity += OpticalFlowxK_0 * OpticalFlowx_Velocityerr;
    OpticalFlowxbias += OpticalFlowxK_1 * OpticalFlowx_Velocityerr;

    OpticalFlowxt_0 = OpticalFlowxPCt_0;
    OpticalFlowxt_1 = OpticalFlowxC_0 * OpticalFlowxP[0][1];

    OpticalFlowxP[0][0] -= OpticalFlowxK_0 * OpticalFlowxt_0;
    OpticalFlowxP[0][1] -= OpticalFlowxK_0 * OpticalFlowxt_1;
    OpticalFlowxP[1][0] -= OpticalFlowxK_1 * OpticalFlowxt_0;
    OpticalFlowxP[1][1] -= OpticalFlowxK_1 * OpticalFlowxt_1;

    RT_Info.FlowX_V  = OpticalFlowx_Velocity;
    /* y轴kf融合 */
    static float OpticalFlowy_Velocity;
    static float Q_OpticalFlowyVelocity = 0.05,Q_ybias = 0.1;
    static float R_OpticalFlowy = 0.01;
    static float OpticalFlowy_Velocityerr,OpticalFlowybias;
    static float OpticalFlowyPCt_0 = 0,OpticalFlowyPCt_1 = 0,OpticalFlowyE = 0;
    static float OpticalFlowyK_0 = 0,OpticalFlowyK_1 = 0,OpticalFlowyt_0 = 0,OpticalFlowyt_1 = 0;
    static char OpticalFlowyC_0 = 1;
    static float OpticalFlowyPdot[4],OpticalFlowyP[2][2];

    OpticalFlowy_Velocity += (Accy - OpticalFlowybias) * OpticalFlow_dt;

    OpticalFlowyPdot[0] = Q_OpticalFlowyVelocity - OpticalFlowyP[0][1] - OpticalFlowyP[1][0];
    OpticalFlowyPdot[1] =   -OpticalFlowyP[1][1];
    OpticalFlowyPdot[2] =   -OpticalFlowyP[1][1];
    OpticalFlowyPdot[3] = Q_ybias;

    OpticalFlowyP[0][0] += OpticalFlowyPdot[0] * OpticalFlow_dt;
    OpticalFlowyP[0][1] += OpticalFlowyPdot[1] * OpticalFlow_dt;
    OpticalFlowyP[1][0] += OpticalFlowyPdot[2] * OpticalFlow_dt;
    OpticalFlowyP[1][1] += OpticalFlowyPdot[3] * OpticalFlow_dt;

    OpticalFlowyPCt_0 = OpticalFlowyC_0 * OpticalFlowyP[0][0];
    OpticalFlowyPCt_1 = OpticalFlowyC_0 * OpticalFlowyP[1][0];
    OpticalFlowyE = R_OpticalFlowy + OpticalFlowyC_0 * OpticalFlowyPCt_0;
    OpticalFlowyK_0 = OpticalFlowyPCt_0 / OpticalFlowyE;
    OpticalFlowyK_1 = OpticalFlowyPCt_1 / OpticalFlowyE;

    OpticalFlowy_Velocityerr = flow_y - OpticalFlowy_Velocity;
    OpticalFlowy_Velocity += OpticalFlowyK_0 * OpticalFlowy_Velocityerr;
    OpticalFlowybias += OpticalFlowyK_1 * OpticalFlowy_Velocityerr;

    OpticalFlowyt_0 = OpticalFlowyPCt_0;
    OpticalFlowyt_1 = OpticalFlowyC_0 * OpticalFlowyP[0][1];

    OpticalFlowyP[0][0] -= OpticalFlowyK_0 * OpticalFlowyt_0;
    OpticalFlowyP[0][1] -= OpticalFlowyK_0 * OpticalFlowyt_1;
    OpticalFlowyP[1][0] -= OpticalFlowyK_1 * OpticalFlowyt_0;
    OpticalFlowyP[1][1] -= OpticalFlowyK_1 * OpticalFlowyt_1;

    RT_Info.FlowY_V  = OpticalFlowy_Velocity;
	
}






//速度位移预测函数
void inertial_filter_predict(float dt, float x[2], float acc)
{
	x[0] += x[1] * dt + acc * dt * dt / 2.0f;
	x[1] += acc * dt;
}
//校准函数
void inertial_filter_correct(float e, float dt, float x[2], int i, float w)
{
	float ewdt = e * w * dt;
	x[i] += ewdt;

	if (i == 0) {
		x[1] += w * ewdt;
	}
}

//定点位置估计
void POS_Pixhawk(float Ultrasonic,float Xvision,float Yvision,float *Accel,float Position_dt)
{
	unsigned int i,j;
	//预测参数
	static float x_vision=8.0f;
	static float y_vision=8.0f;
	static float z_ultra=10.0f;
	static float acc_bias=0.8f;

	static float X_est[2] = {0.0f,0.0f};//X轴的位移和速度
	static float Y_est[2] = {0.0f,0.0f};//X轴的位移和速度
	static float Z_est[2] = {0.0f,0.0f};//Z轴的高度和速度

	static float Accel_ned[3] = {0.0f,0.0f,0.0f};//地理坐标系下的加速度数据
	static float Accel_bias[3] = {0.0f,0.0f,0.0f};//机体坐标系下的加速度偏移量

	static float Corr_Ultra = 0.0f;
	static float Corr_Xvision = 0.0f;
	static float Corr_Yvision = 0.0f;
	float Accel_bias_corr[3] = { 0.0f, 0.0f, 0.0f };
	float Accel_now[3] = {0.0f,0.0f,0.0f};
									
	Accel_now[0] = Accel[0];
	Accel_now[1] = Accel[1];
	Accel_now[2] = Accel[2];
	//位置参数校准
	Corr_Xvision = 0 - Xvision - X_est[0];
	Corr_Yvision = 0 - Yvision - Y_est[0];
  Corr_Ultra = 0 - Ultrasonic - Z_est[0];
	//加速度除去偏移量
  Accel_now[0] -= Accel_bias[0];
  Accel_now[1] -= Accel_bias[1];
  Accel_now[2] -= Accel_bias[2];
	//转化为NED坐标系
  for(i=0; i<3; i++)
  {
		Accel_ned[i]=0.0f;
		for(j=0; j<3; j++)
		{
			Accel_ned[i] += RDrone_R[i][j]* Accel_now[j];
		}
  }
	Accel_ned[2] += GRAVITY_MSS;
	//正确的加速度偏移向量
	Accel_bias_corr[0] -= Corr_Yvision * y_vision * y_vision;
	Accel_bias_corr[1] -= Corr_Xvision * x_vision * x_vision;
  Accel_bias_corr[2] -= Corr_Ultra * z_ultra * z_ultra;
	//转化为机体坐标系
  for (i = 0; i < 3; i++)
  {
		float c = 0.0f;
		for (j = 0; j < 3; j++)
		{
			c += RDrone_R[j][i] * Accel_bias_corr[j];
		}
		Accel_bias[i] += c * acc_bias * Position_dt;
  }
	//X轴预测
	inertial_filter_predict(Position_dt, X_est, Accel_ned[1]);
  inertial_filter_correct(Corr_Xvision, Position_dt, X_est, 0, x_vision);
	//Y轴预测
	inertial_filter_predict(Position_dt, Y_est, Accel_ned[0]);
  inertial_filter_correct(Corr_Yvision, Position_dt, Y_est, 0, y_vision);
	//Z轴预测
	inertial_filter_predict(Position_dt, Z_est, Accel_ned[2]);
  inertial_filter_correct(Corr_Ultra, Position_dt, Z_est, 0, z_ultra);
	
	RT_Info.PointX = X_est[0];
	RT_Info.PointX_V = -X_est[1];

	RT_Info.PointY = Y_est[0];
	RT_Info.PointY_V = -Y_est[1];
	
	RT_Info.Height = -Z_est[0];
	RT_Info.Height_V = -Z_est[1];

}


