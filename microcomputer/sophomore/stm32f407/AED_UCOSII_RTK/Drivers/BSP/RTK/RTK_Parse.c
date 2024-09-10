#include "RTK_Parse.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

uint8_t RMC_Buffer[RMC_MAX_Len] = {0}; // RMC数据缓存
uint8_t GGA_Buffer[GGA_MAX_Len] = {0}; // GGA数据缓存
uint8_t GSA_Buffer[GSA_MAX_Len] = {0}; // GSA数据缓存
uint8_t GSV_Buffer[GSV_MAX_Len] = {0}; // GSV数据缓存
uint8_t VTG_Buffer[VTG_MAX_Len] = {0}; // VTG数据缓存
uint8_t GLL_Buffer[GLL_MAX_Len] = {0}; // GLL数据缓存
uint8_t WTZ_Buffer[WTZ_MAX_Len] = {0}; // WTZ数据缓存

uint8_t RMC_Flag = 0; //RMC标志位
uint8_t GGA_Flag = 0; //GGA标志位
uint8_t GSA_Flag = 0; //GSA标志位
uint8_t GSV_Flag = 0; //GSV标志位
uint8_t VTG_Flag = 0; //VTG标志位
uint8_t GLL_Flag = 0; //GLL标志位
uint8_t WTZ_Flag = 0; //WTZ标志位

_RMC_Typedef RMC; // RMC数据结构体
_GGA_Typedef GGA; // GGA数据结构体
_GSA_Typedef GSA; // GSA数据结构体
_GSV_Typedef GSV; // GSV数据结构体
_VTG_Typedef VTG; // VTG数据结构体
_GLL_Typedef GLL; // GLL数据结构体
_WTZ_Typedef WTZ; // WTZ数据结构体

/*****************************************************/
//  函数名：count_commas
//  描  述：计算字符串中逗号的个数
//  输  入：字符串
//  输  出：逗号的个数
/*****************************************************/
int count_commas(char *arr) // 计算字符串中逗号的个数
{
    int count = 0;                       // 逗号的个数
    for (int i = 0; arr[i] != '\0'; i++) // 遍历字符串
    {
        if (arr[i] == ',') // 判断是否为逗号
        {
            count++; // 逗号个数加1
        }
    }
    return count; // 返回逗号个数
}

/*****************************************************/
//  函数名：Parse_UTCTime
//  描  述：解析UTC时间
//  输  入：UTC时间、北京时间
//  输  出：无
/*****************************************************/
void Parse_UTCtime(char *utc_time, char *time)
{
    int hour, minute, second; // 时、分、秒
    int decimal;              // 小数部分
    // 分离出 HH、MM、SS 和 SS.SS 部分
    sscanf(utc_time, "%2d%2d%2d.%2d", &hour, &minute, &second, &decimal);
    // 转换北京时间
    hour += 8;
    // 计算时间
    sprintf(time, "%2d:%2d:%2d.%2d", hour, minute, second, decimal);
}

/*****************************************************/
//  函数名：RMC_Parse_UTCTime
//  描  述：解析UTC时间
//  输  入：UTC时间、北京时间
//  输  出：无
/*****************************************************/
void RMC_Parse_UTCtime(char *utc_time, char *time)
{
    int hour, minute, second; // 时、分、秒
    int decimal;              // 小数部分
    // 分离出 HH、MM、SS 和 SS.SS 部分
    sscanf(utc_time, "%2d%2d%2d.%2d", &hour, &minute, &second, &decimal);
    // 转换北京时间
    hour += 8;
    // 计算时间
    sprintf(time, "%2d:%2d:%2d.%2d", hour, minute, second, decimal);
}




