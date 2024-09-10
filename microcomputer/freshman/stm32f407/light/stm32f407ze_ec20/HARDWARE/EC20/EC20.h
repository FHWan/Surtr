#ifndef __EC20_H_
#define __EC20_H_
#include "sys.h"
#include "delay.h"
#include "usart.h"



extern uint8_t temperature;      // �¶�
extern uint8_t humidity;         // ʪ��
extern float noise;              // ����
extern float pm;     			 // PM2.5
extern float Lux ;          	 //  ��ǿ
extern float UV;                 // ������ֵ
extern int UVindex;  			 //�����ߵȼ�
extern double latitude;          // γ��
extern double longitude;         // ����

#define UTC_Lendth 11  // UTCʱ�䳤��
#define lat_length 11  // γ�ȳ���
#define LatH_Length 2  // γ�Ȱ��򳤶�
#define lon_Length 12  // ���ȳ���
#define lonH_length 2  // ���Ȱ��򳤶�
#define sta_length 2   // GPS״̬����
#define Time_Lendth 12 // ʱ�䳤��

// GPRMC���������ݽṹ��
typedef struct
{
    char GPS_sta[sta_length];        // GPS״̬
    char UTCtime[UTC_Lendth];        // UTCʱ��
    char latitude[lat_length];       // γ��
    char latitudeHemi[LatH_Length];  // γ�Ȱ���
    char longitude[lon_Length];      // ����
    char longitudeHemi[lonH_length]; // ���Ȱ���
    double lat;                      // γ��
    double lon;                      // ����
    char Time[Time_Lendth];          // ʱ��
} _GPRMC_Typedef;


void Clear_Buffer(void);//��ջ���
void Mqtt_Senddata(void);
uint8_t EC20_init_check(uint8_t i);
void PARSE_GPRMC(void);     // ����GPRMC����
void GPS_Analysis(void);    // GPS���ݽ���
void EC20_4G_Reset(void);   // 4Gģ�鸴λ
void Parse_UTCTime(void);   // ����UTCʱ��
void Parse_gps_data(void);  // ����GPS����

#endif
