#include "./BSP/BEEPLED/gpio.h"

void BEEPLED_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
  
  //��ʼ����������Ӧ����GPIOE0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
  GPIO_ResetBits(GPIOE,GPIO_Pin_0);  //��������Ӧ����GPIOE0���ͣ�

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  //��ʼ����LED��Ӧ����GPIOB0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  //��ʼ����LED��Ӧ����GPIOB1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);

  do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0);   /* PA��ʱ��ʹ�� */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                  /* KEY0���� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                 /* �������� */
  GPIO_Init(GPIOA, &GPIO_InitStructure);               /* KEY0����ģʽ����,�������� */

}

u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //�����ɿ���־
    if(mode==1)key_up=1;    //֧������
    if(key_up&&(KEY0==0))
    {
        delay_ms(10);
        key_up=0;
        if(KEY0==0)       return KEY0_PRES;

    }else if(KEY0==1)key_up=1;
    return 0;   //�ް�������
}