/*****************************************************/
//  函数名：Parase_UTCdate
//  描  述：解析UTC日期
//  输  入：UTC日期、北京日期
//  输  出：无
/*****************************************************/
void Parase_UTCdate(char *utc_date, char *date)
{
    int year, month, day; // 年、月、日
    // 分离出 YY、MM、DD 部分
    sscanf(utc_date, "%2d%2d%2d", &year, &month, &day);
    // 计算日期
    sprintf(date, "%2d/%2d/%2d", year, month, day);
}
/*****************************************************/
//  函数名：RMC_Parase_UTCdate
//  描  述：解析UTC日期
//  输  入：UTC日期、北京日期
//  输  出：无
/*****************************************************/
void RMC_Parase_UTCdate(char *utc_date, char *date)
{
    int year, month, day; // 年、月、日
    // 分离出 YY、MM、DD 部分
    sscanf(utc_date, "%2d%2d%2d", &year, &month, &day);
    // 计算日期
    sprintf(date, "%2d/%2d/%2d", year, month, day);
}

/*****************************************************/
//  函数名：Parse_latitude
//  描  述：解析纬度
//  输  入: 纬度、纬度数据、纬度半球
//  输  出：无
/*****************************************************/
void Parse_latitude(char *latitude, char *lat, char *latHemi)
{
    int lat_d; // dd分量
    int lat_temp0, lat_temp1;
    double lati; // 纬度
    // 分离出 ddmm.mmmm 部分
    sscanf(latitude, "%2d%2d.%d", &lat_d, &lat_temp0, &lat_temp1);
    // 保留有效位数
    lati = (double)lat_d + (double)lat_temp0 / 60 + (double)((double)lat_temp1 / 600000);
    lati = floor(lati * 100000000 + 0.5) / 100000000;
	sprintf(lat, "%f ", lati); // 保存经度
//    sprintf(lat, "%f %s", lati, latHemi); // 保存纬度
}
/*****************************************************/
//  函数名：RMC_Parse_latitude
//  描  述：解析纬度
//  输  入: 纬度、纬度数据、纬度半球
//  输  出：无
/*****************************************************/
void RMC_Parse_latitude(char *latitude, char *lat, char *latHemi)
{
    int lat_d; // dd分量
    int lat_temp0, lat_temp1;
    double lati; // 纬度
    // 分离出 ddmm.mmmm 部分
    sscanf(latitude, "%2d%2d.%d", &lat_d, &lat_temp0, &lat_temp1);
    // 保留有效位数
    lati = (double)lat_d + (double)lat_temp0 / 60 + (double)((double)lat_temp1 / 600000);
    lati = floor(lati * 100000000 + 0.5) / 100000000;
    sprintf(lat, "%f %s", lati, latHemi); // 保存纬度
}

/*****************************************************/
//  函数名：Parse_longitude
//  描  述：解析经度
//  输  入：经度、经度数据、经度半球
//  输  出：无
/*****************************************************/
void Parse_longitude(char *longitude, char *lon, char *lonHemi)
{
    int lon_d; // dd分量
    int lon_temp0, lon_temp1;
    double loni;
    // 分离出 ddmm.mmmm 部分
    sscanf(longitude, "%3d%2d.%d", &lon_d, &lon_temp0, &lon_temp1);
    // 保留有效位数
    loni = (double)lon_d + (double)lon_temp0 / 60 + (double)((double)lon_temp1 / 600000);
    loni = floor(loni * 100000000 + 0.5) / 100000000;
	sprintf(lon, "%f ", loni); // 保存经度
//    sprintf(lon, "%f %s", loni, lonHemi); // 保存经度
}
/*****************************************************/
//  函数名：RMC_Parse_longitude
//  描  述：解析经度
//  输  入：经度、经度数据、经度半球
//  输  出：无
/*****************************************************/
void RMC_Parse_longitude(char *longitude, char *lon, char *lonHemi)
{
    int lon_d; // dd分量
    int lon_temp0, lon_temp1;
    double loni;
    // 分离出 ddmm.mmmm 部分
    sscanf(longitude, "%3d%2d.%d", &lon_d, &lon_temp0, &lon_temp1);
    // 保留有效位数
    loni = (double)lon_d + (double)lon_temp0 / 60 + (double)((double)lon_temp1 / 600000);
    loni = floor(loni * 100000000 + 0.5) / 100000000;
    sprintf(lon, "%f %s", loni, lonHemi); // 保存经度
}
/*****************************************************/
//  函数名：extract_RTK_Buffer
//  描  述：提取RTK数据 分别存入对应的缓存中待解析
//  输  入：无
//  输  出：无
/*****************************************************/
void extract_RTK_Buffer(void)
{
    char *mark = NULL;                           // 标记
    char sign1[] = "\r\n";                       // 标记符号
    mark = strtok((char *)RxBuffer3, sign1); // 以\r\n为标记提取字符串

	
    while (mark != NULL)
    {
//        printf1(">--RTK-->> %s\r\n", mark);      // 打印每次提取的字符串
        if (strstr(mark, "$GNRMC") != NULL)
        {
            strcpy((char *)RMC_Buffer, mark);    // 复制字符串
        }
        else if (strstr(mark, "$GNGGA") != NULL)
        {
            strcpy((char *)GGA_Buffer, mark);
        }
        else if (strstr(mark, "$GNGSA") != NULL)
        {
            strcpy((char *)GSA_Buffer, mark);
        }
        else if (strstr(mark, "$GPGSV") != NULL)
        {
            strcpy((char *)GSV_Buffer, mark);
        }
        else if (strstr(mark, "$GNVTG") != NULL)
        {
            strcpy((char *)VTG_Buffer, mark);
        }
        else if (strstr(mark, "$GNGLL") != NULL)
        {
            strcpy((char *)GLL_Buffer, mark);
        }
        else if (strstr(mark, "$WTRTK") != NULL)
        {
            strcpy((char *)WTZ_Buffer, mark);
        }
        mark = strtok(NULL, sign1); // 指向下一个子字符串 实现遍历
    }
}



