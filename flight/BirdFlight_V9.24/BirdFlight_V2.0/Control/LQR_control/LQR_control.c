#include "LQR_control.h"
/*
	
	LQR 控制器

*/
const float  Klqr_Unit[3][6]={
		/*	r   		    h    			 		N0					Kw            kn       	 		inertia */
		{  10000, 			0.005,				5,			 		0.0065,         0.00,       	0.0000      },//Pitch
		{  10000, 			0.005,				5,	   			0.0065,         0.00,       	0.0000      },//Roll
		{  10000,				0.005,				5,  				0.0030,         0.00,       	0.0000      },//Yaw
};


void LQR_Init(LQR *WxBodyRate,LQR *WyBodyRate,LQR *WzBodyRate){
	//WxBodyRate
	WxBodyRate->LQRr = Klqr_Unit[0][0];
	WxBodyRate->LQRh = Klqr_Unit[0][1];
	WxBodyRate->LQRN0 = Klqr_Unit[0][2];
	WxBodyRate->Kw = Klqr_Unit[0][3];
	WxBodyRate->kn = Klqr_Unit[0][4];
	WxBodyRate->inertia = Klqr_Unit[0][5];
	//WyBodyRate
	WyBodyRate->LQRr = Klqr_Unit[1][0];
	WyBodyRate->LQRh = Klqr_Unit[1][1];
	WyBodyRate->LQRN0 = Klqr_Unit[1][2];
	WyBodyRate->Kw = Klqr_Unit[1][3];
	WyBodyRate->kn = Klqr_Unit[1][4];
	WyBodyRate->inertia = Klqr_Unit[1][5];
	//WzBodyRate
	WzBodyRate->LQRr = Klqr_Unit[2][0];
	WzBodyRate->LQRh = Klqr_Unit[2][1];
	WzBodyRate->LQRN0 = Klqr_Unit[2][2];
	WzBodyRate->Kw = Klqr_Unit[2][3];
	WzBodyRate->kn = Klqr_Unit[2][4];
	WzBodyRate->inertia = Klqr_Unit[2][5];
}



int16_t Sign_LQR(float Input)
{
    int16_t output=0;
    if(Input>1E-6f) output=1;
    else if(Input<-1E-6f) output=-1;
    else output=0;
    return output;
}

int16_t Fsg_LQR(float x,float d)
{
  int16_t output=0;
  output=(Sign_LQR(x+d)-Sign_LQR(x-d))/2;
  return output;
}


/**** 	TD跟踪器 实现设定值的微分提取  ****/
void Fhan_LQR(LQR *LQR_INPUT,float expect_LQR)
{
  float d=0,a0=0,y=0,a1=0,a2=0,a=0;
  float x1_delta=0;
  x1_delta=LQR_INPUT->LQRx1-expect_LQR;               			//x1-v(k)
  LQR_INPUT->LQRh0=LQR_INPUT->LQRN0*LQR_INPUT->LQRh;       	//用h0代替h，解决最速跟踪微分器速度超调问题
  d=LQR_INPUT->LQRr*LQR_INPUT->LQRh0*LQR_INPUT->LQRh0;     	//d=rh^2;
  a0=LQR_INPUT->LQRh0*LQR_INPUT->LQRx2;                  		//a0=h*x2
  y=x1_delta+a0;                                     				//y=x1+a0
  a1=sqrt(d*(d+8*fabsf(y)));                         				//a1=sqrt(d*(d+8*ABS(y))])
  a2=a0+Sign_LQR(y)*(a1-d)/2;                       				//a2=a0+sign(y)*(a1-d)/2;
  a=(a0+y)*Fsg_LQR(y,d)+a2*(1-Fsg_LQR(y,d));
  LQR_INPUT->LQRfh=-LQR_INPUT->LQRr*(a/d)*Fsg_LQR(a,d)
                  -LQR_INPUT->LQRr*Sign_LQR(a)*(1-Fsg_LQR(a,d));       //获得最速微分加速度跟踪量
  LQR_INPUT->LQRx1+=LQR_INPUT->LQRh*LQR_INPUT->LQRx2;      //x1状态量
  LQR_INPUT->LQRx2+=LQR_INPUT->LQRh*LQR_INPUT->LQRfh;      //x2状态量
}



