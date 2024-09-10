#include "ec20.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"	
#include "led.h"
#include <stdio.h>
char *strx,*extstrx,*Readystrx;
char t_json[255];

void Clear_Buffer(void)//清空缓存
{
	u8 i;
	for(i=0;i<Rxcouter;i++)
	RxBuffer[i]=0;//缓存
	Rxcouter=0;

}
void  EC20_Init(void)
{
		printf("AT\r\n"); 
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
		while(strx==NULL)
		{
				Clear_Buffer();	
				printf("AT\r\n"); 
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
		}
		printf("AT+QGPS=1\r\n"); //对GNSS开机
		delay_ms(500);
		printf("AT+QMTDISC=0\r\n");
		delay_ms(500);
		printf("ATE0\r\n"); //关闭回显
		delay_ms(500);
		Clear_Buffer();	
		printf("AT+CSQ\r\n"); //检查CSQ
		delay_ms(500);
		printf("ATI\r\n"); //检查模块的版本号
		delay_ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//检查SIM卡是否在位
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//查看是否返回ready
		while(strx==NULL)
		{
				Clear_Buffer();
				printf("AT+CPIN?\r\n");
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//检查SIM卡是否在位，等待卡在位，如果卡识别不到，剩余的工作就没法做了
		}
		Clear_Buffer();	
		///////////////////////////////////
		printf("AT+CREG?\r\n");//查看是否注册GSM网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//返回正常
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CREG?\r\n");//查看是否注册GSM网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//返回正常
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer();
		/////////////////////////////////////
		printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//返回正常，漫游
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CGREG?\r\n");//查看是否注册GPRS网络
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//返回正常，漫游
		}
		Clear_Buffer();
		printf("AT+COPS?\r\n");//查看注册到哪个运营商，支持移动 联通 电信 
		delay_ms(500);
		Clear_Buffer();
		
	delay_ms(500);
    Clear_Buffer();
    printf("AT+QICLOSE=0\r\n");//关闭socket连接
    delay_ms(500);
    Clear_Buffer();
    printf("AT+QICSGP=1,1,\"CMNET\",\"\",\"\",0\r\n");//接入APN，无用户名和密码
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//开启成功
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");////开启成功
    }
    Clear_Buffer();
    printf("AT+QIDEACT=1\r\n");//去激活
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//开启成功
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//开启成功
    }
    Clear_Buffer();
    printf("AT+QIACT=1\r\n");//激活
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//开启成功
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//开启成功
    }
    Clear_Buffer();
    printf("AT+QIACT?\r\n");//获取当前卡的IP地址
    delay_ms(500);
    Clear_Buffer();
	}	

///发送字符型数据
void EC20Send_StrData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISEND=0\r\n");
	delay_ms(100);
	printf(bufferdata);
  delay_ms(100);	
  USART_SendData(USART2, (u8) 0x1a);//发送完成函数
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer,(char*)"SEND OK");//是否正确发送
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer,(char*)"SEND OK");//是否正确发送
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer();
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
		strx=strstr((char*)strx,(char*)",");//获取第一个,
		strx=strstr((char*)(strx+1),(char*)",");//获取第二个,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer();
	// IWDG_Feed();//喂狗
}

}


///发送十六进制
void EC20Send_HexData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISENDEX=0,\042%s\042\r\n",bufferdata);
	delay_ms(100);

  USART_SendData(USART2, (u8) 0x1a);//发送完成函数
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer,(char*)"OK");//是否正确发送
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer,(char*)"OK");//是否正确发送
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer();
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//发送剩余字节数据
		strx=strstr((char*)strx,(char*)",");//获取第一个,
		strx=strstr((char*)(strx+1),(char*)",");//获取第二个,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer();
	// IWDG_Feed();//喂狗
}


}