/*****************************************************/
//  函数名：Parase_RMC
//  描  述: 解析RMC数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_RMC(void)
{
    // $ GPRMC，<1>，<2>，<3>，<4>，<5>，<6>，<7>，<8>，<9>，<10>，<11>，<12> * hh
    // <1> UTC时间，hhmmss（时分秒）格式
    // <2>定位状态，A =有效定位，V =无效定位
    // <3>纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
    // <4>纬度半球N（北半球）或S（南半球）
    // <5>经度dddmm.mmmm（度分）格式（前面的0也将被传输）
    // <6>经度半球E（东经）或W（西经）
    // <7>地面速率（000.0〜999.9节，前面的0也将被传输）
    // <8>地面航向（000.0〜359.9度，以真北为参考基准，前面的0也将被传输）
    // <9> UTC日期，ddmmyy（日月年）格式
    // <10>磁偏角（000.0〜180.0度，前面的0也将被传输）
    // <11>磁偏角方向，E（东）或W（西）
    // <12>模式指示（仅NMEA0183 3.00版本输出，A =自主定位，D =差分，E =投放，N =数据无效）
    char *subString;                           // 子字符串
    char *subStringNext;                       // 子字符串下一个
    char count = 0;                            // 计数
    if (count_commas((char *)RMC_Buffer) < 12) // 判断逗号个数是否小于13
    {
        memset(RMC_Buffer, 0, sizeof(RMC_Buffer));
		RMC_Flag = 0; //标志位置0
    }
	else
	{
		RMC_Flag = 1; //标志位置1
	}
	if(RMC_Flag == 1)
	{
		for (count = 0; count <= 12; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)RMC_Buffer, ","); // 查找逗号
	//			printf1("RMC_Buffer:%s \r\n",RMC_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memset(RMC.UTCtime, 0, sizeof(RMC.UTCtime));
						memcpy(RMC.UTCtime, subString, subStringNext - subString); // 获取UTC时间
						break;
					case 2:
						memset(RMC.GPS_sta, 0, sizeof(RMC.GPS_sta));
						memcpy(RMC.GPS_sta, subString, subStringNext - subString); // 获取定位状态，A=有效定位，V=无效定位
						break;
					case 3:
						memset(RMC.latitude, 0, sizeof(RMC.latitude));
						memcpy(RMC.latitude, subString, subStringNext - subString-1); // 获取纬度信息(度分)
						break;
					case 4:
						memset(RMC.latitudeHemi, 0, sizeof(RMC.latitudeHemi));
						memcpy(RMC.latitudeHemi, subString, subStringNext - subString); // 获取纬度半球(N/S)
						break;
					case 5:
						memset(RMC.longitude, 0, sizeof(RMC.longitude));
						memcpy(RMC.longitude, subString, subStringNext - subString-1); // 获取经度信息(度分)
						break;
					case 6:
						memset(RMC.longitudeHemi, 0, sizeof(RMC.longitudeHemi));
						memcpy(RMC.longitudeHemi, subString, subStringNext - subString); // 获取经度半球(E/W)
						break;
					case 7:
						memset(RMC.speed, 0, sizeof(RMC.speed));
						memcpy(RMC.speed, subString, subStringNext - subString); // 获取地面速率
						break;
					case 8:
						memset(RMC.course, 0, sizeof(RMC.course));
						memcpy(RMC.course, subString, subStringNext - subString); // 获取地面航向
						break;
					case 9:
						memset(RMC.UTCdate, 0, sizeof(RMC.UTCdate));
						memcpy(RMC.UTCdate, subString, subStringNext - subString); // 获取UTC日期
						break;
					case 10:
						memset(RMC.magneticVariation, 0, sizeof(RMC.magneticVariation));
						memcpy(RMC.magneticVariation, subString, subStringNext - subString); // 获取磁偏角
						break;
					case 11:
						memset(RMC.magneticVariationDirection ,0, sizeof(RMC.magneticVariationDirection));
						memcpy(RMC.magneticVariationDirection, subString, subStringNext - subString); // 获取磁偏角方向
						break;
					case 12:
						memset(RMC.modeIndication, 0, sizeof(RMC.modeIndication));
						memcpy(RMC.modeIndication, subString, subStringNext - subString); // 获取模式指示
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		// 解析UTC时间
		RMC_Parse_UTCtime(RMC.UTCtime, RMC.UTCtime);
		// 解析UTC日期
		RMC_Parase_UTCdate(RMC.UTCdate, RMC.UTCdate);
		// 解析纬度
		RMC_Parse_latitude(RMC.latitude, RMC.latitude, RMC.latitudeHemi);
		// 解析经度
		RMC_Parse_longitude(RMC.longitude, RMC.longitude, RMC.longitudeHemi);
			
		RMC_Flag = 0; //标志位置0
//		printf1("RMC:%s,%s\r\n",RMC.longitude,RMC.latitude);
	//	printf1("Time:%s\r\n", RMC.UTCtime); // 打印UTC时间
	}
    
}


