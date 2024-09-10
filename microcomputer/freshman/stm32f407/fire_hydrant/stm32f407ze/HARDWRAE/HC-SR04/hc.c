#include "hc.h"
#include "delay.h"
#include "sys.h"


//第一个超声波硬件接口定义
#define HCSR041_PORT     GPIOA
#define HCSR041_CLK      RCC_AHB1Periph_GPIOA
#define HCSR041_TRIG     GPIO_Pin_0
#define HCSR041_ECHO     GPIO_Pin_1

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
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   // 定义定时器结构体变量
    GPIO_InitTypeDef GPIO_InitStructure;              // 定义GPIO结构体变量
    RCC_AHB1PeriphClockCmd(HCSR041_CLK, ENABLE);      // 使能GPIOA时钟
   
    GPIO_InitStructure.GPIO_Pin = HCSR041_TRIG;       // 设置TRIG引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置IO口速度为50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     // 设置IO口模式为输出
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);     // 初始化GPIOA的TRIG引脚
    GPIO_ResetBits(HCSR041_PORT, HCSR041_TRIG);       // 将TRIG引脚置低
     
    GPIO_InitStructure.GPIO_Pin = HCSR041_ECHO;       // 设置ECHO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      // 设置IO口模式为输入
    GPIO_Init(HCSR041_PORT, &GPIO_InitStructure);     // 初始化GPIOA的ECHO引脚
    GPIO_ResetBits(HCSR041_PORT, HCSR041_ECHO);       // 将ECHO引脚置低
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   // 使能定时器4时钟
     
    TIM_DeInit(TIM2);                                 // 复位定时器2，确保配置干净
    TIM_TimeBaseStructure.TIM_Period = (1000-1);      // 设置计数器周期为999
    TIM_TimeBaseStructure.TIM_Prescaler = (72-1);      // 设置预分频器为71，得到1MHz的计数频率
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);     // 初始化定时器4的基本配置
        
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);           // 清除定时器4的更新标志位
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);      // 使能定时器4的更新中断
    hcsr04_NVIC();                                  // 配置定时器4的中断优先级和使能中断
    TIM_Cmd(TIM4, DISABLE);                         // 关闭定时器4     
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
   // 检查定时器4更新事件的中断标志位是否被设置
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
   {
       // 清除定时器4更新事件的中断挂起位
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
       
       // 增加msHcCount变量的值
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
float Hcsr041GetLength(void)
{
    u32 t = 0;                 // 定义并初始化计时器值变量t
    int i = 0;                 // 定义并初始化循环计数器i
    float lengthTemp1 = 0;     // 定义并初始化临时距离变量lengthTemp1
    float sum = 0;             // 定义并初始化距离总和变量sum

    while (i != 5)             // 循环执行5次
    {
        TRIG1_Send = 1;            // 设置TRIG引脚为高电平
        delay_us(20);              // 延时20微秒
        TRIG1_Send = 0;            // 设置TRIG引脚为低电平

        while (ECHO1_Reci == 0);   // 等待ECHO引脚的高电平信号
        
        OpenTimerForHc();          // 打开用于超声波测距的定时器
        i++;                       // 计数器加1，表示已完成一次测距
        
        while (ECHO1_Reci == 1);   // 等待ECHO引脚的低电平信号
        
        CloseTimerForHc();         // 关闭用于超声波测距的定时器
        t = GetEchoTimer();        // 获取定时器的计数值
        
        lengthTemp1 = ((float)t / 58.0);  // 将计数值转换为距离（单位：cm）
        sum = lengthTemp1 + sum;          // 将本次测距结果累加到总和上
    }

    lengthTemp1 = sum / 5.0;    // 计算平均距离
    return lengthTemp1;         // 返回平均距离值
}