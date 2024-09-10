#include "ec20.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"	
#include <stdio.h>
#include "sys.h"
char *strx,*extstrx,*Readystrx;
extern u8 RxBuffer2[200],Rxcouter2;

void  EC20_Init(void)
{
		printf("AT\r\n"); 
		delay_ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"OK");//返回OK
		while(strx==NULL)
		{
				Clear_Buffer(2);
				printf("AT\r\n"); 
				delay_ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"OK");//返回OK
		}
		printf("AT+QGPS=1\r\n"); //对GNSS开机
		delay_ms(500);
		printf("AT+QMTDISC=0\r\n");
		delay_ms(500);
		printf("ATE0\r\n"); //关闭回显
		delay_ms(500);
		Clear_Buffer(2);
		printf("AT+CSQ\r\n"); //检查CSQ
		delay_ms(500);
		printf("ATI\r\n"); //检查模块的版本号
		delay_ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//检查SIM卡是否在位
		delay_ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CPIN: READY");//查看是否返回ready
		while(strx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CPIN?\r\n");
				delay_ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CPIN: READY");//检查SIM卡是否在位，等待卡在位，如果卡识别不到，剩余的工作就没法做了
		}
		Clear_Buffer(2);
		///////////////////////////////////
		printf("AT+CREG?\r\n");//查看是否注册GSM网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,1");//返回正常
		extstrx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CREG?\r\n");//查看是否注册GSM网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,1");//返回正常
				extstrx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer(2);
		/////////////////////////////////////
		printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
		extstrx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
				extstrx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer(2);
		printf("AT+COPS?\r\n");//查看注册到哪个运营商，支持移动 联通 电信 
		delay_ms(500);
		Clear_Buffer(2);
}
    	

///发送字符型数据
void EC20Send_StrData(char *bufferdata)
{
	u8 untildata=0xff;
	uint8_t data = 0x1a;
	printf("AT+QISEND=0\r\n");
	delay_ms(100);
	printf(bufferdata);
	delay_ms(100);	
	  
	HAL_UART_Transmit(&UART2_Handler, &data, sizeof(data), HAL_MAX_DELAY);
		while(__HAL_UART_GET_FLAG(&UART2_Handler, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer2,(char*)"SEND OK");//是否正确发送
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer2,(char*)"SEND OK");//是否正确发送
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer(2);
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//发送剩余字节数据
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//发送剩余字节数据
		strx=strstr((char*)strx,(char*)",");//获取第一个,
		strx=strstr((char*)(strx+1),(char*)",");//获取第二个,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer(2);
	// IWDG_Feed();//喂狗
}

}


///发送十六进制
void EC20Send_HexData(char *bufferdata)
{
	u8 untildata=0xff;
	uint8_t data = 0x1a;
	printf("AT+QISENDEX=0,\042%s\042\r\n",bufferdata);
	delay_ms(100);

	HAL_UART_Transmit(&UART2_Handler, &data, sizeof(data), HAL_MAX_DELAY);
		while(__HAL_UART_GET_FLAG(&UART2_Handler, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer2,(char*)"OK");//是否正确发送
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer2,(char*)"OK");//是否正确发送
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer(2);
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//发送剩余字节数据
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//发送剩余字节数据
		strx=strstr((char*)strx,(char*)",");//获取第一个,
		strx=strstr((char*)(strx+1),(char*)",");//获取第二个,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer(2);
	// IWDG_Feed();//喂狗
}


}


void  MQTT_Init(void)	
{
    printf("AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n");
    delay_ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"+QMTOPEN: 0,0");//看下返回状态
    while(strx==NULL)
    {
      strx=strstr((const char*)RxBuffer2,(const char*)"+QMTOPEN: 0,0");//确认返回值正确
    }
    Clear_Buffer(2);
   printf("AT+QMTCONN=0,\"Orienteering\",\"root\",\"xxxxxxxxxxxx\"\r\n");//去登录MQTT服务器，设备ID，账号和密码.用户根据实际需要进行更改
    delay_ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer2,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
    }
    Clear_Buffer(2);
   
}

