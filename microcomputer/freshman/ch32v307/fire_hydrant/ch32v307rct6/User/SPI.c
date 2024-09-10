#include "SPI.h"
#include "debug.h"



/*******************************************************************************
* Function Name  : SPI2_Init
* Description    : Initializes the SPI peripheral.
* Input          : None
* Return         : None
*******************************************************************************/
void SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );//PORTA��Bʱ��ʹ��
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,  ENABLE );                       //SPI1ʱ��ʹ��

    // CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //�����趨������ʼ��PF0��PF1

    // SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // RST
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;                      //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                                                                   //����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                                                           //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                                                                     //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    // SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    // SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                                                                 //����ͬ��ʱ�ӵĵ�һ�������أ��½������ݱ�����
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                                                                        //����ͬ��ʱ�ӵĵڶ��������أ����������ݱ�����
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                                                                           //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    // RC522 SPIͨѶʱ��������СΪ100ns  ��Ƶ�����Ϊ10MHZ
    // RC522 �������½��ر仯
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;                    //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256����������36M/256=140.625KHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                                                      //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                                                            //CRCֵ����Ķ���ʽ
    SPI_Init(SPI2, &SPI_InitStructure);                                                                                     //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

    SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
}
