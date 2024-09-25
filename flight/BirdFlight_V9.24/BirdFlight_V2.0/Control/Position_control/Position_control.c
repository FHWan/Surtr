/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Position_control.c
 * 描述   :外环控制函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Position_control.h"
#include "arm_math.h"

void Position_control(unsigned char Data_flag,float Climb,float Decline){
//    /************************ 降落控制  ************************/

    static unsigned char hover= 0; //高度悬停标志位
//	  static unsigned char poshold= 0; //定点标志位
//		static unsigned char setTargetPos= 0; //设置目标位置标志位
		static unsigned char controlCnt =0; //用于控制周期的计数
    static float TgtHeight = 0;	  // 目标高度变量
		static Vector3f_t DesiredAcceleration;
	
	
	  UAVThrust.Gravity_Acceleration = 9.794f ;
		controlCnt++; //控制周期计数  内环每次都做控制，外环两次控制周期做一次控制
    if(FlightControl.landFlag==1){
        //缓慢降落
        TgtHeight = TgtHeight - Decline;

        /************************高度降落控制 ************************/
				if(controlCnt ==2)
				{
					  //外环单P控制器
						float heightErro = TgtHeight - RT_Info.Height;
						OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro , 1.0f ,-1.0f);
				}
        //速度环PID控制器
        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,4) ,7,-7);
			  //加速度环PID控制器
				OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,5),10,-10);
				
//				//加速度环PID控制器
//        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,1) ,2,-2);


        /*10cm以下 电机怠速*/
        if(Sensor_Info.TofHeight<0.06f){
            TgtHeight = 0;
						FlightControl.ControlStart = false;
            Target_Info.Height = 1.0f; //恢复初始的默认目标高度
						RestartT265();
					  FlightControl.OnOff = Drone_Land;
						RT_Info.CpuTick=0;
            FlightControl.landFlag = 0;
						Flight_Remote_Control.FlightControlMode =  VIOCruise;
						FlightControl.ArmPower =	ArmPowerON;
        }
    }
    else
		{		
//				if(FlightControl.OnOff == Drone_Off)
//				{
//					 Target_Info.Height = 1.0f; //恢复初始的默认目标高度
//						TgtHeight = 0;
//				}
			   /* 手柄遥控高度控制器 */
        if(RockerControl.ZaxisPos ==0)
        {				
					  /* 第一次回到悬停状态，将现在的高度设置为目标高度 */
            if(hover ==1)
            {
                Target_Info.Height = RT_Info.Height ;
                hover=0 ;
            }
            /************************高度悬停控制 ************************/
						/* 第一次起飞缓慢上升 */
						if(TgtHeight < Target_Info.Height && FlightControl.LaunchFlag == true){
//									Target_Info.Height = Target_Info.RoutePlanZ;
									TgtHeight = TgtHeight + Climb ;
						}
						else{
//									Target_Info.Height = Target_Info.RoutePlanZ;
									TgtHeight = Target_Info.Height;
									if(  ( ( RT_Info.VioPosition_Z < 0.85f* (Sensor_Info.TofHeight-0.06f))
										    || ( RT_Info.VioPosition_Z > 1.15f* (Sensor_Info.TofHeight-0.06f) ) )
									         && DataCombineflag == Data_Follow 
															&& FlightControl.LaunchFlag == true	
																&&  abs(Target_Info.Height - Sensor_Info.TofHeight) <=0.05f  )
									{
										  DataCombineflag = Data_Flow;
											RT_Info.VioAbnormal = true;
											Target_Info.Yaw = RT_Info.Yaw;
//											Target_Info.PositionX = 0;
//											Target_Info.PositionY = 0;
											FlightControl.poshold = 1;
											FlightControl.setTargetPos = 0;
									}
									
									FlightControl.LaunchFlag = false ;
						}


						if(controlCnt ==2)
						{
								//外环单P控制器
								float heightErro = TgtHeight - RT_Info.Height;
								OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro ,0.5f ,-0.5f);  //±1m/s的目标速度
						}
							//速度环PID控制器
						OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,5) ,7.0f,-7.0f);
						//加速度环PID控制器
						OriginalAccZ.value =  Limits_data(  PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,6),10.0f,-10.0f);
						