void BodyRateControl(LQR *LQR_InputWx,LQR *LQR_InputWy,LQR *LQR_InputWz,float WxExpect,
	float WxEstimate,float WyExpect,float WyEstimate,float WzExpect,float WzEstimate){
	/**** 	TD跟踪器 实现设定值的微分提取  ****/	
	Fhan_LQR(LQR_InputWx,WxExpect);
	Fhan_LQR(LQR_InputWy,WyExpect);
	Fhan_LQR(LQR_InputWz,WzExpect);
	/**** 	LQR根据模型实现控制  ****/	
	LQR_InputWx->w_error = LQR_InputWx->LQRx1 - WxEstimate;
	LQR_InputWy->w_error = LQR_InputWy->LQRx1 - WyEstimate;
	LQR_InputWz->w_error = LQR_InputWz->LQRx1 - WzEstimate;
		
	/**** 	数据的叉乘  ****/	
//	LQR_InputWx->n_error = LQR_InputWy->LQRx1 * (LQR_InputWz->inertia * LQR_InputWz->LQRx1)
//																		- (LQR_InputWy->inertia * LQR_InputWy->LQRx1) * LQR_InputWz->LQRx1
//																						+ LQR_InputWx->inertia * LQR_InputWx->LQRx2 - UAVThrust.body_torquesX;
 		
//	LQR_InputWy->n_error = -(LQR_InputWx->LQRx1 * (LQR_InputWz->inertia * LQR_InputWz->LQRx1)
//																		- (LQR_InputWx->inertia * LQR_InputWx->LQRx1) * LQR_InputWz->LQRx1)
//																						+ LQR_InputWy->inertia * LQR_InputWy->LQRx2 - UAVThrust.body_torquesY;

//	LQR_InputWz->n_error = LQR_InputWx->LQRx1 * (LQR_InputWy->inertia * LQR_InputWy->LQRx1)	
//																		- (LQR_InputWx->inertia * LQR_InputWx->LQRx1) * LQR_InputWy->LQRx1
//																						+ LQR_InputWz->inertia * LQR_InputWz->LQRx2 - UAVThrust.body_torquesZ;
	/**** 产生实际的力矩 ****/		
	UAVThrust.wxThrust = (LQR_InputWx->Kw * LQR_InputWx->w_error + LQR_InputWx->kn * LQR_InputWx->n_error 
															+ WyEstimate * (LQR_InputWz->inertia * WzEstimate) - (LQR_InputWy->inertia * WyEstimate) * WzEstimate
																 + 0.0002f * LQR_InputWx->LQRx2);//
	
	UAVThrust.wyThrust = (LQR_InputWy->Kw * LQR_InputWy->w_error + LQR_InputWy->kn * LQR_InputWy->n_error
															+ (-(WxEstimate * (LQR_InputWz->inertia * WzEstimate) - (LQR_InputWx->inertia * WxEstimate) * WzEstimate))
																 + 0.0002f * LQR_InputWy->LQRx2);//
	
	UAVThrust.wzThrust = (LQR_InputWz->Kw * LQR_InputWz->w_error + LQR_InputWz->kn * LQR_InputWz->n_error
															+ WxEstimate * (LQR_InputWy->inertia * WyEstimate) - (LQR_InputWx->inertia * WxEstimate) * WyEstimate
																 + 0.0002f * LQR_InputWz->LQRx2);//
																
	UAVThrust.wxThrust = Limits_data(UAVThrust.wxThrust,5,-5);
	UAVThrust.wyThrust = Limits_data(UAVThrust.wyThrust,5,-5);
	UAVThrust.wzThrust = Limits_data(UAVThrust.wzThrust,5,-5);
	
}


void ThrustMixer(float arm_length){
	
	UAVThrust.f1 = -1.414f / (arm_length * 4.0f) * UAVThrust.wxThrust  		//roll
									- 1.414f / (arm_length * 4.0f) * UAVThrust.wyThrust  	//pitch
										- 14.2f * UAVThrust.wzThrust 												//yaw
											+ Gravity_acceleration * Drone_Mass / 4.0f;				//height
	
	UAVThrust.f2 = -1.414f / (arm_length * 4.0f) * UAVThrust.wxThrust 
									+ 1.414f / (arm_length * 4.0f) * UAVThrust.wyThrust
										+ 14.2f * UAVThrust.wzThrust
											+ Gravity_acceleration * Drone_Mass / 4.0f;
	
	UAVThrust.f3 = 1.414f / (arm_length * 4.0f) * UAVThrust.wxThrust 
									+ 1.414f / (arm_length * 4.0f) * UAVThrust.wyThrust
										- 14.2f * UAVThrust.wzThrust
											+ Gravity_acceleration * Drone_Mass / 4.0f;
	
	UAVThrust.f4 = 1.414f / (arm_length * 4.0f) * UAVThrust.wxThrust 
									- 1.414f / (arm_length * 4.0f) * UAVThrust.wyThrust
										+ 14.2f * UAVThrust.wzThrust
											+ Gravity_acceleration * Drone_Mass / 4.0f;
	
	MotorThrust(UAVThrust.f1,UAVThrust.f2,UAVThrust.f3,UAVThrust.f4);
}


/*
	电压12.6V测试
	F=[0.981;1.962;2.943;3.924;4.905;6.1803]; %推力数据 单位N
	cmd=[0.29;0.5;0.66;0.79;0.91;1]; %油门数据 占空比
	p=polyfit(cmd,F,2) % 二次拟合
	plot(cmd,F);
	
	A = 5.8629
	B = -0.4797
	C = 0.6661
	
*/

