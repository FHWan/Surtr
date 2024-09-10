#include "ec20.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"	
#include "led.h"
#include <stdio.h>
char *strx,*extstrx,*Readystrx;
char t_json[255];

void Clear_Buffer(void)//��ջ���
{
	u8 i;
	for(i=0;i<Rxcouter;i++)
	RxBuffer[i]=0;//����
	Rxcouter=0;

}
void  EC20_Init(void)
{
		printf("AT\r\n"); 
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
		while(strx==NULL)
		{
				Clear_Buffer();	
				printf("AT\r\n"); 
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
		}
		printf("AT+QGPS=1\r\n"); //��GNSS����
		delay_ms(500);
		printf("AT+QMTDISC=0\r\n");
		delay_ms(500);
		printf("ATE0\r\n"); //�رջ���
		delay_ms(500);
		Clear_Buffer();	
		printf("AT+CSQ\r\n"); //���CSQ
		delay_ms(500);
		printf("ATI\r\n"); //���ģ��İ汾��
		delay_ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//���SIM���Ƿ���λ
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//�鿴�Ƿ񷵻�ready
		while(strx==NULL)
		{
				Clear_Buffer();
				printf("AT+CPIN?\r\n");
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CPIN: READY");//���SIM���Ƿ���λ���ȴ�����λ�������ʶ�𲻵���ʣ��Ĺ�����û������
		}
		Clear_Buffer();	
		///////////////////////////////////
		printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//��������
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//��������������
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,1");//��������
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CREG: 0,5");//��������������
		}
		Clear_Buffer();
		/////////////////////////////////////
		printf("AT+CGREG?\r\n");//�鿴�Ƿ�ע��GPRS����
		delay_ms(500);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//��������Ҫ��ֻ��ע��ɹ����ſ��Խ���GPRS���ݴ��䡣
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//��������������
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer();
				printf("AT+CGREG?\r\n");//�鿴�Ƿ�ע��GPRS����
				delay_ms(500);
				strx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,1");//��������Ҫ��ֻ��ע��ɹ����ſ��Խ���GPRS���ݴ��䡣
				extstrx=strstr((const char*)RxBuffer,(const char*)"+CGREG: 0,5");//��������������
		}
		Clear_Buffer();
		printf("AT+COPS?\r\n");//�鿴ע�ᵽ�ĸ���Ӫ�̣�֧���ƶ� ��ͨ ���� 
		delay_ms(500);
		Clear_Buffer();
		
	delay_ms(500);
    Clear_Buffer();
    printf("AT+QICLOSE=0\r\n");//�ر�socket����
    delay_ms(500);
    Clear_Buffer();
    printf("AT+QICSGP=1,1,\"CMNET\",\"\",\"\",0\r\n");//����APN�����û���������
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//�����ɹ�
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");////�����ɹ�
    }
    Clear_Buffer();
    printf("AT+QIDEACT=1\r\n");//ȥ����
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//�����ɹ�
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//�����ɹ�
    }
    Clear_Buffer();
    printf("AT+QIACT=1\r\n");//����
    delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//�����ɹ�
  while(strx==NULL)
    {
        delay_ms(500);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//�����ɹ�
    }
    Clear_Buffer();
    printf("AT+QIACT?\r\n");//��ȡ��ǰ����IP��ַ
    delay_ms(500);
    Clear_Buffer();
	}	

///�����ַ�������
void EC20Send_StrData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISEND=0\r\n");
	delay_ms(100);
	printf(bufferdata);
  delay_ms(100);	
  USART_SendData(USART2, (u8) 0x1a);//������ɺ���
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer,(char*)"SEND OK");//�Ƿ���ȷ����
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer,(char*)"SEND OK");//�Ƿ���ȷ����
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer();
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//����ʣ���ֽ�����
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//����ʣ���ֽ�����
		strx=strstr((char*)strx,(char*)",");//��ȡ��һ��,
		strx=strstr((char*)(strx+1),(char*)",");//��ȡ�ڶ���,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer();
	// IWDG_Feed();//ι��
}

}


///����ʮ������
void EC20Send_HexData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISENDEX=0,\042%s\042\r\n",bufferdata);
	delay_ms(100);

  USART_SendData(USART2, (u8) 0x1a);//������ɺ���
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	delay_ms(100);
strx=strstr((char*)RxBuffer,(char*)"OK");//�Ƿ���ȷ����
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer,(char*)"OK");//�Ƿ���ȷ����
		delay_ms(10);
}
delay_ms(100);
Clear_Buffer();
printf("AT+QISEND=0,0\r\n");
delay_ms(200);
strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//����ʣ���ֽ�����
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  delay_ms(200);
		strx=strstr((char*)RxBuffer,(char*)"+QISEND:");//����ʣ���ֽ�����
		strx=strstr((char*)strx,(char*)",");//��ȡ��һ��,
		strx=strstr((char*)(strx+1),(char*)",");//��ȡ�ڶ���,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer();
	// IWDG_Feed();//ι��
}


}


///͸��ģʽ�½�������
void EC20Send_RecAccessMode(void)
{
	
		strx=strstr((const char*)RxBuffer,(const char*)"A1");//��LED0����
			if(strx)
			{		
				LED0=0;
				Clear_Buffer();
      }
		strx=strstr((const char*)RxBuffer,(const char*)"A0");//��LED0�ص�
			if(strx)
			{		
				LED0=1;
				Clear_Buffer();
      }
			strx=strstr((const char*)RxBuffer,(const char*)"B1");//��LED1����
			if(strx)
			{		
				LED1=0;
				Clear_Buffer();
      }
		strx=strstr((const char*)RxBuffer,(const char*)"B0");//��LED1�ص�
			if(strx)
			{		
				LED1=1;
				Clear_Buffer();
      }
	
			strx=strstr((const char*)RxBuffer,(const char*)"NO CARRIER");//�����������ر�
			 if(strx)
			 {
				 while(1)
				 {
					 //Uart1_SendStr("Server Is Closed!\r\n");//��֪�û����������ر�
         }
       }


}


void  MQTT_Init(void)	
{
    printf("AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n");//xΪ��ȥ�ķ�������ַ
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