_GGA_Typedef GGA2;

/*****************************************************/
//  函数名：Parase_GGA
//  描  述: 解析GGA数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_GGA(void)
{
    // $ GPGGA，<1>，<2>，<3>，<4>，<5>，<6>，<7>，<8>，<9>，M，<10>，M，<11> ，<12> * hh
    // <1> UTC时间，hhmmss（时分秒）格式
    // <2>纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
    // <3>纬度半球N（北半球）或S（南半球）
    // <4>经度dddmm.mmmm（度分）格式（前面的0也将被传输）
    // <5>经度半球E（东经）或W（西经）
    // <6> GPS状态：0 =未定位，1 =非差分定位，2 =差分定位，6 =正在采样
    // <7>正在使用解算位置的卫星数量（00〜12）（前面的0也将被传输）
    // <8> HDOP水平精度因子（0.5〜99.9）
    // <9>海拔高度（-9999.9〜99999.9）
    // <10>地球沥青球面相对大地水准面的高度
    // <11>差分时间（从最近一次接收到差分信号开始的秒数，如果不是差分定位将为空）
    // <12>差分站ID号0000〜1023（前面的0也将被传输，如果不是差分定位将为空）
    char *subString;                           // 子字符串
    char *subStringNext;                       // 子字符串下一个
    char count = 0;                            // 计数
    if (count_commas((char *)GGA_Buffer) != 14) // 判断逗号个数是否小于12
    {
        memset(GGA_Buffer,0, sizeof(GGA_Buffer));
		GGA_Flag = 0; //标志位置0
		
    }
	else 
	{
		GGA_Flag = 1; //标志位置1
	}
		if(GGA_Flag == 1)
	{	
			 for (count = 0; count <= 14; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)GGA_Buffer, ","); // 查找逗号
	//			printf1("GGA_Buffer:%s\r\n",GGA_Buffer);
				
			
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memset(GGA.UTCtime, 0, sizeof(GGA.UTCtime));
						memcpy(GGA.UTCtime, subString, subStringNext - subString); // 获取UTC时间
						break;
					case 2:
						memset(GGA.latitude, 0, sizeof(GGA.latitude));
						memcpy(GGA.latitude, subString, subStringNext - subString); // 获取纬度信息(度分)
						break;
					case 3:
						memset(GGA.latitudeHemi, 0, sizeof(GGA.latitudeHemi));
						memcpy(GGA.latitudeHemi, subString, subStringNext - subString); // 获取纬度半球(N/S)
						break;
					case 4:
						memset(GGA.longitude, 0, sizeof(GGA.longitude));
						memcpy(GGA.longitude, subString, subStringNext - subString); // 获取经度信息(度分)
						break;
					case 5:
						memset(GGA.longitudeHemi, 0, sizeof(GGA.longitudeHemi));
						memcpy(GGA.longitudeHemi, subString, subStringNext - subString); // 获取经度半球(E/W)
						break;
					case 6:
						memset(GGA.GPS_sta, 0, sizeof(GGA.GPS_sta));
						memcpy(GGA.GPS_sta, subString, subStringNext - subString); // 获取GPS状态
						break;
					case 7:
						memset(GGA.satellites, 0, sizeof(GGA.satellites));
						memcpy(GGA.satellites, subString, subStringNext - subString); // 获取正在使用解算位置的卫星数量
						break;
					case 8:
						memset(GGA.HDOP, 0, sizeof(GGA.HDOP));
						memcpy(GGA.HDOP, subString, subStringNext - subString); // 获取HDOP水平精度因子
						break;
					case 9:
						memset(GGA.altitude, 0, sizeof(GGA.altitude));
						memcpy(GGA.altitude, subString, subStringNext - subString); // 获取海拔高度
						break;
					 case 10:
						memset(GGA.altitudeunit, 0, sizeof(GGA.altitudeunit));
						memcpy(GGA.altitudeunit, subString, subStringNext - subString); // 获取海拔高度单位
						break;
					case 11:
						memset(GGA.geoidHeight, 0, sizeof(GGA.geoidHeight));
						memcpy(GGA.geoidHeight, subString, subStringNext - subString); // 获取地球沥青球面相对大地水准面的高度
						break;
					case 12:
						memset(GGA.geoidHeightunit, 0, sizeof(GGA.geoidHeightunit));
						memcpy(GGA.geoidHeightunit, subString, subStringNext - subString); // 获取地球沥青球面相对大地水准面的高度单位
						break;
					case 13:
						memset(GGA.DGPS_age, 0, sizeof(GGA.DGPS_age));
						memcpy(GGA.DGPS_age, subString, subStringNext - subString); // 获取差分时间
						break;
					case 14:
						memset(GGA.DGPS_ID, 0, sizeof(GGA.DGPS_ID));
						memcpy(GGA.DGPS_ID, subString, subStringNext - subString); // 获取差分站ID号
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
	//	printf1("GGA:%s, %s\r\n",GGA.longitude,GGA.latitude);

		GGA2 = GGA;
		// 解析UTC时间
		Parse_UTCtime(GGA.UTCtime, GGA2.UTCtime);
		// 解析纬度
		Parse_latitude(GGA.latitude, GGA2.latitude, GGA.latitudeHemi);
		// 解析经度
		Parse_longitude(GGA.longitude, GGA2.longitude, GGA.longitudeHemi);

		GGA_Flag = 0; //标志位置0
	}
   
	