void MotorThrustCallback(float Accelerator1,float Accelerator2,float Accelerator3,float Accelerator4,float arm_length,float rotor_drag_coeff){
	
	const double f1 = 5.8629f * Accelerator1 * Accelerator1 - 0.4797f * abs(Accelerator1) + 0.6661f;
  const double f2 = 5.8629f * Accelerator2 * Accelerator2 - 0.4797f * abs(Accelerator2) + 0.6661f;
  const double f3 = 5.8629f * Accelerator3 * Accelerator3 - 0.4797f * abs(Accelerator3) + 0.6661f;
  const double f4 = 5.8629f * Accelerator4 * Accelerator4 - 0.4797f * abs(Accelerator4) + 0.6661f;
	
	UAVThrust.body_torquesX = 0.707f * arm_length * (f3 + f4 - f1 - f2);
	UAVThrust.body_torquesY = 0.707f * arm_length * (f2 + f3 - f1 - f4);
	UAVThrust.body_torquesZ = rotor_drag_coeff * (f2 - f3 + f4 - f1);
	UAVThrust.collective_thrust = f1 + f2 + f3 + f4;
}


/*
	电压12.6V测试
	cmd=[0.29;0.5;0.66;0.79;0.91;1]; %油门数据 占空比
	F=[0.981;1.962;2.943;3.924;4.905;6.1803]; %推力数据 单位N
	p=polyfit(F,cmd,2) % 二次拟合
	plot(F,cmd);
	
	A = -0.0157
	B = 0.2484
	C = 0.0653
	
*/


void MotorThrust(float f1,float f2,float f3,float f4){
	
	float M1,M2,M3,M4;
	if(FlightControl.droneMode==Drone_Mode_4Axis){
		M1 = -0.0157f * f1 * f1 + 0.2484f * f1 + 0.0653f;
		M2 = -0.0157f * f2 * f2 + 0.2484f * f2 + 0.0653f;
		M3 = -0.0157f * f3 * f3 + 0.2484f * f3 + 0.0653f;
		M4 = -0.0157f * f4 * f4 + 0.2484f * f4 + 0.0653f;
	}
	else{
		f1 = f1 + 2.21395f;
		M1 = -0.0157f * f1 * f1 + 0.2484f * f1 + 0.0653f;
		f2 = f2 + 2.21395f;
		M2 = -0.0157f * f2 * f2 + 0.2484f * f2 + 0.0653f;
		f3 = f3 + 2.21395f;
		M3 = -0.0157f * f3 * f3 + 0.2484f * f3 + 0.0653f;
		f4 = f4 + 2.21395f;
		M4 = -0.0157f * f4 * f4 + 0.2484f * f4 + 0.0653f;
		
	}
	
	MotorThrustCallback(M1,M2,M3,M4,ARM_Length,0.016);
	
	
	Throttle_Info.M1 = (int)(M1 * 1000.0f) + UAVThrust.HeightThrust;
	Throttle_Info.M2 = (int)(M2 * 1000.0f) + UAVThrust.HeightThrust;
	Throttle_Info.M3 = (int)(M3 * 1000.0f) + UAVThrust.HeightThrust;
	Throttle_Info.M4 = (int)(M4 * 1000.0f) + UAVThrust.HeightThrust;
	
	if(Throttle_Info.M1 > 800)  Throttle_Info.M1=800;
	if(Throttle_Info.M2 > 800)  Throttle_Info.M2=800;
	if(Throttle_Info.M3 > 800)  Throttle_Info.M3=800;
	if(Throttle_Info.M4 > 800)  Throttle_Info.M4=800;

	if(Throttle_Info.M1 < 100)  Throttle_Info.M1=100;
	if(Throttle_Info.M2 < 100)  Throttle_Info.M2=100;
	if(Throttle_Info.M3 < 100)  Throttle_Info.M3=100;
	if(Throttle_Info.M4 < 100)  Throttle_Info.M4=100;
	
	PWM_OUTPUT(Throttle_Info.M1,Throttle_Info.M2,Throttle_Info.M3,Throttle_Info.M4);
	
}





void PWM_OUTPUT( unsigned int Motor1,
								 unsigned int Motor2,
								 unsigned int Motor3,
								 unsigned int Motor4)
{
	Motor1+=1000;
	Motor2+=1000;
	Motor3+=1000;
	Motor4+=1000;

	if(RT_Info.lowPowerFlag==1)
	{
		TIM2->CCR1=1000;
		TIM2->CCR2=1000;
		TIM2->CCR3=1000;
		TIM2->CCR4=1000;
	}
	else
	{
		TIM2->CCR1=Motor1;
		TIM2->CCR2=Motor2;
		TIM2->CCR3=Motor3;
		TIM2->CCR4=Motor4;
	}
}







