#ifndef __EC20_H_
#define __EC20_H_
#include "sys.h"
#include "delay.h"
#include "usart.h"



extern uint8_t temperature;      // 温度
extern uint8_t humidity;         // 湿度
extern float noise;              // 噪音
extern float pm;     			 // PM2.5
extern float Lux ;          	 //  光强
extern float UV;                 // 紫外线值
extern int UVindex;  			 //紫外线等级
extern double latitude;          // 纬度
extern double longitude;         // 经度

#define UTC_Lendth 11  // UTC时间长度
#define lat_length 11  // 纬度长度
#define LatH_Length 2  // 纬度半球长度
#define lon_Length 12  // 经度长度
#define lonH_length 2  // 经度半球长度
#define sta_length 2   // GPS状态长度
#define Time_Lendth 12 // 时间长度

// GPRMC解析后数据结构体
typedef struct
{
    char GPS_sta[sta_length];        // GPS状态
    char UTCtime[UTC_Lendth];        // UTC时间
    char latitude[lat_length];       // 纬度
    char latitudeHemi[LatH_Length];  // 纬度半球
    char longitude[lon_Length];      // 经度
    char longitudeHemi[lonH_length]; // 经度半球
    double lat;                      // 纬度
    double lon;                      // 经度
    char Time[Time_Lendth];          // 时间
} _GPRMC_Typedef;


void Clear_Buffer(void);//清空缓存
void Mqtt_Senddata(void);
uint8_t EC20_init_check(uint8_t i);
void PARSE_GPRMC(void);     // 解析GPRMC数据
void GPS_Analysis(void);    // GPS数据解析
void EC20_4G_Reset(void);   // 4G模块复位
void Parse_UTCTime(void);   // 解析UTC时间
void Parse_gps_data(void);  // 解析GPS数据

#endif
