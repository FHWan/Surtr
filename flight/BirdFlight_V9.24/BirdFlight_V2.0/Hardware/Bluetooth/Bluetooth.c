/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :Bluetooth.c
 * 描述   :蓝牙配置
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Bluetooth.h"

u8 bluetooth_bound[8]="AT+BAUD8";
u8 bluetooth_name[13]="AT+NAMExiluna";
u8 bluetooth_role[9]="AT+ROLE=S";

void Bluetooth_init()
{
	/*蓝牙第一次初始化有用，后面没用，因为波特率已经变成115200*/
//	Usart3toBluetooth_Init(9600);
//	Uart3_tx(bluetooth_name,sizeof(bluetooth_name));//配置蓝牙名字
//	delay_ms(2000);
//	Uart3_tx(bluetooth_bound,sizeof(bluetooth_bound));//配置蓝牙波特率
//	delay_ms(2000); 
	Usart3toBluetooth_Init(115200);
	delay_ms(2000); 	
}