//						//加速度环PID控制器
//						OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,0,RT_Info.accZaxis,0.005,3),6.0f,-6.0f);
        }
        else
        {
            OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,RockerControl.ZaxisPos/100,RT_Info.Height_V,0.005,5) ,7.0f,-7.0f);
						//加速度环PID控制器
						OriginalAccZ.value =  Limits_data(  PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,6),10.f,-10.f);
					
//						//加速度环PID控制器
//						OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,RockerControl.ZaxisPos/40,RT_Info.accZaxis,0.005,3),6.0f,-6.0f);
          hover =1;
        }
    }
			
		UAVThrust.HeightThrust =  OriginalAccZ.value + UAVThrust.Gravity_Acceleration;
//				UAVThrust.HeightThrust =  RockerControl.ZaxisPos/40.0f + UAVThrust.Gravity_Acceleration;

    /************************ 位置环速度控制器  ************************/
    //只有飞行器的高度大于10cm才开始进行位置控制
    if(RT_Info.Height > 0.01f){
        switch (Data_flag){
            /************************ 有头模式（无定位）  ************************/
            case 0:
//                Target_Info.Pitch = Target_Info.RemotePitch;
//                Target_Info.Roll = Target_Info.RemoteRoll;
						
								Target_Info.Pitch = RockerControl.XaxisPos;
								Target_Info.Roll =  RockerControl.YaxisPos;
                break;
            /************************ 无头模式（无定位）  ************************/
            case 1:

                break;
            /************************ 定点模式  ************************/
            case 2:
										if(RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 &&
														RT_Info.VioPosition_X!=0 && RT_Info.VioPosition_Y!=0 && RT_Info.VioPosition_Z!=0)
										{
												
												OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

												Target_Info.DesiredAccelerationX =  Limits_data( PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
																													 RT_Info.PointX_V,0.005,3) , 6 , -6 );

												OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

												Target_Info.DesiredAccelerationY  = Limits_data( - PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
																													 RT_Info.PointY_V,0.005,3) , 6 , -6);										
																												
											
											DesiredAcceleration.x = Target_Info.DesiredAccelerationX;
											DesiredAcceleration.y = Target_Info.DesiredAccelerationY;
											DesiredAcceleration.z = UAVThrust.HeightThrust;
											ComputeDesiredAttitude(DesiredAcceleration,0);
										}
										else
										{
												Target_Info.Pitch = RockerControl.XaxisPos;
												Target_Info.Roll = RockerControl.YaxisPos;
										}
                break;
            /************************ 光流定点 ************************/
            case 3:
								if( RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 && 	
													RT_Info.FlowX_V!=0 && RT_Info.FlowY_V!=0 )
								{				
										if(  (cos(RT_Info.Pitch/57.3f)*cos(RT_Info.Roll/57.3f))>=0.99f  && 												
															sqrt(RT_Info.FlowX_V*RT_Info.FlowX_V +RT_Info.FlowY_V *RT_Info.FlowY_V ) <=0.1f
																	&&	FlightControl.poshold == 1 )
										{	
													Target_Info.PositionX = RT_Info.FlowX;
													Target_Info.PositionY = RT_Info.FlowY;
													FlightControl.setTargetPos = 1 ;
													FlightControl.poshold = 0 ;
										}
										else
										{
												if(FlightControl.setTargetPos ==1  && RockerControl.Navigation == 0)
												{
														float PosXerr =  Target_Info.PositionX -  RT_Info.FlowX;												
														float PosYerr =  Target_Info.PositionY -  RT_Info.FlowY;
														OriginalFlowX.value = Limits_data( PID_ParaInfo.FlowX.Kp * PosXerr,0.6f,-0.6f);
														OriginalFlowY.value = Limits_data( PID_ParaInfo.FlowY.Kp * PosYerr,0.6f,-0.6f);
												}
												else
												{
														OriginalFlowX.value =0;
														OriginalFlowY.value =0;
														OriginalFlowVelX.iOut =0 ;
														OriginalFlowVelY.iOut =0 ;
												}

										}
										
										Target_Info.DesiredAccelerationX = Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalFlowX.value,
																										 RT_Info.FlowX_V,0.005f,1.5) , 6, -6 ) ;

										Target_Info.DesiredAccelerationY = Limits_data( PID_Control(&PID_ParaInfo.FlowVelY,&OriginalFlowVelY,OriginalFlowY.value,
																											RT_Info.FlowY_V,0.005f,1.5) ,6, -6 );	
																																																					
										DesiredAcceleration.x = Target_Info.DesiredAccelerationX;
										DesiredAcceleration.y = Target_Info.DesiredAccelerationY;
										DesiredAcceleration.z = UAVThrust.HeightThrust;
										ComputeDesiredAttitude(DesiredAcceleration,0);																					
										
								}
								else
								{
										Target_Info.Pitch = RockerControl.XaxisPos;
										Target_Info.Roll = RockerControl.YaxisPos;
										OriginalFlowVelX.iOut =0 ;
										OriginalFlowVelY.iOut =0 ;
										FlightControl.poshold = 1;
										FlightControl.setTargetPos = 0;
								}
                break;
						/************************ 视觉里程计模式  ************************/
            case 4:
										if( RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 && 	
													RT_Info.VioVel_X!=0 && RT_Info.VioVel_Y!=0 && RT_Info.VioVel_Z!=0 &&  Flight_Remote_Control.FlightControlMode == VIOCruise )
										{
													float PosXerr =  Target_Info.RoutePlanX -  RT_Info.VioPosition_X;												
													float PosYerr =  Target_Info.RoutePlanY -  RT_Info.VioPosition_Y;

											    if( abs(Target_Info.RoutePlanZ - RT_Info.Height) >=0.1f )
													{
															OriginalPosX.value = Limits_data( PID_ParaInfo.PosX.Kp * PosXerr,0.4f,-0.4f);
															OriginalPosY.value = Limits_data( PID_ParaInfo.PosY.Kp * PosYerr,0.4f,-0.4f);
													}
													else
													{															
															OriginalPosX.value = Limits_data( PID_ParaInfo.PosX.Kp * PosXerr,0.4f,-0.4f);
															OriginalPosY.value = Limits_data( PID_ParaInfo.PosY.Kp * PosYerr,0.4f,-0.4f);													
													}


//													Target_Info.DesiredAccelerationX =  Limits_data( PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
//																														 RT_Info.VioVel_X,0.005f,1) , 6 , -6 );							
//													Target_Info.DesiredAccelerationY  = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
//																														 RT_Info.VioVel_Y,0.005f,1) , 6 , -6 );			
													Target_Info.DesiredAccelerationX = Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalPosX.value,
																													 RT_Info.FlowX_V,0.005f,1.5) , 6, -6 ) ;

													Target_Info.DesiredAccelerationY = Limits_data( PID_Control(&PID_ParaInfo.FlowVelY,&OriginalFlowVelY,OriginalPosY.value,
																														RT_Info.FlowY_V,0.005f,1.5) ,6, -6 );	
																																																							
													DesiredAcceleration.x = Target_Info.DesiredAccelerationX;
													DesiredAcceleration.y = Target_Info.DesiredAccelerationY;
													DesiredAcceleration.z = UAVThrust.HeightThrust;
													ComputeDesiredAttitude(DesiredAcceleration,0);
										}
										else if( RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 && 	
																RT_Info.VioVel_X!=0 && RT_Info.VioVel_Y!=0 && RT_Info.VioVel_Z!=0 &&  Flight_Remote_Control.FlightControlMode == VIOPosHold)
										{

											
												if(  (cos(RT_Info.Pitch/57.3f)*cos(RT_Info.Roll/57.3f))>=0.98f  && 												
																	sqrt(RT_Info.VioVel_X*RT_Info.VioVel_X +RT_Info.VioVel_Y *RT_Info.VioVel_Y ) <=0.2f
																			&&	FlightControl.poshold == 1 )
												{	
															Target_Info.PositionX = RT_Info.VioPosition_X;
															Target_Info.PositionY = RT_Info.VioPosition_Y;
															FlightControl.setTargetPos = 1 ;
															FlightControl.poshold = 0 ;
												}
												else
												{
													  if(FlightControl.setTargetPos ==1)
														{
																float PosXerr =  Target_Info.PositionX -  RT_Info.VioPosition_X;												
																float PosYerr =  Target_Info.PositionY -  RT_Info.VioPosition_Y;
																OriginalPosX.value = Limits_data( PID_ParaInfo.PosX.Kp * PosXerr,0.4f,-0.4f);
																OriginalPosY.value = Limits_data( PID_ParaInfo.PosY.Kp * PosYerr,0.4f,-0.4f);
														}
														else
														{
																OriginalPosX.value =0;
																OriginalPosY.value =0;
														}

												}
//												Target_Info.DesiredAccelerationX =  Limits_data( PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
//																														 RT_Info.VioVel_X,0.005f,1) , 6 , -6 );							
//												Target_Info.DesiredAccelerationY  = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
//																														 RT_Info.VioVel_Y,0.005f,1) , 6 , -6 );			
													Target_Info.DesiredAccelerationX = Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalPosX.value,
																													 RT_Info.FlowX_V,0.005f,1.5) , 6, -6 ) ;

													Target_Info.DesiredAccelerationY = Limits_data( PID_Control(&PID_ParaInfo.FlowVelY,&OriginalFlowVelY,OriginalPosY.value,
																														RT_Info.FlowY_V,0.005f,1.5) ,6, -6 );	
																																																							
												DesiredAcceleration.x = Target_Info.DesiredAccelerationX;
												DesiredAcceleration.y = Target_Info.DesiredAccelerationY;
												DesiredAcceleration.z = UAVThrust.HeightThrust;
												ComputeDesiredAttitude(DesiredAcceleration,0);																							
										}
										else
										{
												Flight_Remote_Control.FlightControlMode = VIOPosHold;
												Target_Info.Pitch = RockerControl.XaxisPos;
												Target_Info.Roll = RockerControl.YaxisPos;
												OriginalVelX.iOut =0 ;
												OriginalVelY.iOut =0 ;
												FlightControl.poshold = 1;
											  FlightControl.setTargetPos = 0;
										}
                break;
            default:

                break;
        }

    }
		if(controlCnt == 2)
			controlCnt =0;
}



