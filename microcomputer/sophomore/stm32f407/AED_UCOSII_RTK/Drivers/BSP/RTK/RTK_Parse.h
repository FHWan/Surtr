#ifndef __RTK_Parse_H__
#define __RTK_Parse_H__

#include "main.h"
#include "string.h"
#include "sys.h"
#include "delay.h"

#define RMC_MAX_Len 80 // ����RMC���ݳ���
#define GGA_MAX_Len 80 // ����GGA���ݳ���
#define GSA_MAX_Len 70 // ����GSA���ݳ���
#define GSV_MAX_Len 70 // ����GSV���ݳ���
#define VTG_MAX_Len 50 // ����VTG���ݳ���
#define GLL_MAX_Len 50 // ����GLL���ݳ���
#define WTZ_MAX_Len 100 // ������̬���ݳ���


extern uint8_t RMC_Buffer[RMC_MAX_Len]; // RMC���ݻ���
extern uint8_t GGA_Buffer[GGA_MAX_Len]; // GGA���ݻ���
extern uint8_t GSA_Buffer[GSA_MAX_Len]; // GSA���ݻ���
extern uint8_t GSV_Buffer[GSV_MAX_Len]; // GSV���ݻ���
extern uint8_t VTG_Buffer[VTG_MAX_Len]; // VTG���ݻ���
extern uint8_t GLL_Buffer[GLL_MAX_Len]; // GLL���ݻ���
extern uint8_t WTZ_Buffer[WTZ_MAX_Len]; // WTZ���ݻ���

// ����RTK���ݳ���
#define UTC_MAX_Len 11    // UTCʱ�䳤��
#define Lat_MAX_Len 11    // γ�ȳ���
#define LatHemi_MAX_Len 2 // γ�Ȱ��򳤶�
#define Lon_MAX_Len 12    // ���ȳ���
#define LonHemi_MAX_Len 2 // ���Ȱ��򳤶�

// typedef struct
// {
//     char    UTCtime[UTC_MAX_Len];               // UTCʱ��
//     char    Latitude[Lat_MAX_Len];              // ԭʼγ��
//     char    LatitudeHemi[LatHemi_MAX_Len];      // γ�Ȱ���
//     double  Latitude;                           // γ��
//     char    Longitude[Lat_MAX_Len];             // ԭʼ����
//     char    LongitudeHemi[LatHemi_MAX_Len];     // ���Ȱ���
//     double  Longitude;                          // ����
// } rtk_data;

typedef struct
{
    char UTCtime[10] ;                   // UTCʱ��
    char GPS_sta[2];                    // ��λ״̬
    char latitude[10];                  // γ����Ϣ(�ȷ�)
    char latitudeHemi[2];               // γ�Ȱ���(N/S)
    char longitude[11];                 // ������Ϣ(�ȷ�)
    char longitudeHemi[2];              // ���Ȱ���(E/W)
    char speed[6];                      // ��������
    char course[6];                     // ���溽��
    char UTCdate[8];                    // UTC����
    char magneticVariation[6];          // ��ƫ��
    char magneticVariationDirection[2]; // ��ƫ�Ƿ���
    char modeIndication[2];             // ģʽָʾ
} _RMC_Typedef;


typedef struct
{
    char UTCtime[10];      // UTCʱ��
    char latitude[11];     // γ����Ϣ(�ȷ�)
    char latitudeHemi[1];  // γ�Ȱ���(N/S)
    char longitude[12];    // ������Ϣ(�ȷ�)
    char longitudeHemi[1]; // ���Ȱ���(E/W)
    char GPS_sta[1];       // ��λ״̬
    char satellites[2];    // ʹ����������
    char HDOP[4];          // HDOP
    char altitude[7];      // ���θ߶�
	char altitudeunit[1];     //���θ߶ȵ�λ
    char geoidHeight[7];   // ���ˮ׼��߶�
	char geoidHeightunit[1];// ���ˮ׼��߶ȵ�λ
    char DGPS_age[5];      // �����������
    char DGPS_ID[5];       // �������ID
} _GGA_Typedef;

typedef struct
{
    char mode[2];       // ģʽ
    char fixType[2];    // ��λ����
    char satellites[3]; // ʹ����������
    char PDOP[5];       // PDOP
    char HDOP[5];       // HDOP
    char VDOP[5];       // VDOP
} _GSA_Typedef;

typedef struct
{
    char totalMessages[3];    // ����Ϣ��
    char messageNumber[3];    // ��Ϣ���
    char satellitesInView[3]; // �ɼ���������
    char satelliteID[3];      // ���Ǳ��
    char elevation[3];        // ����
    char azimuth[3];          // ��λ��
    char SNR[3];              // �����
} _GSV_Typedef;

typedef struct
{
    char course[6];            // ���溽��
    char reference[2];         // �ο�
    char courseMagnetic[6];    // ���溽���ƫ��
    char referenceMagnetic[2]; // �ο���ƫ��
    char speedKnots[6];        // ��������(��)
    char referenceKnots[2];    // �ο�(��)
    char speedKm[6];           // ��������(����/Сʱ)
    char referenceKm[2];       // �ο�(����/Сʱ)
} _VTG_Typedef;

typedef struct
{
    char latitude[10];     // γ����Ϣ(�ȷ�)
    char latitudeHemi[2];  // γ�Ȱ���(N/S)
    char longitude[11];    // ������Ϣ(�ȷ�)
    char longitudeHemi[2]; // ���Ȱ���(E/W)
    char UTCtime[10];      // UTCʱ��
    char status[2];        // ��λ״̬
} _GLL_Typedef;

typedef struct
{
    char roll[8];       // �����
    char pitch[8];      // ������
    char yaw[8];        // ƫ����
    char RTK_status[2]; // RTK״̬
    char status_4G[2];  // 4G״̬
    char quality_4G[2]; // 4G�ź�����
} _WTZ_Typedef;

extern _GGA_Typedef GGA;
int count_commas(char *arr);                                     // ���㶺�Ÿ���
void Parse_UTCtime(char *utc_time, char *time);                  // ����UTCʱ��
void RMC_Parse_UTCtime(char *utc_time, char *time);
void Parase_UTCdate(char *utc_date, char *date);                 // ����UTC����
void RMC_Parase_UTCdate(char *utc_date, char *date);                
void Parse_latitude(char *latitude, char *lat, char *latHemi);   // ����γ��
void RMC_Parse_latitude(char *latitude, char *lat, char *latHemi);   // ����γ��
void Parse_longitude(char *longitude, char *lon, char *lonHemi); // ��������
void RMC_Parse_longitude(char *longitude, char *lon, char *lonHemi); 
void extract_RTK_Buffer(void);                                   // ��ȡRTK����
void Parase_RMC(void);                                           // ����RMC����
void Parase_GGA(void);                                           // ����GGA����
void Parase_GSA(void);                                           // ����GSA����
void Parase_GSV(void);                                           // ����GSV����
void Parase_VTG(void);                                           // ����VTG����
void Parase_GLL(void);                                           // ����GLL����
void Parase_WTZ(void);                                           // ����WTZ����
void Parase_RTK(void);                                           // ����RTK����

#endif
