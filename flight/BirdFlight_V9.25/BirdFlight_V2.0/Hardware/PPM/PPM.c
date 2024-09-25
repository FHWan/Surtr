/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Bluetooth.c
 * ����   :��������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "PPM.h"

TIM_ICInitTypeDef  TIM1_ICInitStructure;

void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ��TIM1ʱ��
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //PA11 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //���� 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1); 
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);					
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4; 
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC4IE�����ж�	
	
  TIM_Cmd(TIM1,ENABLE ); 	//ʹ�ܶ�ʱ��5
}

u32 temp=0;
u8  TIM1CH4_CAPTURE_STA=0,ppm_rx_sta=0,ppm_rx_num=0;	//���벶��״̬		    				
u16	TIM1CH4_CAPTURE_VAL;	//���벶��ֵ
u16 ppm_rx[10];//ppm_rx[0]   1   ���յ�ppm����
//��ʱ��5�жϷ������	 
void TIM1_CC_IRQHandler(void)
{ 
	OS_ERR err;
	OSIntEnter();
	//�׳��ź���
			if((TIM1CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{	  
			if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
			
			{	    
				if(TIM1CH4_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM1CH4_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
					{
						TIM1CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
						TIM1CH4_CAPTURE_VAL=0XFFFF;
					}else TIM1CH4_CAPTURE_STA++;
				}	 
			}
			if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)//����1���������¼�
			{	
				if(TIM1CH4_CAPTURE_STA&0X40)		//����һ���½��� 		
				{	  			
					TIM1CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
					TIM1CH4_CAPTURE_VAL=TIM_GetCapture4(TIM1);
					TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
				}else  								//��δ��ʼ,��һ�β���������
				{
					TIM1CH4_CAPTURE_STA=0;			//���
					TIM1CH4_CAPTURE_VAL=0;
					TIM_SetCounter(TIM1,0);
					TIM1CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
					TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				}		    
			}			     	    					   
		}
		
			//����֡����
		if(TIM1CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
//			temp=TIM5CH1_CAPTURE_STA&0X3F;
//			temp*=65536;//���ʱ���ܺ�
//			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��

			
			if(ppm_rx_sta==1) 
			{
				ppm_rx[ppm_rx_num+1]=TIM1CH4_CAPTURE_VAL;
				ppm_rx_num++;
			}
			if(4>TIM1CH4_CAPTURE_STA&0X3F>0||TIM1CH4_CAPTURE_VAL>3000)
				ppm_rx_sta++;//�͵�ƽʱ�����3000usΪ��ʼ֡
			if(ppm_rx_sta==2) 
			{
				ppm_rx_sta=0;ppm_rx[0]=1;ppm_rx_num=0;				
				Control_Info.CH1 = ppm_rx[1];
				Control_Info.CH2 = ppm_rx[2];
				Control_Info.CH3 = ppm_rx[3];
				Control_Info.CH4 = ppm_rx[4];
				Control_Info.CH5 = ppm_rx[5];
				Control_Info.CH6 = ppm_rx[6];
				Control_Info.CH7 = ppm_rx[7];
				
				for(int j=1 ;j<8; j++)
				{
					ppm_rx[j] =0;
				}
						
				OSSemPost(&PPM_proc,OS_OPT_POST_1,&err);
			}
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
			TIM1CH4_CAPTURE_STA=0;//������һ�β���
			
		}

	OSIntExit();
}
		
		
void PPM_dataDeal(void)
{
	  static float  Target_Info_Roll ,Target_Info_Pitch=0,Target_Info_Yaw=0;;
	  static float  deltaYaw , segYaw=0;
	  if(//FlightControl.OnOff==Drone_On && FlightControl.droneMode == Drone_Mode_4Axis 
			  Control_Info.CH1>=(Control_Info.CH1_Min -10)  && (Control_Info.CH1<=Control_Info.CH1_Max + 10) 
				&& Control_Info.CH2>=(Control_Info.CH2_Min -10)  && (Control_Info.CH2<=Control_Info.CH2_Max + 10)
				&& Control_Info.CH3>=(Control_Info.CH3_Min -10)  && (Control_Info.CH3<=Control_Info.CH3_Max + 10)
				&& Control_Info.CH4>=(Control_Info.CH4_Min -10)  && (Control_Info.CH4<=Control_Info.CH4_Max + 10)
				&& Control_Info.CH5>=(Control_Info.CH5_Min -10)  && (Control_Info.CH5<=Control_Info.CH5_Max + 10)
				&& Control_Info.CH6>=(Control_Info.CH6_Min -10)  && (Control_Info.CH6<=Control_Info.CH6_Max + 10) )
		{
			  // ͨ��1����Roll
			  /* �м�������λĬ��Ŀ��Ƕ�Ϊ0�� */
			  if(Control_Info.CH1 <= Control_Info.CH1_Mid + 80 &&  Control_Info.CH1 >= Control_Info.CH1_Mid - 80)
				{
					Target_Info_Roll = 0;
				}
				else
				{
					/* Roll���Ʒ�ΧΪ -26��~ 26�㣬�޸���ֵ16�ɸı䷶Χ */	
					Target_Info_Roll = (Control_Info.CH1 -Control_Info.CH1_Mid)/40;
				}
				// ͨ��2����pitch
			  /* �м�������λĬ��Ŀ��Ƕ�Ϊ0�� */
			  if(Control_Info.CH2 <= Control_Info.CH2_Mid + 80 &&  Control_Info.CH2 >= Control_Info.CH2_Mid - 80)
				{
					Target_Info_Pitch = 0;
				}
				else
				{
					/* pitch���Ʒ�ΧΪ -26��~ 26�㣬�޸���ֵ16�ɸı䷶Χ */	
					Target_Info_Pitch = (Control_Info.CH2 - Control_Info.CH2_Mid)/40 ;
				}
				
			// ͨ��4����Yaw
			  /* �м�������λĬ��Ŀ��Ƕ�Ϊ0�� */
				if(Control_Info.CH4 <= Control_Info.CH4_Mid + 80 &&  Control_Info.CH4 >= Control_Info.CH4_Mid - 80)
				{
					Target_Info_Yaw = 0;
				}
				else
				{
					Target_Info_Yaw = (Control_Info.CH4 - Control_Info.CH4_Mid)/8 ;
				}
				
				//��ͷģʽ
				if(Flight_Remote_Control.FlightHeadingMode == Heading)
				{
						Target_Info.RemotePitch = Target_Info_Pitch;
						Target_Info.RemoteRoll = Target_Info_Roll;
						if(FlightControl.OnOff==Drone_On)
						{
							RockerControl.Navigation = -Target_Info_Yaw;
							RockerControl.XaxisPos = Target_Info_Pitch;
							RockerControl.YaxisPos = -Target_Info_Roll;
						}
				}
				//��ͷģʽ�ֽ��������pitch��roll  8�����޷ֽ�
				else if(Flight_Remote_Control.FlightHeadingMode == Headless)
				{				
					if(RT_Info.HomeYaw  >= 0)
					{
						segYaw =  RT_Info.HomeYaw  - 180;
						if  ( RT_Info.Yaw <=180  && RT_Info.Yaw >= RT_Info.HomeYaw )  
						{
							deltaYaw =   RT_Info.Yaw  - RT_Info.HomeYaw;
						}
						else if(RT_Info.Yaw > -180  && RT_Info.Yaw <= segYaw )
						{
							deltaYaw =  180 - RT_Info.HomeYaw +  RT_Info.Yaw + 180 ;
						}
						else if(RT_Info.Yaw >= 0  && RT_Info.Yaw < RT_Info.HomeYaw)
						{
							deltaYaw =  RT_Info.Yaw  - RT_Info.HomeYaw;
						}
						else if(RT_Info.Yaw < 0  && RT_Info.Yaw >= segYaw)
						{
							deltaYaw =  - RT_Info.HomeYaw +  RT_Info.Yaw;
						}
					}
					else
					{
						segYaw = 180 + RT_Info.HomeYaw;
						if  ( RT_Info.Yaw <0  && RT_Info.Yaw >= RT_Info.HomeYaw )  
						{
							deltaYaw =  RT_Info.Yaw - RT_Info.HomeYaw; 
						}
						else if(RT_Info.Yaw >=0  && RT_Info.Yaw <= segYaw )
						{
							deltaYaw =  - RT_Info.HomeYaw +  RT_Info.Yaw  ;
						}
						else if(RT_Info.Yaw > -180  && RT_Info.Yaw < RT_Info.HomeYaw)
						{
							deltaYaw =  RT_Info.Yaw  - RT_Info.HomeYaw;
						}
						else if(RT_Info.Yaw <= 180  && RT_Info.Yaw > segYaw)
						{
							deltaYaw = -180 - RT_Info.HomeYaw +  RT_Info.Yaw -180;
						}						
					}
					
					
					Target_Info.RemotePitch =  Target_Info_Pitch * cos( deltaYaw /180*PI) - Target_Info_Roll * sin(deltaYaw/180*PI) ;
					Target_Info.RemoteRoll = Target_Info_Pitch * sin(deltaYaw/180*PI) + Target_Info_Roll * cos(deltaYaw/180*PI);
				}
				
				 // ����ģʽѡ��
        if( Control_Info.CH5 <= Control_Info.CH5_Min + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Min-80)
        {
            FlightControl.OnOff = Drone_Off;
        }
        else if( Control_Info.CH5 <= Control_Info.CH5_Mid + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Mid-80)
        {
            FlightControl.OnOff = Drone_On;
            FlightControl.DroneMode=Drone_Mode_4Axis;
        }
        else if( Control_Info.CH5 <= Control_Info.CH5_Max + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Max-80)
        {
            FlightControl.landFlag=1;
        }
				
				
				Target_Info.RemotePitch = Target_Info_Pitch;
				Target_Info.RemoteRoll = Target_Info_Roll;
				
				
				if(Control_Info.CH3 <=  Control_Info.CH3_Mid + 80 &&  Control_Info.CH3 >=  Control_Info.CH3_Mid - 80)
				{
						RockerControl.ZaxisPos = 0.0f;
				}
				else
				{
						float temp = (float )Control_Info.CH3 ;	
						if(temp >= Control_Info.CH3_Mid + 80)
						RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.1f;	
						//ԭ RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.01f;
						else if(temp <= Control_Info.CH3_Mid - 80  )
						RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.03f;
						//ԭ RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.006f;
				}
									
//				// ������ٶȻ�����
//				if( ( Control_Info.CH4 <= Control_Info.CH4_Mid + 80  &&  Control_Info.CH4 >= Control_Info.CH4_Mid -80) 
//    					|| ( Control_Info.CH3 <= Control_Info.CH3_Min + 15)  )  // && Acc_z <= 0.25f)
//				{
//					if( TargetYaw_Change==1)
//					{
//					  Target_Info.RateYaw = 0;
//						Target_Info.Yaw = RT_Info.Yaw ;
//						TargetYaw_Change =0;
//				 }
//				}
//				else
//				{
//					temp[3] = (float )Control_Info.CH4 ;	
//          /* ͨ���ٶȻ������ƺ����ת�� */					
//					Target_Info.RateYaw =  (temp[3] - Control_Info.CH4_Mid) / -800 ;
//					TargetYaw_Change =1 ;
//				}
				
//				// ����ģʽѡ��
//				if( Control_Info.CH5 <= Control_Info.CH5_Min + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Min-80) 
//				{
//						if(Flight_Remote_Control.FlightControlMode !=   Flight_Remote_Control.CH5_Mode1 )
//						{
//							Beep_RingsOnce();	
//							Flight_Remote_Control.FlightControlMode =   Flight_Remote_Control.CH5_Mode1 ;
//						}
//				}
//				else if( Control_Info.CH5 <= Control_Info.CH5_Mid + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Mid-80) 
//				{
//						if(Flight_Remote_Control.FlightControlMode !=   Flight_Remote_Control.CH5_Mode2 )
//						{
//							Beep_RingsOnce();	
//							Flight_Remote_Control.FlightControlMode =   Flight_Remote_Control.CH5_Mode2 ;
//						}
//				}
//				else if( Control_Info.CH5 <= Control_Info.CH5_Max + 80  &&  Control_Info.CH5 >= Control_Info.CH5_Max-80) 
//				{
//						if(Flight_Remote_Control.FlightControlMode !=   Flight_Remote_Control.CH5_Mode3 )
//						{
//							Beep_RingsOnce();	
//							Flight_Remote_Control.FlightControlMode =   Flight_Remote_Control.CH5_Mode3 ;
//						}
//				}
//				
//				
//				// ��ͷ��ͷģʽѡ��
//				if( Control_Info.CH6 <= Control_Info.CH6_Min + 80  &&  Control_Info.CH6 >= Control_Info.CH6_Min-80) 
//				{
//						if(Flight_Remote_Control.FlightHeadingMode !=   Flight_Remote_Control.CH6_Mode1 )
//						{
//							Beep_RingsOnce();	
//							Flight_Remote_Control.FlightHeadingMode =   Flight_Remote_Control.CH6_Mode1 ;
//						}
//				}
//				else if( Control_Info.CH6 <= Control_Info.CH6_Max + 80  &&  Control_Info.CH6 >= Control_Info.CH6_Max-80) 
//				{
//						if(Flight_Remote_Control.FlightHeadingMode !=   Flight_Remote_Control.CH6_Mode2 )
//						{
//							Beep_RingsOnce();	
//							Flight_Remote_Control.FlightHeadingMode =   Flight_Remote_Control.CH6_Mode2 ;
//						}
//				}
				
		}

}


void Remote_Control_Mode_Init(void)
{
	Flight_Remote_Control.FlightControlMode =  Flight_Remote_Control.CH5_Mode1 ;
	Flight_Remote_Control.FlightHeadingMode =  Flight_Remote_Control.CH6_Mode1 ;
}
