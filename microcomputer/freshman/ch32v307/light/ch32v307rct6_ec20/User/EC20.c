#include "ec20.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
#include "debug.h"

char *strx,*extstrx,*Readystrx;
extern u8 RxBuffer2[200],Rxcouter2;

void  EC20_Init(void)
{
		printf("AT\r\n"); 
		Delay_Ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"OK");//����OK
		while(strx==NULL)
		{
				Clear_Buffer(2);
				printf("AT\r\n"); 
				Delay_Ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"OK");//����OK
		}
		printf("AT+QGPS=1\r\n"); //��GNSS����
		Delay_Ms(500);
		printf("AT+QMTDISC=0\r\n");
		Delay_Ms(500);
		printf("ATE0\r\n"); //�رջ���
		Delay_Ms(500);
		Clear_Buffer(2);
		printf("AT+CSQ\r\n"); //���CSQ
		Delay_Ms(500);
		printf("ATI\r\n"); //���ģ��İ汾��
		Delay_Ms(500);
		/////////////////////////////////
		printf("AT+CPIN?\r\n");//���SIM���Ƿ���λ
		Delay_Ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CPIN: READY");//�鿴�Ƿ񷵻�ready
		while(strx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CPIN?\r\n");
				Delay_Ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CPIN: READY");//���SIM���Ƿ���λ���ȴ�����λ�������ʶ�𲻵���ʣ��Ĺ�����û������
		}
		Clear_Buffer(2);
		///////////////////////////////////
		printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
		Delay_Ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,1");//��������
		extstrx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,5");//��������������
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CREG?\r\n");//�鿴�Ƿ�ע��GSM����
				Delay_Ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,1");//��������
				extstrx=strstr((const char*)RxBuffer2,(const char*)"+CREG: 0,5");//��������������
		}
		Clear_Buffer(2);
		/////////////////////////////////////
		printf("AT+CGREG?\r\n");//�鿴�Ƿ�ע��GPRS����
		Delay_Ms(500);
		strx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,1");//��������Ҫ��ֻ��ע��ɹ����ſ��Խ���GPRS���ݴ��䡣
		extstrx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,5");//��������������
		while(strx==NULL&&extstrx==NULL)
		{
				Clear_Buffer(2);
				printf("AT+CGREG?\r\n");//�鿴�Ƿ�ע��GPRS����
				Delay_Ms(500);
				strx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,1");//��������Ҫ��ֻ��ע��ɹ����ſ��Խ���GPRS���ݴ��䡣
				extstrx=strstr((const char*)RxBuffer2,(const char*)"+CGREG: 0,5");//��������������
		}
		Clear_Buffer(2);
		printf("AT+COPS?\r\n");//�鿴ע�ᵽ�ĸ���Ӫ�̣�֧���ƶ� ��ͨ ���� 
		Delay_Ms(500);
		Clear_Buffer(2);
}
    	

///�����ַ�������
void EC20Send_StrData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISEND=0\r\n");
	Delay_Ms(100);
	printf(bufferdata);
  Delay_Ms(100);	
  USART_SendData(USART2, (u8) 0x1a);//������ɺ���
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	Delay_Ms(100);
strx=strstr((char*)RxBuffer2,(char*)"SEND OK");//�Ƿ���ȷ����
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer2,(char*)"SEND OK");//�Ƿ���ȷ����
		Delay_Ms(10);
}
Delay_Ms(100);
Clear_Buffer(2);
printf("AT+QISEND=0,0\r\n");
Delay_Ms(200);
strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//����ʣ���ֽ�����
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  Delay_Ms(200);
		strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//����ʣ���ֽ�����
		strx=strstr((char*)strx,(char*)",");//��ȡ��һ��,
		strx=strstr((char*)(strx+1),(char*)",");//��ȡ�ڶ���,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer(2);
	// IWDG_Feed();//ι��
}

}


