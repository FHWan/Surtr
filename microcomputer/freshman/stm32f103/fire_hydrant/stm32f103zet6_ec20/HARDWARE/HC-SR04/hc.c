#include "hc.h"
#include "delay.h"
#include "sys.h"


//第一个超声波硬件接口定义
#define HCSR041_PORT     GPIOB
#define HCSR041_CLK      RCC_APB2Periph_GPIOB
#define HCSR041_TRIG     GPIO_Pin_3
#define HCSR041_ECHO     GPIO_Pin_7
//第二个超声波
#define HCSR042_PORT     GPIOB
#define HCSR042_CLK      RCC_APB2Periph_GPIOB
#define HCSR042_TRIG     GPIO_Pin_12
#define HCSR042_ECHO     GPIO_Pin_13

u16 msHcCount = 0;
//定时器4设置
void hcsr04_NVIC()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
	NVIC_Init(&NVIC_InitStructure);
}

//IO口初始化 及其他初始化
void Hcsr041Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(HCSR041_CLK, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin =HCSR041_TRIG;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR041_PORT,HCSR041_TRIG);
     
    GPIO_InitStructure.GPIO_Pin =   HCSR041_ECHO;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);  
    GPIO_ResetBits(HCSR041_PORT,HCSR041_ECHO);    
     
          
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   
     
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period = (1000-1); 
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);          
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    
    hcsr04_NVIC();
    TIM_Cmd(TIM4,DISABLE);     
}


void Hcsr042Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(HCSR042_CLK, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin =HCSR042_TRIG;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HCSR042_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR042_PORT,HCSR042_TRIG);
     
    GPIO_InitStructure.GPIO_Pin =   HCSR042_ECHO;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR042_PORT, &GPIO_InitStructure);  
    GPIO_ResetBits(HCSR042_PORT,HCSR042_ECHO);    
     
          
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   
     
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period = (1000-1); 
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);          
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    
    hcsr04_NVIC();
    TIM_Cmd(TIM4,DISABLE);     
}
//打开定时器4
static void OpenTimerForHc()  
{
   TIM_SetCounter(TIM4,0);
   msHcCount = 0;
   TIM_Cmd(TIM4, ENABLE); 
}

//关闭定时器4
static void CloseTimerForHc()    
{
   TIM_Cmd(TIM4, DISABLE); 
}

//定时器4终中断
void TIM4_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 
       msHcCount++;
   }
}
 

//获取定时器4计数器值
u32 GetEchoTimer(void)
{
   u32 t = 0;
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM4);
   TIM4->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//通过定时器4计数器值推算距离
float Hcsr041GetLength(void )
{
   u32 t = 0;
   int i = 0;
   float lengthTemp1 = 0;
   float sum = 0;
   while(i!=5)
   {
      TRIG1_Send = 1;      
      delay_us(20);
      TRIG1_Send = 0;
      while(ECHO1_Reci == 0);      
      OpenTimerForHc();        
      i = i + 1;
      while(ECHO1_Reci == 1);
      CloseTimerForHc();        
      t = GetEchoTimer();        
      lengthTemp1 = ((float)t/58.0);//cm
      sum = lengthTemp1 + sum ;
        
    }
    lengthTemp1 = sum/5.0;
    return lengthTemp1;
}

//float Hcsr042GetLength(void )
//{
//   u32 t = 0;
//   int i = 0;
//   float lengthTemp2 = 0;
//   float sum = 0;
//   while(i!=5)
//   {
//      TRIG2_Send = 1;      
//      delay_us(20);
//      TRIG2_Send = 0;
//      while(ECHO2_Reci == 0);      
//      OpenTimerForHc();        
//      i = i + 1;
//      while(ECHO2_Reci == 1);
//      CloseTimerForHc();        
//      t = GetEchoTimer();        
//      lengthTemp2 = ((float)t/58.0);//cm
//      sum = lengthTemp2 + sum ;
//        
//    }
//    lengthTemp2 = sum/5.0;
//    return lengthTemp2;
//}
