/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * ���� 	:Xiluna Tech
 * �ļ��� :Bluetooth.c
 * ����   :��������
 * ����   :http://xiluna.com/
 * ���ں� :XilunaTech
**********************************************************************************/
#include "Bluetooth.h"

u8 bluetooth_bound[8]="AT+BAUD8";
u8 bluetooth_name[13]="AT+NAMExiluna";
u8 bluetooth_role[9]="AT+ROLE=S";

void Bluetooth_init()
{
	/*������һ�γ�ʼ�����ã�����û�ã���Ϊ�������Ѿ����115200*/
//	Usart3toBluetooth_Init(9600);
//	Uart3_tx(bluetooth_name,sizeof(bluetooth_name));//������������
//	delay_ms(2000);
//	Uart3_tx(bluetooth_bound,sizeof(bluetooth_bound));//��������������
//	delay_ms(2000); 
	Usart3toBluetooth_Init(115200);
	delay_ms(2000); 	
}