//	printf1("GGA:%s\r\n",GGA2.UTCtime);
//	printf1("GGA:%s, %s\r\n",GGA2.longitude,GGA2.latitude);
//	printf1("GGA:%s, %s\r\n",GGA2.longitudeHemi,GGA2.latitudeHemi);
}



/*****************************************************/
//  函数名：Parase_GSA
//  描  述: 解析GSA数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_GSA(void)
{
    // $ GPGSA，<1>，<2>，<3>，<4> 、、、、、 <12>，<13>，<14>，<15>，<16>，<17>，<18>
    // <1>模式：M =手动，A =自动。
    // <2>定位型式1 =未定位，2 =二维定位，3 =三维定位。
    // <3>到<14> PRN数字：01至32表天空使用中的卫星编号，最多可接收12颗卫星信息
    // <15> PDOP位置精度因子（0.5〜99.9）
    // <16> HDOP水平精度因子（0.5〜99.9）
    // <17> VDOP垂直精度因子（0.5〜99.9）
    // <18>校验和
    char *subString;                           // 子字符串
    char *subStringNext;                       // 子字符串下一个
    char count = 0;                            // 计数
    if (count_commas((char *)GSA_Buffer) != 18) // 判断逗号个数是否小于18
    {
        memset(GSA_Buffer, 0, sizeof(GSA_Buffer));
		GSA_Flag = 0; //标志位置0
		
    }
	else 
	{
		GSA_Flag = 1; //标志位置1
	}
	if(GSA_Flag == 1)
	{
			 for (count = 0; count <= 18; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)GSA_Buffer, ","); // 查找逗号
//				printf1("GSA_Buffer:%s\r\n",GSA_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memcpy(GSA.mode, subString, subStringNext - subString); // 获取模式
						break;
					case 2:
						memcpy(GSA.fixType, subString, subStringNext - subString); // 获取定位类型
						break;
					case 3:
						memcpy(GSA.satellites, subString, subStringNext - subString); // 获取使用卫星数量
						break;
					case 15:
						memcpy(GSA.PDOP, subString, subStringNext - subString); // 获取PDOP
						break;
					case 16:
						memcpy(GSA.HDOP, subString, subStringNext - subString); // 获取HDOP
						break;
					case 17:
						memcpy(GSA.VDOP, subString, subStringNext - subString); // 获取VDOP
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		GSA_Flag = 0;//标志位置0
	}
   
}


