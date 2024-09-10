#include "./BSP/BEEPLED/gpio.h"

void BEEPLED_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能GPIOE时钟
  
  //初始化蜂鸣器对应引脚GPIOE0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  GPIO_ResetBits(GPIOE,GPIO_Pin_0);  //蜂鸣器对应引脚GPIOE0拉低，

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  //初始化白LED对应引脚GPIOB0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  //初始化红LED对应引脚GPIOB1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);

  do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0);   /* PA口时钟使能 */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                  /* KEY0引脚 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                 /* 下拉输入 */
  GPIO_Init(GPIOA, &GPIO_InitStructure);               /* KEY0引脚模式设置,下拉输入 */

}

u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
    if(key_up&&(KEY0==0))
    {
        delay_ms(10);
        key_up=0;
        if(KEY0==0)       return KEY0_PRES;

    }else if(KEY0==1)key_up=1;
    return 0;   //无按键按下
}




