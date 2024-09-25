/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Position_control.c
 * ����   :�⻷���ƺ���
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Position_control.h"
#include "arm_math.h"

void Position_control(unsigned char Data_flag,float Climb,float Decline){
//    /************************ �������  ************************/

    static unsigned char hover= 0; //�߶���ͣ��־λ
//	  static unsigned char poshold= 0; //�����־λ
//		static unsigned char setTargetPos= 0; //����Ŀ��λ�ñ�־λ
		static unsigned char controlCnt =0; //���ڿ������ڵļ���
    static float TgtHeight = 0;	  // Ŀ��߶ȱ���
		static Vector3f_t DesiredAcceleration;
	
	
	  UAVThrust.Gravity_Acceleration = 9.794f ;
		controlCnt++; //�������ڼ���  �ڻ�ÿ�ζ������ƣ��⻷���ο���������һ�ο���
    if(FlightControl.landFlag==1){
        //��������
        TgtHeight = TgtHeight - Decline;

        /************************�߶Ƚ������ ************************/
				if(controlCnt ==2)
				{
					  //�⻷��P������
						float heightErro = TgtHeight - RT_Info.Height;
						OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro , 1.0f ,-1.0f);
				}
        //�ٶȻ�PID������
        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,4) ,7,-7);
			  //���ٶȻ�PID������
				OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,5),10,-10);
				
//				//���ٶȻ�PID������
//        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,1) ,2,-2);


        /*10cm���� �������*/
        if(Sensor_Info.TofHeight<0.06f){
            TgtHeight = 0;
						FlightControl.ControlStart = false;
            Target_Info.Height = 1.0f; //�ָ���ʼ��Ĭ��Ŀ��߶�
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
//					 Target_Info.Height = 1.0f; //�ָ���ʼ��Ĭ��Ŀ��߶�
//						TgtHeight = 0;
//				}
			   /* �ֱ�ң�ظ߶ȿ����� */
        if(RockerControl.ZaxisPos ==0)
        {				
					  /* ��һ�λص���ͣ״̬�������ڵĸ߶�����ΪĿ��߶� */
            if(hover ==1)
            {
                Target_Info.Height = RT_Info.Height ;
                hover=0 ;
            }
            /************************�߶���ͣ���� ************************/
						/* ��һ����ɻ������� */
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
								//�⻷��P������
								float heightErro = TgtHeight - RT_Info.Height;
								OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro ,0.5f ,-0.5f);  //��1m/s��Ŀ���ٶ�
						}
							//�ٶȻ�PID������
						OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,5) ,7.0f,-7.0f);
						//���ٶȻ�PID������
						OriginalAccZ.value =  Limits_data(  PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,6),10.0f,-10.0f);
						
//						//���ٶȻ�PID������
//						OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,0,RT_Info.accZaxis,0.005,3),6.0f,-6.0f);
        }
        else
        {
            OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,RockerControl.ZaxisPos/100,RT_Info.Height_V,0.005,5) ,7.0f,-7.0f);
						//���ٶȻ�PID������
						OriginalAccZ.value =  Limits_data(  PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,6),10.f,-10.f);
					
//						//���ٶȻ�PID������
//						OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,RockerControl.ZaxisPos/40,RT_Info.accZaxis,0.005,3),6.0f,-6.0f);
          hover =1;
        }
    }
			
		UAVThrust.HeightThrust =  OriginalAccZ.value + UAVThrust.Gravity_Acceleration;
//				UAVThrust.HeightThrust =  RockerControl.ZaxisPos/40.0f + UAVThrust.Gravity_Acceleration;

    /************************ λ�û��ٶȿ�����  ************************/
    //ֻ�з������ĸ߶ȴ���10cm�ſ�ʼ����λ�ÿ���
    if(RT_Info.Height > 0.01f){
        switch (Data_flag){
            /************************ ��ͷģʽ���޶�λ��  ************************/
            case 0:
//                Target_Info.Pitch = Target_Info.RemotePitch;
//                Target_Info.Roll = Target_Info.RemoteRoll;
						
								Target_Info.Pitch = RockerControl.XaxisPos;
								Target_Info.Roll =  RockerControl.YaxisPos;
                break;
            /************************ ��ͷģʽ���޶�λ��  ************************/
            case 1:

                break;
            /************************ ����ģʽ  ************************/
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
            /************************ �������� ************************/
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
						/************************ �Ӿ���̼�ģʽ  ************************/
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
*�� �� ��: ComputeRobustBodyXAxis
*����˵��: ����body����ϵ
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/	
Vector3f_t ComputeRobustBodyXAxis(Vector3f_t x_B_prototype,Vector3f_t x_C,Vector3f_t y_C){
	Vector3f_t x_B = x_B_prototype;
	float x_BNorm = x_B.x * x_B.x + x_B.y * x_B.y + x_B.z * x_B.z;
	if(almostZero(x_BNorm)){
		// ��y_c �� z_b == 0 �����ǹ��� ��ʱ�Ǵ�ֱ�˶����ݲ�����
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
*�� �� ��: ComputeDesiredAttitude
*����˵��: ����������̬
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/	
void ComputeDesiredAttitude(Vector3f_t DesiredAcceleration,float reference_heading){
	//�����������ת �������
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
	//������������
	Matrix3_Mul_Matrix1(headingOrientation,UnitX,&X_C);
	Matrix3_Mul_Matrix1(headingOrientation,UnitY,&Y_C);
	
	Vector3f_t Z_B;
	float AccNorm = DesiredAcceleration.x * DesiredAcceleration.x 
										+ DesiredAcceleration.y * DesiredAcceleration.y 
												+ DesiredAcceleration.z + DesiredAcceleration.z;
	//����������� ���ټ�ʧȥ����
	if(almostZero(AccNorm)){
		/**�˴����費���ܲ������������˶�**/
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
	
	��λ���� a = a1*I + a2*J + a3*K   b = b1*I + b2*I2 + b3*I3
	a��b = (a2b3 - a3b2)I + (a3b1 - a1b3)J + (a1b2 - a2b1)K
	
				a2b3 - a3b2
	a��b = a3b1 - a1b3
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