/*****************************************************/
//  函数名：Parase_GSV
//  描  述: 解析GSV数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_GSV(void)
{
    // $ GPGSV，<1>，<2>，<3>，<4>，<5>，<6>，<7>，？<4>，<5>，<6>，<7>，<8 >
    // <1> GSV语句的总数
    // <2>本句GSV的编号
    // <3>可见卫星的总数，00至12。
    // <4>卫星编号，01至32。
    // <5>卫星仰角，00至90度。
    // <6>卫星方位角，000至359度。实际值。
    // <7>讯号噪声比（C / No），00至99 dB；无表未接收到讯号。
    // <8>校验和
    char *subString;                          // 子字符串
    char *subStringNext;                      // 子字符串下一个
    char count = 0;                           // 计数
    if (count_commas((char *)GSV_Buffer) < 8) // 判断逗号个数是否小于8
    {
        memset(GSV_Buffer, 0, sizeof(GSV_Buffer));
		GSV_Flag = 0; //标志位置0
    }
	else 
	{
		GSV_Flag = 1; //标志位置1
	}
	if(GSV_Flag == 1)
	{
			for (count = 0; count <= 3; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)GSV_Buffer, ","); // 查找逗号
//				printf1("GSV_Buffer:%s\r\n",GSV_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memcpy(GSV.totalMessages, subString, subStringNext - subString); // 获取总消息数
						break;
					case 2:
						memcpy(GSV.messageNumber, subString, subStringNext - subString); // 获取消息编号
						break;
					case 3:
						memcpy(GSV.satellitesInView, subString, subStringNext - subString); // 获取可见卫星数量
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		GSV_Flag = 0; //标志位置0
	}
    
}