bool almostZero(float value){
  return fabs(value) < kAlmostZeroValueThreshold;
}

/**********************************************************************************************************
*函 数 名: ComputeRobustBodyXAxis
*功能说明: 计算body坐标系
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/	
Vector3f_t ComputeRobustBodyXAxis(Vector3f_t x_B_prototype,Vector3f_t x_C,Vector3f_t y_C){
	Vector3f_t x_B = x_B_prototype;
	float x_BNorm = x_B.x * x_B.x + x_B.y * x_B.y + x_B.z * x_B.z;
	if(almostZero(x_BNorm)){
		// 若y_c × z_b == 0 则它们共线 此时是垂直运动，暂不考虑
		x_B.x = x_B.x / sqrtf(x_BNorm);
		x_B.y = x_B.y / sqrtf(x_BNorm);
		x_B.z = x_B.z / sqrtf(x_BNorm);
	}else{
		x_B.x = x_B.x / sqrtf(x_BNorm);
		x_B.y = x_B.y / sqrtf(x_BNorm);
		x_B.z = x_B.z / sqrtf(x_BNorm);
	}
	return x_B;
	
}


/**********************************************************************************************************
*函 数 名: ComputeDesiredAttitude
*功能说明: 计算期望姿态
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/	
void ComputeDesiredAttitude(Vector3f_t DesiredAcceleration,float reference_heading){
	//若航向产生旋转 则需计算
	float headingOrientation[9];
	headingOrientation[0] = cosf(reference_heading);
	headingOrientation[1] = -sinf(reference_heading);
	headingOrientation[2] = 0.0f;
	headingOrientation[3] = sinf(reference_heading);
	headingOrientation[4] = cosf(reference_heading);
	headingOrientation[5] = 0.0f;
	headingOrientation[6] = 0.0f;
	headingOrientation[7] = 0.0f;
	headingOrientation[8] = 1.0f;
	float UnitX[3] = {1,0,0};
	float UnitY[3] = {0,1,0};
	Vector3f_t X_C,Y_C;
	//计算期望方向
	Matrix3_Mul_Matrix1(headingOrientation,UnitX,&X_C);
	Matrix3_Mul_Matrix1(headingOrientation,UnitY,&Y_C);
	
	Vector3f_t Z_B;
	float AccNorm = DesiredAcceleration.x * DesiredAcceleration.x 
										+ DesiredAcceleration.y * DesiredAcceleration.y 
												+ DesiredAcceleration.z + DesiredAcceleration.z;
	//自由落体情况 加速计失去作用
	if(almostZero(AccNorm)){
		/**此处假设不可能产生自由落体运动**/
		AccNorm = 0.05f;
		Z_B.x = DesiredAcceleration.x / sqrtf(AccNorm);
		Z_B.y = DesiredAcceleration.y / sqrtf(AccNorm);
		Z_B.z = DesiredAcceleration.z / sqrtf(AccNorm);
	}else{
		Z_B.x = DesiredAcceleration.x / sqrtf(AccNorm);
		Z_B.y = DesiredAcceleration.y / sqrtf(AccNorm);
		Z_B.z = DesiredAcceleration.z / sqrtf(AccNorm);
	}