///����ʮ������
void EC20Send_HexData(char *bufferdata)
{
	u8 untildata=0xff;
	printf("AT+QISENDEX=0,\042%s\042\r\n",bufferdata);
	Delay_Ms(100);

  USART_SendData(USART2, (u8) 0x1a);//������ɺ���
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
	}
	Delay_Ms(100);
strx=strstr((char*)RxBuffer2,(char*)"OK");//�Ƿ���ȷ����
while(strx==NULL)
{
		strx=strstr((char*)RxBuffer2,(char*)"OK");//�Ƿ���ȷ����
		Delay_Ms(10);
}
Delay_Ms(100);
Clear_Buffer(2);
printf("AT+QISEND=0,0\r\n");
Delay_Ms(200);
strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//����ʣ���ֽ�����
while(untildata)
{
	  printf("AT+QISEND=0,0\r\n");
	  Delay_Ms(200);
		strx=strstr((char*)RxBuffer2,(char*)"+QISEND:");//����ʣ���ֽ�����
		strx=strstr((char*)strx,(char*)",");//��ȡ��һ��,
		strx=strstr((char*)(strx+1),(char*)",");//��ȡ�ڶ���,
	  untildata=*(strx+1)-0x30;
    Clear_Buffer(2);
	// IWDG_Feed();//ι��
}


}


void  MQTT_Init(void)	
{
    printf("AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n");
    Delay_Ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"+QMTOPEN: 0,0");//���·���״̬
    while(strx==NULL)
    {
      strx=strstr((const char*)RxBuffer2,(const char*)"+QMTOPEN: 0,0");//ȷ�Ϸ���ֵ��ȷ
    }
    Clear_Buffer(2);
   printf("AT+QMTCONN=0,\"light\",\"root\",\"xxxxxxxxxx\"\r\n");//ȥ��¼MQTT���������豸ID���˺ź�����.�û�����ʵ����Ҫ���и���
    Delay_Ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer2,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
    }
    Clear_Buffer(2);
   
}

u8 Mqtt_Savedata(u8 *t_payload,int uvconcentration,float noise,int temperature,int humidity,float pm,double lon,double lat,int water,int WaterLevel,int card)
{
    char json[]="{\"DeviceID\":20230806002,\"dename\":1001,\"uvconcentration\":%d,\"noise\":%f,\"temperature\":%d,\"humidity\":%d,\"pm\":%f,\"lon\":%lf,\"lat\":%lf,\"water\":%d,\"WaterLevel\":%d,\"card\":%d}";
        char t_json[255];
        int payload_len;
        unsigned short json_len;
        sprintf(t_json, json,uvconcentration,noise,temperature,humidity,pm,lon,lat,water,WaterLevel,card);
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
    printf("AT+QGPSGNMEA=\"GGA\"\r\n");//��ȡGPS������λ����
    Delay_Ms(500);
    strx=strstr((const char*)RxBuffer2,(const char*)"OK");//����OK
      while(strx==NULL)
      {
       strx=strstr((const char*)RxBuffer2,(const char*)"OK");//����OK
      }
          len=Rxcouter2&0x3fff;//�õ��˴ν��յ������ݳ���
          if(len>55)
          {
              num=0;
              if(RxBuffer2[14]=='$'&&RxBuffer2[15]=='G'&&RxBuffer2[16]=='N'&&RxBuffer2[17]=='G'&&RxBuffer2[18]=='G'&&RxBuffer2[19]=='A')//��ͷ
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
                          num++;//��¼���ĸ���
                          ll_len=1;
                      }
                  }
               for(t=0;t<17;t++)//����
               {
                       if(lat[t]=='.')
                   {
                       lat[t]=lat[t-1];
                       lat[t-1]=lat[t-2];
                       lat[t-2]='.';
                       //���䲿��  ��GPS����ת����γ�Ƚ��в���
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
               for(t=0;t<17;t++)//����
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
                       //���䲿��  ��GPS����ת����γ�Ƚ��в���
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
               for(t=0;t<17;t++)//����
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