/*****************************************************/
//  函数名：Parase_VTG
//  描  述: 解析VTG数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_VTG(void)
{
    // $ GPVTG，<1>，T，<2>，M，<3>，N，<4>，K，<5> * hh
    // 字段0：$GPVTG，语句ID，表明该语句为Track Made Good and Ground Speed（VTG）地面速度信息
    // 字段1：运动角度，000 - 359，（前导位数不足则补0）
    // 字段2：T=真北参照系
    // 字段3：运动角度，000 - 359，（前导位数不足则补0）
    // 字段4：M=磁北参照系
    // 字段5：水平运动速度（0.00）（前导位数不足则补0）
    // 字段6：N=节，Knots
    // 字段7：水平运动速度（0.00）（前导位数不足则补0）
    // 字段8：K=公里/时，km/h
    // 字段9：校验值（$与*之间的数异或后的值）
    char *subString;                          // 子字符串
    char *subStringNext;                      // 子字符串下一个
    char count = 0;                           // 计数
    if (count_commas((char *)VTG_Buffer) < 9) // 判断逗号个数是否小于9
    {
        memset(VTG_Buffer, 0, sizeof(VTG_Buffer));
		VTG_Flag = 0; //标志位置0
    }
	else 
	{
		VTG_Flag = 1; //标志位置1
	}
	if(VTG_Flag == 1)
	{
			 for (count = 0; count <= 9; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)VTG_Buffer, ","); // 查找逗号
//				printf1("VTG_Buffer:%s\r\n",VTG_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memcpy(VTG.course, subString, subStringNext - subString); // 获取地面航向
						break;
					case 2:
						memcpy(VTG.reference, subString, subStringNext - subString); // 获取参考
						break;
					case 3:
						memcpy(VTG.courseMagnetic, subString, subStringNext - subString); // 获取地面航向磁偏角
						break;
					case 4:
						memcpy(VTG.referenceMagnetic, subString, subStringNext - subString); // 获取参考磁偏角
						break;
					case 5:
						memcpy(VTG.speedKnots, subString, subStringNext - subString); // 获取地面速率(节)
						break;
					case 6:
						memcpy(VTG.referenceKnots, subString, subStringNext - subString); // 获取参考(节)
						break;
					case 7:
						memcpy(VTG.speedKm, subString, subStringNext - subString); // 获取地面速率(公里/小时)
						break;
					case 8:
						memcpy(VTG.referenceKm, subString, subStringNext - subString); // 获取参考(公里/小时)
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		VTG_Flag = 0; //标志位置0
	}
   
}



/*****************************************************/
//  函数名：Parase_GLL
//  描  述: 解析GLL数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_GLL(void)
{
    // $GPGLL,<1>,<2>,<3>,<4>,<5>,<6>*2D
    // 字段0：$GPGLL，语句ID，表明该语句为Geographic Position（GLL）地理定位信息
    // 字段1：纬度ddmm.mmmm，度分格式（前导位数不足则补0）
    // 字段2：纬度N（北纬）或S（南纬）
    // 字段3：经度dddmm.mmmm，度分格式（前导位数不足则补0）
    // 字段4：经度E（东经）或W（西经）
    // 字段5：UTC时间，hhmmss.sss格式
    // 字段6：状态，A=定位，V=未定位
    // 字段7：校验值（$与*之间的数异或后的值）
    char *subString;                          // 子字符串
    char *subStringNext;                      // 子字符串下一个
    char count = 0;                           // 计数
    if (count_commas((char *)GLL_Buffer) != 7) // 判断逗号个数是否小于7
    {
        memset(GLL_Buffer, 0, sizeof(GLL_Buffer));
		GLL_Flag = 0; //标志位置0
    }
	else
	{
		GLL_Flag = 1; //标志位置1
	}
		if(GLL_Flag == 1)
	{
			 for (count = 0; count <= 7; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)GLL_Buffer, ","); // 查找逗号
	//			printf1("GLL_Buffer:%s\r\n",GLL_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 1:
						memcpy(GLL.latitude, subString, subStringNext - subString); // 获取纬度信息(度分)
						break;
					case 2:
						memcpy(GLL.latitudeHemi, subString, subStringNext - subString); // 获取纬度半球(N/S)
						break;
					case 3:
						memcpy(GLL.longitude, subString, subStringNext - subString); // 获取经度信息(度分)
						break;
					case 4:
						memcpy(GLL.longitudeHemi, subString, subStringNext - subString); // 获取经度半球(E/W)
						break;
					case 5:
						memcpy(GLL.UTCtime, subString, subStringNext - subString); // 获取UTC时间
						break;
					case 6:
						memcpy(GLL.status, subString, subStringNext - subString); // 获取状态
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}

			// 解析UTC时间
		Parse_UTCtime(GLL.UTCtime, GLL.UTCtime);
		// 解析纬度
		Parse_latitude(GLL.latitude, GLL.latitude, GLL.latitudeHemi);
		// 解析经度
		Parse_longitude(GLL.longitude, GLL.longitude, GLL.longitudeHemi);
		GLL_Flag = 0; //标志位置0
	
	}
   
	