/*
	
	单位向量 a = a1*I + a2*J + a3*K   b = b1*I + b2*I2 + b3*I3
	a×b = (a2b3 - a3b2)I + (a3b1 - a1b3)J + (a1b2 - a2b1)K
	
				a2b3 - a3b2
	a×b = a3b1 - a1b3
				a1b2 - a2b1
	
*/
	Vector3f_t x_B_prototype;
	x_B_prototype.x = Y_C.y * Z_B.z - Y_C.z * Z_B.y;
	x_B_prototype.y = Y_C.z * Z_B.x - Y_C.x * Z_B.z;
	x_B_prototype.z = Y_C.x * Z_B.y - Y_C.y * Z_B.x;
	Vector3f_t X_B = ComputeRobustBodyXAxis(x_B_prototype,X_C,Y_C);
	
	Vector3f_t Y_B;
	Y_B.x = Z_B.y * X_B.z - Z_B.z * X_B.y;
	Y_B.y = Z_B.z * X_B.x - Z_B.x * X_B.z;
	Y_B.z = Z_B.x * X_B.y - Z_B.y * X_B.x;
	float Y_BNorm = Y_B.x * Y_B.x + Y_B.y * Y_B.y + Y_B.z * Y_B.z;
	Y_B.x = Y_B.x / sqrtf(Y_BNorm);
	Y_B.y = Y_B.y / sqrtf(Y_BNorm);
	Y_B.z = Y_B.z / sqrtf(Y_BNorm);
	
	float R_W_B[9];
	R_W_B[0] = X_B.x;R_W_B[1] = Y_B.x;R_W_B[2] = Z_B.x;
	R_W_B[3] = X_B.y;R_W_B[4] = Y_B.y;R_W_B[5] = Z_B.y;
	R_W_B[6] = X_B.z;R_W_B[7] = Y_B.z;R_W_B[8] = Z_B.z;
	
	
	Target_Info.Roll  = ConstrainFloat(atan2(R_W_B[7],R_W_B[8]), -0.2f, 0.2f) *57.3f;
	Target_Info.Pitch = - ConstrainFloat(-atan2(R_W_B[6],sqrtf(R_W_B[7]*R_W_B[7] + R_W_B[8]*R_W_B[8])), -0.2f, 0.2f) *57.3f;


}


