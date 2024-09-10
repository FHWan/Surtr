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
TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
TIM_IC_InitTypeDef  TIM3_CH4Config;    

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM3CH4_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM3CH4_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)

//��ʱ��5��ʼ��
void ultrasound_init()
{
    TIM3_Handler.Instance=TIM3;//��ʱ��5
    TIM3_Handler.Init.Prescaler=90-1;//Ԥ����ϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���
    TIM3_Handler.Init.Period=0xFFFFFFFF;//�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����   
    HAL_TIM_IC_Init(&TIM3_Handler);
    
    TIM3_CH4Config.ICPolarity=TIM_ICPOLARITY_RISING;//�����ز���
    TIM3_CH4Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM3_CH4Config.ICPrescaler=TIM_ICPSC_DIV1;//���������Ƶ������Ƶ
    TIM3_CH4Config.ICFilter=0;//���������˲��������˲�
    HAL_TIM_IC_ConfigChannel(&TIM3_Handler,&TIM3_CH4Config,TIM_CHANNEL_4);
    
    HAL_TIM_IC_Start_IT(&TIM3_Handler,TIM_CHANNEL_4);   //����TIM5�Ĳ���ͨ��1�����ҿ��������ж�
    __HAL_TIM_ENABLE_IT(&TIM3_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
}

float HC_Distance(void)
{
	int time=0;
	float Distance=0;
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);//��PB6
    delay_us(20);//��PB6����һ����Ϊ20us�ĸߵ�ƽ����
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);//�ر�PB6
	
	if(TIM3CH4_CAPTURE_STA&0X80)        //�ɹ�������һ�θߵ�ƽ
	{
		time=TIM3CH4_CAPTURE_STA&0X3F; 
		time*=0XFFFFFFFF;               //���ʱ���ܺ�
		time+=TIM3CH4_CAPTURE_VAL;      //�õ��ܵĸߵ�ƽʱ��
		Distance=time*340/20000;
		TIM3CH4_CAPTURE_STA=0;          //������һ�β���
	}
	return Distance;
}

//��ʱ��5�ص�����
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
    {        
        __HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��GPIOAʱ��
        __HAL_RCC_TIM3_CLK_ENABLE();//ʹ��TIM5ʱ��
        
        GPIO_Initure.Pin=GPIO_PIN_1;//Pin1
        GPIO_Initure.Mode=GPIO_MODE_AF_PP;//�����������
        GPIO_Initure.Speed=GPIO_SPEED_HIGH;//����
        GPIO_Initure.Pull=GPIO_PULLDOWN;//����
        GPIO_Initure.Alternate=GPIO_AF2_TIM3;//PA0 ����Ϊ TIM5 ͨ�� 1
        HAL_GPIO_Init(GPIOB,&GPIO_Initure);
        
        HAL_NVIC_SetPriority(TIM3_IRQn,2,0); //�����ж����ȼ�����ռ 2�������ȼ� 0
        HAL_NVIC_EnableIRQ(TIM3_IRQn); //���� ITM5 �ж�ͨ��
    }
    
	__HAL_RCC_GPIOG_CLK_ENABLE();  //ʹ��PBʱ��
    
    GPIO_InitStructure.Pin= GPIO_PIN_3;
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;//�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;//����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;//����
    HAL_GPIO_Init(GPIOG,&GPIO_InitStructure);
}
//��ʱ��5�жϷ�����
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM3_Handler);//��ʱ�����ô�����
}
 

//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
	
	if((TIM3CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
			if(TIM3CH4_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH4_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH4_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM3CH4_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM3CH4_CAPTURE_STA++;
			}	 
	}		
}

//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if((TIM3CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
		if(TIM3CH4_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                TIM3CH4_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM3_Handler,TIM_CHANNEL_4);//��ȡ��ǰ�Ĳ���ֵ.
                TIM_RESET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4);   //һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH4_CAPTURE_STA=0;			//���
				TIM3CH4_CAPTURE_VAL=0;
				TIM3CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
				__HAL_TIM_DISABLE(&TIM3_Handler);        //�رն�ʱ��5
				__HAL_TIM_SET_COUNTER(&TIM3_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4);   //һ��Ҫ�����ԭ�������ã���
				TIM_SET_CAPTUREPOLARITY(&TIM3_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
				__HAL_TIM_ENABLE(&TIM3_Handler);//ʹ�ܶ�ʱ��5
			}		    
	}		
	
}