u8 Mqtt_Savedata(u8 *t_payload,char *Card_ID, double lon,double lat,float pitch,float roll,float yaw,int temperature,int humidity,float WindSpeed,float HR,float SP02)
{
    char json[]="{\"DeviceID\":1001,\"card_id\":\"%s\",\"lon\":%lf,\"lat\":%lf,\"pitch\":%f,\"roll\":%f,\"yaw\":%f,\"temperature\":%d,\"humidity\":%d,\"WindSpeed\":%f,\"HR\":%f,\"SP02\":%f}";
	char t_json[255];
	int payload_len;
	unsigned short json_len;
	sprintf(t_json, json,Card_ID,lon,lat,pitch,roll,yaw,temperature,humidity,WindSpeed,HR,SP02);
	payload_len =  strlen(t_json)/sizeof(char);
	json_len = strlen(t_json)/sizeof(char);
	memcpy(t_payload, t_json, json_len);
	return json_len;
}

void Read_GPS(u8 *lat,u8 *lon)
{
    u8 t;
    u8 len;
    float mm;
    int flag;
    u8 j;
    u8 num=0;
    u8 ll_len;
    char shijian[17]=":";

    Clear_Buffer(2);
    printf("AT+QGPSGNMEA=\"GGA\"\r\n");//读取GPS北斗定位数据
    delay_ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"OK");//返回OK
      while(strx==NULL)
      {
       strx=strstr((const char*)RxBuffer2,(const char*)"OK");//返回OK
      }
          len=Rxcouter2&0x3fff;//得到此次接收到的数据长度
          if(len>55)
          {
              num=0;
              if(RxBuffer2[13]=='$'&&RxBuffer2[14]=='G'&&RxBuffer2[15]=='P'&&RxBuffer2[16]=='G'&&RxBuffer2[17]=='G'&&RxBuffer2[18]=='A')//报头
              {
                  for(t=0;t<len;t++)
                  {
                      if(num==2&&RxBuffer2[t]!=',')
                      lat[ll_len++]=RxBuffer2[t];
                      if(num==4&&RxBuffer2[t]!=',')
                      lon[ll_len++]=RxBuffer2[t];
                      if(num==1&&RxBuffer2[t]!=',')
                      shijian[ll_len++]=RxBuffer2[t];
                      if(RxBuffer2[t]==',')
                      {
                          num++;//记录，的个数
                          ll_len=1;
                      }
                  }
               for(t=0;t<17;t++)//重组
               {
                       if(lat[t]=='.')
                   {
                       lat[t]=lat[t-1];
                       lat[t-1]=lat[t-2];
                       lat[t-2]='.';
                       //补充部分  对GPS参数转化经纬度进行操作
                       mm = 10*(lat[t-1]-48)+lat[t]-48+0.1*(lat[t+1]-48)+0.01*(lat[t+2]-48)+0.001*(lat[t+3]-48)+0.0001*(lat[t+4]-48)+0.00001*(lat[t+5]-48);
                       mm = mm/60.0;
                       for(j=0;j<5;j++)
                       {
                          mm = 10.0*mm;
                          lat[t-1+j]=((int)mm)+48;
                          mm=mm+48-lat[t-1+j];
                       }
                       break;
                   }
               }
               for(t=0;t<17;t++)//重组
               {
                     lat[t]=lat[t+1];
               }

               for(t=0;t<17;t++)
               {
                   if(lon[t]=='.')
                   {
                       lon[t]=lon[t-1];
                       lon[t-1]=lon[t-2];
                       lon[t-2]='.';
                       //补充部分  对GPS参数转化经纬度进行操作
                       mm = 10*(lon[t-1]-48)+lon[t]-48+0.1*(lon[t+1]-48)+0.01*(lon[t+2]-48)+0.001*(lon[t+3]-48)+0.0001*(lon[t+4]-48)+0.00001*(lon[t+5]-48);
                       mm = mm/60.0;
                       for(j=0;j<5;j++)
                       {
                          mm = 10.0*mm;
                          lon[t-1+j]=((int)mm)+48;
                          mm=mm+48-lon[t-1+j];
                       }
                       break;
                   }
               }
               for(t=0;t<17;t++)//重组
               {
                     lon[t]=lon[t+1];
               }

               if(lat[1]!='0')
                  flag=1;
           }
          }
          else
              flag=0;
}