//	printf1("GLL:%s, %s\r\n",GLL.longitude,GLL.latitude);
}


/*****************************************************/
//  函数名：Parase_WTZ
//  描  述: 解析RTK姿态传感器数据
//  输  入：无
//  输  出：无
/*****************************************************/

void Parase_WTZ(void)
{
    // $WTRTK,0.00,0.00,0.00,0.00,-9.25,-1.28,0.00,0,19,0,5
    // 数据        说明
    // $WTRTK      包头
    // 0.00        差分X距离（单位：米）
    // 0.00        差分Y距离（单位：米）
    // 0.00        差分Z距离（单位：米）
    // 0.00        差分R距离（单位：米）
    // -9.25       俯仰角
    // -1.28       横滚角
    // 0.00        航向角
    // 0           移动站RTK状态    0表示初始化，1表示单点定位，2表示码差分，4表示固定解，5表示浮点解
    // 19          4G状态           0~13：设置参数 14~20：连接中   21：连接完成
    // 0           固定基站状态     -1表示选择固定基站失败 0表示选择无固定基站选择 1表示选择固定基站成功
    // CSQ         4G信号质量
    // 5           Ntrip状态        5:连接成功  其他：连接中
    char *subString;                           // 子字符串
    char *subStringNext;                       // 子字符串下一个
    char count = 0;                            // 计数
    if (count_commas((char *)WTZ_Buffer) < 10 ) // 判断逗号个数是否等于10
    {
        memset(WTZ_Buffer, 0, sizeof(WTZ_Buffer));
		WTZ_Flag = 0; //标志位置0
    }
	else
	{
		WTZ_Flag = 1; //标志位置1
	}
	if(WTZ_Flag == 1)
	{
			  for (count = 0; count <= 12; count++) // 获取全段数据
		{
			if (count == 0)
			{
				subString = strstr((const char *)WTZ_Buffer, ","); // 查找逗号
//				printf1("WTZ_Buffer:%s\r\n",WTZ_Buffer);
			}
			else
			{
				subString++;                                          // 偏移到逗号后面
				if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
				{
					switch (count)
					{
					case 5:
						memcpy(WTZ.roll, subString, subStringNext - subString); // 获取俯仰角
						break;
					case 6:
						memcpy(WTZ.pitch, subString, subStringNext - subString); // 获取横滚角
						break;
					case 7:
						memcpy(WTZ.yaw, subString, subStringNext - subString); // 获取航向角
						break;
					case 8:
						memcpy(WTZ.RTK_status, subString, subStringNext - subString); // 获取移动站RTK状态
						break;
					case 9:
						memcpy(WTZ.status_4G, subString, subStringNext - subString); // 获取4G状态
						break;
					case 10:
						memcpy(WTZ.quality_4G, subString, subStringNext - subString); // 获取固定基站状态
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		WTZ_Flag = 0; //标志位置1
	}
  

}


/*****************************************************/
//  函数名：Parase_RTK  主函数
//  描  述: 解析RTK数据
//  输  入：无
//  输  出：无
/*****************************************************/
void Parase_RTK(void)
{
    extract_RTK_Buffer(); // 提取RTK数据
    Parase_RMC();         // 解析RMC数据
    Parase_GGA();         // 解析GGA数据
    Parase_GSA();         // 解析GSA数据
    Parase_GSV();         // 解析GSV数据
    Parase_VTG();         // 解析VTG数据
    Parase_GLL();         // 解析GLL数据
    Parase_WTZ();         // 解析RTK姿态传感器数据
}
