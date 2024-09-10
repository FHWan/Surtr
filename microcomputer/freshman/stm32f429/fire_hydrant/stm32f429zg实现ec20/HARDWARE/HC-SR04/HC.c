#include "sys.h"
#include "delay.h"

/*
VCC -> VCC
Trig -> PB6
Echo -> PA0
GND -> GND
*/
GPIO_InitTypeDef GPIO_Initure;
GPIO_InitTypeDef GPIO_InitStructure;
TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
TIM_IC_InitTypeDef  TIM3_CH4Config;    

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM3CH4_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM3CH4_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)

//定时器5初始化
void ultrasound_init()
{
    TIM3_Handler.Instance=TIM3;//定时器5
    TIM3_Handler.Init.Prescaler=90-1;//预分屏系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数
    TIM3_Handler.Init.Period=0xFFFFFFFF;//自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //时钟分频因子   
    HAL_TIM_IC_Init(&TIM3_Handler);
    
    TIM3_CH4Config.ICPolarity=TIM_ICPOLARITY_RISING;//上升沿捕获
    TIM3_CH4Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//映射到TI1上
    TIM3_CH4Config.ICPrescaler=TIM_ICPSC_DIV1;//配置输入分频，不分频
    TIM3_CH4Config.ICFilter=0;//配置输入滤波器，不滤波
    HAL_TIM_IC_ConfigChannel(&TIM3_Handler,&TIM3_CH4Config,TIM_CHANNEL_4);
    
    HAL_TIM_IC_Start_IT(&TIM3_Handler,TIM_CHANNEL_4);   //开启TIM5的捕获通道1，并且开启捕获中断
    __HAL_TIM_ENABLE_IT(&TIM3_Handler,TIM_IT_UPDATE);   //使能更新中断
}

float HC_Distance(void)
{
	int time=0;
	float Distance=0;
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);//打开PB6
    delay_us(20);//向PB6输入一个长为20us的高电平方波
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);//关闭PB6
	
	if(TIM3CH4_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
	{
		time=TIM3CH4_CAPTURE_STA&0X3F; 
		time*=0XFFFFFFFF;               //溢出时间总和
		time+=TIM3CH4_CAPTURE_VAL;      //得到总的高电平时间
		Distance=time*340/20000;
		TIM3CH4_CAPTURE_STA=0;          //开启下一次捕获
	}
	return Distance;
}

//定时器5回调函数
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
    {        
        __HAL_RCC_GPIOB_CLK_ENABLE();//使能GPIOA时钟
        __HAL_RCC_TIM3_CLK_ENABLE();//使能TIM5时钟
        
        GPIO_Initure.Pin=GPIO_PIN_1;//Pin1
        GPIO_Initure.Mode=GPIO_MODE_AF_PP;//复用推挽输出
        GPIO_Initure.Speed=GPIO_SPEED_HIGH;//高速
        GPIO_Initure.Pull=GPIO_PULLDOWN;//下拉
        GPIO_Initure.Alternate=GPIO_AF2_TIM3;//PA0 复用为 TIM5 通道 1
        HAL_GPIO_Init(GPIOB,&GPIO_Initure);
        
        HAL_NVIC_SetPriority(TIM3_IRQn,2,0); //设置中断优先级，抢占 2，子优先级 0
        HAL_NVIC_EnableIRQ(TIM3_IRQn); //开启 ITM5 中断通道
    }
    
	__HAL_RCC_GPIOG_CLK_ENABLE();  //使能PB时钟
    
    GPIO_InitStructure.Pin= GPIO_PIN_3;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLUP;//上拉
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//高速
    HAL_GPIO_Init(GPIOG,&GPIO_InitStructure);
}
//定时器5中断服务函数
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM3_Handler);//定时器共用处理函数
}
 

//定时器更新中断（计数溢出）中断处理回调函数， 该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//更新中断（溢出）发生时执行
{
	
	if((TIM3CH4_CAPTURE_STA&0X80)==0)//还未成功捕获
	{
			if(TIM3CH4_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH4_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH4_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM3CH4_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM3CH4_CAPTURE_STA++;
			}	 
	}		
}

//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	if((TIM3CH4_CAPTURE_STA&0X80)==0)//还未成功捕获
	{
		if(TIM3CH4_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
                TIM3CH4_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM3_Handler,TIM_CHANNEL_4);//获取当前的捕获值.
                TIM_RESET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4);   //一定要先清除原来的设置！！
                TIM_SET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH4_CAPTURE_STA=0;			//清空
				TIM3CH4_CAPTURE_VAL=0;
				TIM3CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				__HAL_TIM_DISABLE(&TIM3_Handler);        //关闭定时器5
				__HAL_TIM_SET_COUNTER(&TIM3_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4);   //一定要先清除原来的设置！！
				TIM_SET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);//定时器5通道1设置为下降沿捕获
				__HAL_TIM_ENABLE(&TIM3_Handler);//使能定时器5
			}		    
	}		
	
}