///透传模式下接受数据
void EC20Send_RecAccessMode(void)
{
	
		strx=strstr((const char*)RxBuffer,(const char*)"A1");//对LED0开灯
			if(strx)
			{		
				LED0=0;
				Clear_Buffer();
      }
		strx=strstr((const char*)RxBuffer,(const char*)"A0");//对LED0关灯
			if(strx)
			{		
				LED0=1;
				Clear_Buffer();
      }
			strx=strstr((const char*)RxBuffer,(const char*)"B1");//对LED1开灯
			if(strx)
			{		
				LED1=0;
				Clear_Buffer();
      }
		strx=strstr((const char*)RxBuffer,(const char*)"B0");//对LED1关灯
			if(strx)
			{		
				LED1=1;
				Clear_Buffer();
      }
	
			strx=strstr((const char*)RxBuffer,(const char*)"NO CARRIER");//服务器主动关闭
			 if(strx)
			 {
				 while(1)
				 {
					 //Uart1_SendStr("Server Is Closed!\r\n");//告知用户服务器被关闭
         }
       }


}


void  MQTT_Init(void)	
{
    printf("AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n");//x为隐去的服务器地址
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//??????
    while(strx==NULL)
    {
      strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//???????
    }
    Clear_Buffer();
   printf("AT+QMTCONN=0,\"test_water\",\"root\",\"123456\"\r\n");//???MQTT???,??ID,?????.????????????
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//??????
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//??????
    }
    Clear_Buffer();
   
}

u8 Mqtt_Savedata(u8 *t_payload,char *Card_ID,float water_pressure,u8 *lon,u8 *lat,float pitch,float roll,float yaw ,float water_height)
{
	char json[]="{\"DeviceID\":2023,\"model_number\":\"SY49781\",\"manager\":\"XuBin\",\"card_id\":\"%s\",\"current_pressure\":%f,\"lon\":%s,\"lat\":%s,\"pitch\":%f,\"roll\":%f,\"yaw\":%f,\"water_height\":%f}";
		int payload_len;
		unsigned short json_len;
		sprintf(t_json, json,Card_ID,water_pressure,lon,lat,pitch,roll,yaw,water_height);
		payload_len =  strlen(t_json)/sizeof(char);
		json_len = strlen(t_json)/sizeof(char);
		memcpy(t_payload, t_json, json_len);
		return json_len;
}

void Read_GPS(u8 *lat,u8 *lon)
{
    u8 t;
    u8 len;
    double mm;
    int flag;
    u8 j;
    u8 num=0;
    u8 ll_len;
    char shijian[17]=":";

    Clear_Buffer();
    printf("AT+QGPSGNMEA=\"GGA\"\r\n");//??GPS??????
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//??OK
      while(strx==NULL)
      {
       strx=strstr((const char*)RxBuffer,(const char*)"OK");//??OK
      }
          len=Rxcouter&0x3fff;//????????????
          if(len>55)
          {
              num=0;
              if(RxBuffer[14]=='$'&&RxBuffer[15]=='G'&&RxBuffer[16]=='N'&&RxBuffer[17]=='G'&&RxBuffer[18]=='G'&&RxBuffer[19]=='A')//??
              {
                  for(t=0;t<len;t++)
                  {
                      if(num==2&&RxBuffer[t]!=',')
                      lat[ll_len++]=RxBuffer[t];
                      if(num==4&&RxBuffer[t]!=',')
                      lon[ll_len++]=RxBuffer[t];
                      if(num==1&&RxBuffer[t]!=',')
                      shijian[ll_len++]=RxBuffer[t];
                      if(RxBuffer[t]==',')
                      {
                          num++;//??,???
                          ll_len=1;
                      }
                  }
               for(t=0;t<17;t++)//??
               {
                       if(lat[t]=='.')
                   {
                       lat[t]=lat[t-1];
                       lat[t-1]=lat[t-2];
                       lat[t-2]='.';
                       //????  ?GPS???????????
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
               for(t=0;t<17;t++)//??
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
                       //????  ?GPS???????????
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
               for(t=0;t<17;t++)//??
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




