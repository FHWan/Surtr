#ifndef __RTK_Parse_H__
#define __RTK_Parse_H__

#include "main.h"
#include "string.h"
#include "sys.h"
#include "delay.h"

#define RMC_MAX_Len 80 // 定义RMC数据长度
#define GGA_MAX_Len 80 // 定义GGA数据长度
#define GSA_MAX_Len 70 // 定义GSA数据长度
#define GSV_MAX_Len 70 // 定义GSV数据长度
#define VTG_MAX_Len 50 // 定义VTG数据长度
#define GLL_MAX_Len 50 // 定义GLL数据长度
#define WTZ_MAX_Len 100 // 定义姿态数据长度


extern uint8_t RMC_Buffer[RMC_MAX_Len]; // RMC数据缓存
extern uint8_t GGA_Buffer[GGA_MAX_Len]; // GGA数据缓存
extern uint8_t GSA_Buffer[GSA_MAX_Len]; // GSA数据缓存
extern uint8_t GSV_Buffer[GSV_MAX_Len]; // GSV数据缓存
extern uint8_t VTG_Buffer[VTG_MAX_Len]; // VTG数据缓存
extern uint8_t GLL_Buffer[GLL_MAX_Len]; // GLL数据缓存
extern uint8_t WTZ_Buffer[WTZ_MAX_Len]; // WTZ数据缓存

// 定义RTK数据长度
#define UTC_MAX_Len 11    // UTC时间长度
#define Lat_MAX_Len 11    // 纬度长度
#define LatHemi_MAX_Len 2 // 纬度半球长度
#define Lon_MAX_Len 12    // 经度长度
#define LonHemi_MAX_Len 2 // 经度半球长度

// typedef struct
// {
//     char    UTCtime[UTC_MAX_Len];               // UTC时间
//     char    Latitude[Lat_MAX_Len];              // 原始纬度
//     char    LatitudeHemi[LatHemi_MAX_Len];      // 纬度半球
//     double  Latitude;                           // 纬度
//     char    Longitude[Lat_MAX_Len];             // 原始经度
//     char    LongitudeHemi[LatHemi_MAX_Len];     // 经度半球
//     double  Longitude;                          // 经度
// } rtk_data;

typedef struct
{
    char UTCtime[10] ;                   // UTC时间
    char GPS_sta[2];                    // 定位状态
    char latitude[10];                  // 纬度信息(度分)
    char latitudeHemi[2];               // 纬度半球(N/S)
    char longitude[11];                 // 经度信息(度分)
    char longitudeHemi[2];              // 经度半球(E/W)
    char speed[6];                      // 地面速率
    char course[6];                     // 地面航向
    char UTCdate[8];                    // UTC日期
    char magneticVariation[6];          // 磁偏角
    char magneticVariationDirection[2]; // 磁偏角方向
    char modeIndication[2];             // 模式指示
} _RMC_Typedef;


typedef struct
{
    char UTCtime[10];      // UTC时间
    char latitude[11];     // 纬度信息(度分)
    char latitudeHemi[1];  // 纬度半球(N/S)
    char longitude[12];    // 经度信息(度分)
    char longitudeHemi[1]; // 经度半球(E/W)
    char GPS_sta[1];       // 定位状态
    char satellites[2];    // 使用卫星数量
    char HDOP[4];          // HDOP
    char altitude[7];      // 海拔高度
	char altitudeunit[1];     //海拔高度单位
    char geoidHeight[7];   // 大地水准面高度
	char geoidHeightunit[1];// 大地水准面高度单位
    char DGPS_age[5];      // 差分数据年龄
    char DGPS_ID[5];       // 差分数据ID
} _GGA_Typedef;

typedef struct
{
    char mode[2];       // 模式
    char fixType[2];    // 定位类型
    char satellites[3]; // 使用卫星数量
    char PDOP[5];       // PDOP
    char HDOP[5];       // HDOP
    char VDOP[5];       // VDOP
} _GSA_Typedef;

typedef struct
{
    char totalMessages[3];    // 总消息数
    char messageNumber[3];    // 消息编号
    char satellitesInView[3]; // 可见卫星数量
    char satelliteID[3];      // 卫星编号
    char elevation[3];        // 仰角
    char azimuth[3];          // 方位角
    char SNR[3];              // 信噪比
} _GSV_Typedef;

typedef struct
{
    char course[6];            // 地面航向
    char reference[2];         // 参考
    char courseMagnetic[6];    // 地面航向磁偏角
    char referenceMagnetic[2]; // 参考磁偏角
    char speedKnots[6];        // 地面速率(节)
    char referenceKnots[2];    // 参考(节)
    char speedKm[6];           // 地面速率(公里/小时)
    char referenceKm[2];       // 参考(公里/小时)
} _VTG_Typedef;

typedef struct
{
    char latitude[10];     // 纬度信息(度分)
    char latitudeHemi[2];  // 纬度半球(N/S)
    char longitude[11];    // 经度信息(度分)
    char longitudeHemi[2]; // 经度半球(E/W)
    char UTCtime[10];      // UTC时间
    char status[2];        // 定位状态
} _GLL_Typedef;

typedef struct
{
    char roll[8];       // 横滚角
    char pitch[8];      // 俯仰角
    char yaw[8];        // 偏航角
    char RTK_status[2]; // RTK状态
    char status_4G[2];  // 4G状态
    char quality_4G[2]; // 4G信号质量
} _WTZ_Typedef;

extern _GGA_Typedef GGA;
int count_commas(char *arr);                                     // 计算逗号个数
void Parse_UTCtime(char *utc_time, char *time);                  // 解析UTC时间
void RMC_Parse_UTCtime(char *utc_time, char *time);
void Parase_UTCdate(char *utc_date, char *date);                 // 解析UTC日期
void RMC_Parase_UTCdate(char *utc_date, char *date);                
void Parse_latitude(char *latitude, char *lat, char *latHemi);   // 解析纬度
void RMC_Parse_latitude(char *latitude, char *lat, char *latHemi);   // 解析纬度
void Parse_longitude(char *longitude, char *lon, char *lonHemi); // 解析经度
void RMC_Parse_longitude(char *longitude, char *lon, char *lonHemi); 
void extract_RTK_Buffer(void);                                   // 提取RTK数据
void Parase_RMC(void);                                           // 解析RMC数据
void Parase_GGA(void);                                           // 解析GGA数据
void Parase_GSA(void);                                           // 解析GSA数据
void Parase_GSV(void);                                           // 解析GSV数据
void Parase_VTG(void);                                           // 解析VTG数据
void Parase_GLL(void);                                           // 解析GLL数据
void Parase_WTZ(void);                                           // 解析WTZ数据
void Parase_RTK(void);                                           // 解析RTK数据

#endif
