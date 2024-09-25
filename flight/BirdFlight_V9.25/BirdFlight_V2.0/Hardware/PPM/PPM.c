/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Bluetooth.c
 * 描述   :蓝牙配置
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "PPM.h"

TIM_ICInitTypeDef  TIM1_ICInitStructure;

void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能TIM1时钟
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //PA11 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1); 
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);					
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4; 
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC4IE捕获中断	
	
  TIM_Cmd(TIM1,ENABLE ); 	//使能定时器5
}

u32 temp=0;
u8  TIM1CH4_CAPTURE_STA=0,ppm_rx_sta=0,ppm_rx_num=0;	//输入捕获状态		    				
u16	TIM1CH4_CAPTURE_VAL;	//输入捕获值
u16 ppm_rx[10];//ppm_rx[0]   1   接收到ppm数据
//定时器5中断服务程序	 
void TIM1_CC_IRQHandler(void)
{ 
	OS_ERR err;
	OSIntEnter();
	//抛出信号量
			if((TIM1CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{	  
			if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
			
			{	    
				if(TIM1CH4_CAPTURE_STA&0X40)//已经捕获到高电平了
				{
					if((TIM1CH4_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
					{
						TIM1CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
						TIM1CH4_CAPTURE_VAL=0XFFFF;
					}else TIM1CH4_CAPTURE_STA++;
				}	 
			}
			if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
			{	
				if(TIM1CH4_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
				{	  			
					TIM1CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
					TIM1CH4_CAPTURE_VAL=TIM_GetCapture4(TIM1);
					TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
				}else  								//还未开始,第一次捕获上升沿
				{
					TIM1CH4_CAPTURE_STA=0;			//清空
					TIM1CH4_CAPTURE_VAL=0;
					TIM_SetCounter(TIM1,0);
					TIM1CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
					TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				}		    
			}			     	    					   
		}
		
			//处理帧数据
		if(TIM1CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
//			temp=TIM5CH1_CAPTURE_STA&0X3F;
//			temp*=65536;//溢出时间总和
//			temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间

			
			if(ppm_rx_sta==1) 
			{
				ppm_rx[ppm_rx_num+1]=TIM1CH4_CAPTURE_VAL;
				ppm_rx_num++;
			}
			if(4>TIM1CH4_CAPTURE_STA&0X3F>0||TIM1CH4_CAPTURE_VAL>3000)
				ppm_rx_sta++;//低电平时间大于3000us为起始帧
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
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
			TIM1CH4_CAPTURE_STA=0;//开启下一次捕获
			
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
			  // 通道1控制Roll
			  /* 中间两个档位默认目标角度为0° */
			  if(Control_Info.CH1 <= Control_Info.CH1_Mid + 80 &&  Control_Info.CH1 >= Control_Info.CH1_Mid - 80)
				{
					Target_Info_Roll = 0;
				}
				else
				{
					/* Roll控制范围为 -26°~ 26°，修改数值16可改变范围 */	
					Target_Info_Roll = (Control_Info.CH1 -Control_Info.CH1_Mid)/40;
				}
				// 通道2控制pitch
			  /* 中间两个档位默认目标角度为0° */
			  if(Control_Info.CH2 <= Control_Info.CH2_Mid + 80 &&  Control_Info.CH2 >= Control_Info.CH2_Mid - 80)
				{
					Target_Info_Pitch = 0;
				}
				else
				{
					/* pitch控制范围为 -26°~ 26°，修改数值16可改变范围 */	
					Target_Info_Pitch = (Control_Info.CH2 - Control_Info.CH2_Mid)/40 ;
				}
				
			// 通道4控制Yaw
			  /* 中间两个档位默认目标角度为0° */
				if(Control_Info.CH4 <= Control_Info.CH4_Mid + 80 &&  Control_Info.CH4 >= Control_Info.CH4_Mid - 80)
				{
					Target_Info_Yaw = 0;
				}
				else
				{
					Target_Info_Yaw = (Control_Info.CH4 - Control_Info.CH4_Mid)/8 ;
				}
				
				//有头模式
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
				//无头模式分解控制量到pitch和roll  8个象限分解
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
				
				 // 飞行模式选择
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
						//原 RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.01f;
						else if(temp <= Control_Info.CH3_Mid - 80  )
						RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.03f;
						//原 RockerControl.ZaxisPos = (temp- Control_Info.CH3_Mid)* 0.006f;
				}
									
//				// 航向的速度环控制
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
//          /* 通过速度环来控制航向的转向 */					
//					Target_Info.RateYaw =  (temp[3] - Control_Info.CH4_Mid) / -800 ;
//					TargetYaw_Change =1 ;
//				}
				
//				// 飞行模式选择
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
//				// 有头无头模式选择
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
