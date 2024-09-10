#include "RTK_Parse.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

uint8_t RMC_Buffer[RMC_MAX_Len] = {0}; // RMC���ݻ���
uint8_t GGA_Buffer[GGA_MAX_Len] = {0}; // GGA���ݻ���
uint8_t GSA_Buffer[GSA_MAX_Len] = {0}; // GSA���ݻ���
uint8_t GSV_Buffer[GSV_MAX_Len] = {0}; // GSV���ݻ���
uint8_t VTG_Buffer[VTG_MAX_Len] = {0}; // VTG���ݻ���
uint8_t GLL_Buffer[GLL_MAX_Len] = {0}; // GLL���ݻ���
uint8_t WTZ_Buffer[WTZ_MAX_Len] = {0}; // WTZ���ݻ���

uint8_t RMC_Flag = 0; //RMC��־λ
uint8_t GGA_Flag = 0; //GGA��־λ
uint8_t GSA_Flag = 0; //GSA��־λ
uint8_t GSV_Flag = 0; //GSV��־λ
uint8_t VTG_Flag = 0; //VTG��־λ
uint8_t GLL_Flag = 0; //GLL��־λ
uint8_t WTZ_Flag = 0; //WTZ��־λ

_RMC_Typedef RMC; // RMC���ݽṹ��
_GGA_Typedef GGA; // GGA���ݽṹ��
_GSA_Typedef GSA; // GSA���ݽṹ��
_GSV_Typedef GSV; // GSV���ݽṹ��
_VTG_Typedef VTG; // VTG���ݽṹ��
_GLL_Typedef GLL; // GLL���ݽṹ��
_WTZ_Typedef WTZ; // WTZ���ݽṹ��

/*****************************************************/
//  ��������count_commas
//  ��  ���������ַ����ж��ŵĸ���
//  ��  �룺�ַ���
//  ��  �������ŵĸ���
/*****************************************************/
int count_commas(char *arr) // �����ַ����ж��ŵĸ���
{
    int count = 0;                       // ���ŵĸ���
    for (int i = 0; arr[i] != '\0'; i++) // �����ַ���
    {
        if (arr[i] == ',') // �ж��Ƿ�Ϊ����
        {
            count++; // ���Ÿ�����1
        }
    }
    return count; // ���ض��Ÿ���
}

/*****************************************************/
//  ��������Parse_UTCTime
//  ��  ��������UTCʱ��
//  ��  �룺UTCʱ�䡢����ʱ��
//  ��  ������
/*****************************************************/
void Parse_UTCtime(char *utc_time, char *time)
{
    int hour, minute, second; // ʱ���֡���
    int decimal;              // С������
    // ����� HH��MM��SS �� SS.SS ����
    sscanf(utc_time, "%2d%2d%2d.%2d", &hour, &minute, &second, &decimal);
    // ת������ʱ��
    hour += 8;
    // ����ʱ��
    sprintf(time, "%2d:%2d:%2d.%2d", hour, minute, second, decimal);
}

/*****************************************************/
//  ��������RMC_Parse_UTCTime
//  ��  ��������UTCʱ��
//  ��  �룺UTCʱ�䡢����ʱ��
//  ��  ������
/*****************************************************/
void RMC_Parse_UTCtime(char *utc_time, char *time)
{
    int hour, minute, second; // ʱ���֡���
    int decimal;              // С������
    // ����� HH��MM��SS �� SS.SS ����
    sscanf(utc_time, "%2d%2d%2d.%2d", &hour, &minute, &second, &decimal);
    // ת������ʱ��
    hour += 8;
    // ����ʱ��
    sprintf(time, "%2d:%2d:%2d.%2d", hour, minute, second, decimal);
}




/*****************************************************/
//  ��������Parase_UTCdate
//  ��  ��������UTC����
//  ��  �룺UTC���ڡ���������
//  ��  ������
/*****************************************************/
void Parase_UTCdate(char *utc_date, char *date)
{
    int year, month, day; // �ꡢ�¡���
    // ����� YY��MM��DD ����
    sscanf(utc_date, "%2d%2d%2d", &year, &month, &day);
    // ��������
    sprintf(date, "%2d/%2d/%2d", year, month, day);
}
/*****************************************************/
//  ��������RMC_Parase_UTCdate
//  ��  ��������UTC����
//  ��  �룺UTC���ڡ���������
//  ��  ������
/*****************************************************/
void RMC_Parase_UTCdate(char *utc_date, char *date)
{
    int year, month, day; // �ꡢ�¡���
    // ����� YY��MM��DD ����
    sscanf(utc_date, "%2d%2d%2d", &year, &month, &day);
    // ��������
    sprintf(date, "%2d/%2d/%2d", year, month, day);
}

/*****************************************************/
//  ��������Parse_latitude
//  ��  ��������γ��
//  ��  ��: γ�ȡ�γ�����ݡ�γ�Ȱ���
//  ��  ������
/*****************************************************/
void Parse_latitude(char *latitude, char *lat, char *latHemi)
{
    int lat_d; // dd����
    int lat_temp0, lat_temp1;
    double lati; // γ��
    // ����� ddmm.mmmm ����
    sscanf(latitude, "%2d%2d.%d", &lat_d, &lat_temp0, &lat_temp1);
    // ������Чλ��
    lati = (double)lat_d + (double)lat_temp0 / 60 + (double)((double)lat_temp1 / 600000);
    lati = floor(lati * 100000000 + 0.5) / 100000000;
	sprintf(lat, "%f ", lati); // ���澭��
//    sprintf(lat, "%f %s", lati, latHemi); // ����γ��
}
/*****************************************************/
//  ��������RMC_Parse_latitude
//  ��  ��������γ��
//  ��  ��: γ�ȡ�γ�����ݡ�γ�Ȱ���
//  ��  ������
/*****************************************************/
void RMC_Parse_latitude(char *latitude, char *lat, char *latHemi)
{
    int lat_d; // dd����
    int lat_temp0, lat_temp1;
    double lati; // γ��
    // ����� ddmm.mmmm ����
    sscanf(latitude, "%2d%2d.%d", &lat_d, &lat_temp0, &lat_temp1);
    // ������Чλ��
    lati = (double)lat_d + (double)lat_temp0 / 60 + (double)((double)lat_temp1 / 600000);
    lati = floor(lati * 100000000 + 0.5) / 100000000;
    sprintf(lat, "%f %s", lati, latHemi); // ����γ��
}

/*****************************************************/
//  ��������Parse_longitude
//  ��  ������������
//  ��  �룺���ȡ��������ݡ����Ȱ���
//  ��  ������
/*****************************************************/
void Parse_longitude(char *longitude, char *lon, char *lonHemi)
{
    int lon_d; // dd����
    int lon_temp0, lon_temp1;
    double loni;
    // ����� ddmm.mmmm ����
    sscanf(longitude, "%3d%2d.%d", &lon_d, &lon_temp0, &lon_temp1);
    // ������Чλ��
    loni = (double)lon_d + (double)lon_temp0 / 60 + (double)((double)lon_temp1 / 600000);
    loni = floor(loni * 100000000 + 0.5) / 100000000;
	sprintf(lon, "%f ", loni); // ���澭��
//    sprintf(lon, "%f %s", loni, lonHemi); // ���澭��
}
/*****************************************************/
//  ��������RMC_Parse_longitude
//  ��  ������������
//  ��  �룺���ȡ��������ݡ����Ȱ���
//  ��  ������
/*****************************************************/
void RMC_Parse_longitude(char *longitude, char *lon, char *lonHemi)
{
    int lon_d; // dd����
    int lon_temp0, lon_temp1;
    double loni;
    // ����� ddmm.mmmm ����
    sscanf(longitude, "%3d%2d.%d", &lon_d, &lon_temp0, &lon_temp1);
    // ������Чλ��
    loni = (double)lon_d + (double)lon_temp0 / 60 + (double)((double)lon_temp1 / 600000);
    loni = floor(loni * 100000000 + 0.5) / 100000000;
    sprintf(lon, "%f %s", loni, lonHemi); // ���澭��
}
/*****************************************************/
//  ��������extract_RTK_Buffer
//  ��  ������ȡRTK���� �ֱ�����Ӧ�Ļ����д�����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void extract_RTK_Buffer(void)
{
    char *mark = NULL;                           // ���
    char sign1[] = "\r\n";                       // ��Ƿ���
    mark = strtok((char *)RxBuffer3, sign1); // ��\r\nΪ�����ȡ�ַ���

	
    while (mark != NULL)
    {
//        printf1(">--RTK-->> %s\r\n", mark);      // ��ӡÿ����ȡ���ַ���
        if (strstr(mark, "$GNRMC") != NULL)
        {
            strcpy((char *)RMC_Buffer, mark);    // �����ַ���
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
        mark = strtok(NULL, sign1); // ָ����һ�����ַ��� ʵ�ֱ���
    }
}



/*****************************************************/
//  ��������Parase_RMC
//  ��  ��: ����RMC����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_RMC(void)
{
    // $ GPRMC��<1>��<2>��<3>��<4>��<5>��<6>��<7>��<8>��<9>��<10>��<11>��<12> * hh
    // <1> UTCʱ�䣬hhmmss��ʱ���룩��ʽ
    // <2>��λ״̬��A =��Ч��λ��V =��Ч��λ
    // <3>γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
    // <4>γ�Ȱ���N�������򣩻�S���ϰ���
    // <5>����dddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
    // <6>���Ȱ���E����������W��������
    // <7>�������ʣ�000.0�9�1999.9�ڣ�ǰ���0Ҳ�������䣩
    // <8>���溽��000.0�9�1359.9�ȣ����汱Ϊ�ο���׼��ǰ���0Ҳ�������䣩
    // <9> UTC���ڣ�ddmmyy�������꣩��ʽ
    // <10>��ƫ�ǣ�000.0�9�1180.0�ȣ�ǰ���0Ҳ�������䣩
    // <11>��ƫ�Ƿ���E��������W������
    // <12>ģʽָʾ����NMEA0183 3.00�汾�����A =������λ��D =��֣�E =Ͷ�ţ�N =������Ч��
    char *subString;                           // ���ַ���
    char *subStringNext;                       // ���ַ�����һ��
    char count = 0;                            // ����
    if (count_commas((char *)RMC_Buffer) < 12) // �ж϶��Ÿ����Ƿ�С��13
    {
        memset(RMC_Buffer, 0, sizeof(RMC_Buffer));
		RMC_Flag = 0; //��־λ��0
    }
	else
	{
		RMC_Flag = 1; //��־λ��1
	}
	if(RMC_Flag == 1)
	{
		for (count = 0; count <= 12; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)RMC_Buffer, ","); // ���Ҷ���
	//			printf1("RMC_Buffer:%s \r\n",RMC_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memset(RMC.UTCtime, 0, sizeof(RMC.UTCtime));
						memcpy(RMC.UTCtime, subString, subStringNext - subString); // ��ȡUTCʱ��
						break;
					case 2:
						memset(RMC.GPS_sta, 0, sizeof(RMC.GPS_sta));
						memcpy(RMC.GPS_sta, subString, subStringNext - subString); // ��ȡ��λ״̬��A=��Ч��λ��V=��Ч��λ
						break;
					case 3:
						memset(RMC.latitude, 0, sizeof(RMC.latitude));
						memcpy(RMC.latitude, subString, subStringNext - subString-1); // ��ȡγ����Ϣ(�ȷ�)
						break;
					case 4:
						memset(RMC.latitudeHemi, 0, sizeof(RMC.latitudeHemi));
						memcpy(RMC.latitudeHemi, subString, subStringNext - subString); // ��ȡγ�Ȱ���(N/S)
						break;
					case 5:
						memset(RMC.longitude, 0, sizeof(RMC.longitude));
						memcpy(RMC.longitude, subString, subStringNext - subString-1); // ��ȡ������Ϣ(�ȷ�)
						break;
					case 6:
						memset(RMC.longitudeHemi, 0, sizeof(RMC.longitudeHemi));
						memcpy(RMC.longitudeHemi, subString, subStringNext - subString); // ��ȡ���Ȱ���(E/W)
						break;
					case 7:
						memset(RMC.speed, 0, sizeof(RMC.speed));
						memcpy(RMC.speed, subString, subStringNext - subString); // ��ȡ��������
						break;
					case 8:
						memset(RMC.course, 0, sizeof(RMC.course));
						memcpy(RMC.course, subString, subStringNext - subString); // ��ȡ���溽��
						break;
					case 9:
						memset(RMC.UTCdate, 0, sizeof(RMC.UTCdate));
						memcpy(RMC.UTCdate, subString, subStringNext - subString); // ��ȡUTC����
						break;
					case 10:
						memset(RMC.magneticVariation, 0, sizeof(RMC.magneticVariation));
						memcpy(RMC.magneticVariation, subString, subStringNext - subString); // ��ȡ��ƫ��
						break;
					case 11:
						memset(RMC.magneticVariationDirection ,0, sizeof(RMC.magneticVariationDirection));
						memcpy(RMC.magneticVariationDirection, subString, subStringNext - subString); // ��ȡ��ƫ�Ƿ���
						break;
					case 12:
						memset(RMC.modeIndication, 0, sizeof(RMC.modeIndication));
						memcpy(RMC.modeIndication, subString, subStringNext - subString); // ��ȡģʽָʾ
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		// ����UTCʱ��
		RMC_Parse_UTCtime(RMC.UTCtime, RMC.UTCtime);
		// ����UTC����
		RMC_Parase_UTCdate(RMC.UTCdate, RMC.UTCdate);
		// ����γ��
		RMC_Parse_latitude(RMC.latitude, RMC.latitude, RMC.latitudeHemi);
		// ��������
		RMC_Parse_longitude(RMC.longitude, RMC.longitude, RMC.longitudeHemi);
			
		RMC_Flag = 0; //��־λ��0
//		printf1("RMC:%s,%s\r\n",RMC.longitude,RMC.latitude);
	//	printf1("Time:%s\r\n", RMC.UTCtime); // ��ӡUTCʱ��
	}
    
}


_GGA_Typedef GGA2;

/*****************************************************/
//  ��������Parase_GGA
//  ��  ��: ����GGA����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_GGA(void)
{
    // $ GPGGA��<1>��<2>��<3>��<4>��<5>��<6>��<7>��<8>��<9>��M��<10>��M��<11> ��<12> * hh
    // <1> UTCʱ�䣬hhmmss��ʱ���룩��ʽ
    // <2>γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
    // <3>γ�Ȱ���N�������򣩻�S���ϰ���
    // <4>����dddmm.mmmm���ȷ֣���ʽ��ǰ���0Ҳ�������䣩
    // <5>���Ȱ���E����������W��������
    // <6> GPS״̬��0 =δ��λ��1 =�ǲ�ֶ�λ��2 =��ֶ�λ��6 =���ڲ���
    // <7>����ʹ�ý���λ�õ�����������00�9�112����ǰ���0Ҳ�������䣩
    // <8> HDOPˮƽ�������ӣ�0.5�9�199.9��
    // <9>���θ߶ȣ�-9999.9�9�199999.9��
    // <10>��������������Դ��ˮ׼��ĸ߶�
    // <11>���ʱ�䣨�����һ�ν��յ�����źſ�ʼ��������������ǲ�ֶ�λ��Ϊ�գ�
    // <12>���վID��0000�9�11023��ǰ���0Ҳ�������䣬������ǲ�ֶ�λ��Ϊ�գ�
    char *subString;                           // ���ַ���
    char *subStringNext;                       // ���ַ�����һ��
    char count = 0;                            // ����
    if (count_commas((char *)GGA_Buffer) != 14) // �ж϶��Ÿ����Ƿ�С��12
    {
        memset(GGA_Buffer,0, sizeof(GGA_Buffer));
		GGA_Flag = 0; //��־λ��0
		
    }
	else 
	{
		GGA_Flag = 1; //��־λ��1
	}
		if(GGA_Flag == 1)
	{	
			 for (count = 0; count <= 14; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)GGA_Buffer, ","); // ���Ҷ���
	//			printf1("GGA_Buffer:%s\r\n",GGA_Buffer);
				
			
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memset(GGA.UTCtime, 0, sizeof(GGA.UTCtime));
						memcpy(GGA.UTCtime, subString, subStringNext - subString); // ��ȡUTCʱ��
						break;
					case 2:
						memset(GGA.latitude, 0, sizeof(GGA.latitude));
						memcpy(GGA.latitude, subString, subStringNext - subString); // ��ȡγ����Ϣ(�ȷ�)
						break;
					case 3:
						memset(GGA.latitudeHemi, 0, sizeof(GGA.latitudeHemi));
						memcpy(GGA.latitudeHemi, subString, subStringNext - subString); // ��ȡγ�Ȱ���(N/S)
						break;
					case 4:
						memset(GGA.longitude, 0, sizeof(GGA.longitude));
						memcpy(GGA.longitude, subString, subStringNext - subString); // ��ȡ������Ϣ(�ȷ�)
						break;
					case 5:
						memset(GGA.longitudeHemi, 0, sizeof(GGA.longitudeHemi));
						memcpy(GGA.longitudeHemi, subString, subStringNext - subString); // ��ȡ���Ȱ���(E/W)
						break;
					case 6:
						memset(GGA.GPS_sta, 0, sizeof(GGA.GPS_sta));
						memcpy(GGA.GPS_sta, subString, subStringNext - subString); // ��ȡGPS״̬
						break;
					case 7:
						memset(GGA.satellites, 0, sizeof(GGA.satellites));
						memcpy(GGA.satellites, subString, subStringNext - subString); // ��ȡ����ʹ�ý���λ�õ���������
						break;
					case 8:
						memset(GGA.HDOP, 0, sizeof(GGA.HDOP));
						memcpy(GGA.HDOP, subString, subStringNext - subString); // ��ȡHDOPˮƽ��������
						break;
					case 9:
						memset(GGA.altitude, 0, sizeof(GGA.altitude));
						memcpy(GGA.altitude, subString, subStringNext - subString); // ��ȡ���θ߶�
						break;
					 case 10:
						memset(GGA.altitudeunit, 0, sizeof(GGA.altitudeunit));
						memcpy(GGA.altitudeunit, subString, subStringNext - subString); // ��ȡ���θ߶ȵ�λ
						break;
					case 11:
						memset(GGA.geoidHeight, 0, sizeof(GGA.geoidHeight));
						memcpy(GGA.geoidHeight, subString, subStringNext - subString); // ��ȡ��������������Դ��ˮ׼��ĸ߶�
						break;
					case 12:
						memset(GGA.geoidHeightunit, 0, sizeof(GGA.geoidHeightunit));
						memcpy(GGA.geoidHeightunit, subString, subStringNext - subString); // ��ȡ��������������Դ��ˮ׼��ĸ߶ȵ�λ
						break;
					case 13:
						memset(GGA.DGPS_age, 0, sizeof(GGA.DGPS_age));
						memcpy(GGA.DGPS_age, subString, subStringNext - subString); // ��ȡ���ʱ��
						break;
					case 14:
						memset(GGA.DGPS_ID, 0, sizeof(GGA.DGPS_ID));
						memcpy(GGA.DGPS_ID, subString, subStringNext - subString); // ��ȡ���վID��
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
		// ����UTCʱ��
		Parse_UTCtime(GGA.UTCtime, GGA2.UTCtime);
		// ����γ��
		Parse_latitude(GGA.latitude, GGA2.latitude, GGA.latitudeHemi);
		// ��������
		Parse_longitude(GGA.longitude, GGA2.longitude, GGA.longitudeHemi);

		GGA_Flag = 0; //��־λ��0
	}
   
	
//	printf1("GGA:%s\r\n",GGA2.UTCtime);
//	printf1("GGA:%s, %s\r\n",GGA2.longitude,GGA2.latitude);
//	printf1("GGA:%s, %s\r\n",GGA2.longitudeHemi,GGA2.latitudeHemi);
}



/*****************************************************/
//  ��������Parase_GSA
//  ��  ��: ����GSA����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_GSA(void)
{
    // $ GPGSA��<1>��<2>��<3>��<4> ���������� <12>��<13>��<14>��<15>��<16>��<17>��<18>
    // <1>ģʽ��M =�ֶ���A =�Զ���
    // <2>��λ��ʽ1 =δ��λ��2 =��ά��λ��3 =��ά��λ��
    // <3>��<14> PRN���֣�01��32�����ʹ���е����Ǳ�ţ����ɽ���12��������Ϣ
    // <15> PDOPλ�þ������ӣ�0.5�9�199.9��
    // <16> HDOPˮƽ�������ӣ�0.5�9�199.9��
    // <17> VDOP��ֱ�������ӣ�0.5�9�199.9��
    // <18>У���
    char *subString;                           // ���ַ���
    char *subStringNext;                       // ���ַ�����һ��
    char count = 0;                            // ����
    if (count_commas((char *)GSA_Buffer) != 18) // �ж϶��Ÿ����Ƿ�С��18
    {
        memset(GSA_Buffer, 0, sizeof(GSA_Buffer));
		GSA_Flag = 0; //��־λ��0
		
    }
	else 
	{
		GSA_Flag = 1; //��־λ��1
	}
	if(GSA_Flag == 1)
	{
			 for (count = 0; count <= 18; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)GSA_Buffer, ","); // ���Ҷ���
//				printf1("GSA_Buffer:%s\r\n",GSA_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memcpy(GSA.mode, subString, subStringNext - subString); // ��ȡģʽ
						break;
					case 2:
						memcpy(GSA.fixType, subString, subStringNext - subString); // ��ȡ��λ����
						break;
					case 3:
						memcpy(GSA.satellites, subString, subStringNext - subString); // ��ȡʹ����������
						break;
					case 15:
						memcpy(GSA.PDOP, subString, subStringNext - subString); // ��ȡPDOP
						break;
					case 16:
						memcpy(GSA.HDOP, subString, subStringNext - subString); // ��ȡHDOP
						break;
					case 17:
						memcpy(GSA.VDOP, subString, subStringNext - subString); // ��ȡVDOP
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		GSA_Flag = 0;//��־λ��0
	}
   
}


/*****************************************************/
//  ��������Parase_GSV
//  ��  ��: ����GSV����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_GSV(void)
{
    // $ GPGSV��<1>��<2>��<3>��<4>��<5>��<6>��<7>����<4>��<5>��<6>��<7>��<8 >
    // <1> GSV��������
    // <2>����GSV�ı��
    // <3>�ɼ����ǵ�������00��12��
    // <4>���Ǳ�ţ�01��32��
    // <5>�������ǣ�00��90�ȡ�
    // <6>���Ƿ�λ�ǣ�000��359�ȡ�ʵ��ֵ��
    // <7>Ѷ�������ȣ�C / No����00��99 dB���ޱ�δ���յ�Ѷ�š�
    // <8>У���
    char *subString;                          // ���ַ���
    char *subStringNext;                      // ���ַ�����һ��
    char count = 0;                           // ����
    if (count_commas((char *)GSV_Buffer) < 8) // �ж϶��Ÿ����Ƿ�С��8
    {
        memset(GSV_Buffer, 0, sizeof(GSV_Buffer));
		GSV_Flag = 0; //��־λ��0
    }
	else 
	{
		GSV_Flag = 1; //��־λ��1
	}
	if(GSV_Flag == 1)
	{
			for (count = 0; count <= 3; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)GSV_Buffer, ","); // ���Ҷ���
//				printf1("GSV_Buffer:%s\r\n",GSV_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memcpy(GSV.totalMessages, subString, subStringNext - subString); // ��ȡ����Ϣ��
						break;
					case 2:
						memcpy(GSV.messageNumber, subString, subStringNext - subString); // ��ȡ��Ϣ���
						break;
					case 3:
						memcpy(GSV.satellitesInView, subString, subStringNext - subString); // ��ȡ�ɼ���������
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		GSV_Flag = 0; //��־λ��0
	}
    
}



/*****************************************************/
//  ��������Parase_VTG
//  ��  ��: ����VTG����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_VTG(void)
{
    // $ GPVTG��<1>��T��<2>��M��<3>��N��<4>��K��<5> * hh
    // �ֶ�0��$GPVTG�����ID�����������ΪTrack Made Good and Ground Speed��VTG�������ٶ���Ϣ
    // �ֶ�1���˶��Ƕȣ�000 - 359����ǰ��λ��������0��
    // �ֶ�2��T=�汱����ϵ
    // �ֶ�3���˶��Ƕȣ�000 - 359����ǰ��λ��������0��
    // �ֶ�4��M=�ű�����ϵ
    // �ֶ�5��ˮƽ�˶��ٶȣ�0.00����ǰ��λ��������0��
    // �ֶ�6��N=�ڣ�Knots
    // �ֶ�7��ˮƽ�˶��ٶȣ�0.00����ǰ��λ��������0��
    // �ֶ�8��K=����/ʱ��km/h
    // �ֶ�9��У��ֵ��$��*֮����������ֵ��
    char *subString;                          // ���ַ���
    char *subStringNext;                      // ���ַ�����һ��
    char count = 0;                           // ����
    if (count_commas((char *)VTG_Buffer) < 9) // �ж϶��Ÿ����Ƿ�С��9
    {
        memset(VTG_Buffer, 0, sizeof(VTG_Buffer));
		VTG_Flag = 0; //��־λ��0
    }
	else 
	{
		VTG_Flag = 1; //��־λ��1
	}
	if(VTG_Flag == 1)
	{
			 for (count = 0; count <= 9; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)VTG_Buffer, ","); // ���Ҷ���
//				printf1("VTG_Buffer:%s\r\n",VTG_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memcpy(VTG.course, subString, subStringNext - subString); // ��ȡ���溽��
						break;
					case 2:
						memcpy(VTG.reference, subString, subStringNext - subString); // ��ȡ�ο�
						break;
					case 3:
						memcpy(VTG.courseMagnetic, subString, subStringNext - subString); // ��ȡ���溽���ƫ��
						break;
					case 4:
						memcpy(VTG.referenceMagnetic, subString, subStringNext - subString); // ��ȡ�ο���ƫ��
						break;
					case 5:
						memcpy(VTG.speedKnots, subString, subStringNext - subString); // ��ȡ��������(��)
						break;
					case 6:
						memcpy(VTG.referenceKnots, subString, subStringNext - subString); // ��ȡ�ο�(��)
						break;
					case 7:
						memcpy(VTG.speedKm, subString, subStringNext - subString); // ��ȡ��������(����/Сʱ)
						break;
					case 8:
						memcpy(VTG.referenceKm, subString, subStringNext - subString); // ��ȡ�ο�(����/Сʱ)
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		VTG_Flag = 0; //��־λ��0
	}
   
}



/*****************************************************/
//  ��������Parase_GLL
//  ��  ��: ����GLL����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_GLL(void)
{
    // $GPGLL,<1>,<2>,<3>,<4>,<5>,<6>*2D
    // �ֶ�0��$GPGLL�����ID�����������ΪGeographic Position��GLL������λ��Ϣ
    // �ֶ�1��γ��ddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
    // �ֶ�2��γ��N����γ����S����γ��
    // �ֶ�3������dddmm.mmmm���ȷָ�ʽ��ǰ��λ��������0��
    // �ֶ�4������E����������W��������
    // �ֶ�5��UTCʱ�䣬hhmmss.sss��ʽ
    // �ֶ�6��״̬��A=��λ��V=δ��λ
    // �ֶ�7��У��ֵ��$��*֮����������ֵ��
    char *subString;                          // ���ַ���
    char *subStringNext;                      // ���ַ�����һ��
    char count = 0;                           // ����
    if (count_commas((char *)GLL_Buffer) != 7) // �ж϶��Ÿ����Ƿ�С��7
    {
        memset(GLL_Buffer, 0, sizeof(GLL_Buffer));
		GLL_Flag = 0; //��־λ��0
    }
	else
	{
		GLL_Flag = 1; //��־λ��1
	}
		if(GLL_Flag == 1)
	{
			 for (count = 0; count <= 7; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)GLL_Buffer, ","); // ���Ҷ���
	//			printf1("GLL_Buffer:%s\r\n",GLL_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 1:
						memcpy(GLL.latitude, subString, subStringNext - subString); // ��ȡγ����Ϣ(�ȷ�)
						break;
					case 2:
						memcpy(GLL.latitudeHemi, subString, subStringNext - subString); // ��ȡγ�Ȱ���(N/S)
						break;
					case 3:
						memcpy(GLL.longitude, subString, subStringNext - subString); // ��ȡ������Ϣ(�ȷ�)
						break;
					case 4:
						memcpy(GLL.longitudeHemi, subString, subStringNext - subString); // ��ȡ���Ȱ���(E/W)
						break;
					case 5:
						memcpy(GLL.UTCtime, subString, subStringNext - subString); // ��ȡUTCʱ��
						break;
					case 6:
						memcpy(GLL.status, subString, subStringNext - subString); // ��ȡ״̬
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}

			// ����UTCʱ��
		Parse_UTCtime(GLL.UTCtime, GLL.UTCtime);
		// ����γ��
		Parse_latitude(GLL.latitude, GLL.latitude, GLL.latitudeHemi);
		// ��������
		Parse_longitude(GLL.longitude, GLL.longitude, GLL.longitudeHemi);
		GLL_Flag = 0; //��־λ��0
	
	}
   
	
//	printf1("GLL:%s, %s\r\n",GLL.longitude,GLL.latitude);
}


/*****************************************************/
//  ��������Parase_WTZ
//  ��  ��: ����RTK��̬����������
//  ��  �룺��
//  ��  ������
/*****************************************************/

void Parase_WTZ(void)
{
    // $WTRTK,0.00,0.00,0.00,0.00,-9.25,-1.28,0.00,0,19,0,5
    // ����        ˵��
    // $WTRTK      ��ͷ
    // 0.00        ���X���루��λ���ף�
    // 0.00        ���Y���루��λ���ף�
    // 0.00        ���Z���루��λ���ף�
    // 0.00        ���R���루��λ���ף�
    // -9.25       ������
    // -1.28       �����
    // 0.00        �����
    // 0           �ƶ�վRTK״̬    0��ʾ��ʼ����1��ʾ���㶨λ��2��ʾ���֣�4��ʾ�̶��⣬5��ʾ�����
    // 19          4G״̬           0~13�����ò��� 14~20��������   21���������
    // 0           �̶���վ״̬     -1��ʾѡ��̶���վʧ�� 0��ʾѡ���޹̶���վѡ�� 1��ʾѡ��̶���վ�ɹ�
    // CSQ         4G�ź�����
    // 5           Ntrip״̬        5:���ӳɹ�  ������������
    char *subString;                           // ���ַ���
    char *subStringNext;                       // ���ַ�����һ��
    char count = 0;                            // ����
    if (count_commas((char *)WTZ_Buffer) < 10 ) // �ж϶��Ÿ����Ƿ����10
    {
        memset(WTZ_Buffer, 0, sizeof(WTZ_Buffer));
		WTZ_Flag = 0; //��־λ��0
    }
	else
	{
		WTZ_Flag = 1; //��־λ��1
	}
	if(WTZ_Flag == 1)
	{
			  for (count = 0; count <= 12; count++) // ��ȡȫ������
		{
			if (count == 0)
			{
				subString = strstr((const char *)WTZ_Buffer, ","); // ���Ҷ���
//				printf1("WTZ_Buffer:%s\r\n",WTZ_Buffer);
			}
			else
			{
				subString++;                                          // ƫ�Ƶ����ź���
				if ((subStringNext = strstr(subString, ",")) != NULL) // ������һ������
				{
					switch (count)
					{
					case 5:
						memcpy(WTZ.roll, subString, subStringNext - subString); // ��ȡ������
						break;
					case 6:
						memcpy(WTZ.pitch, subString, subStringNext - subString); // ��ȡ�����
						break;
					case 7:
						memcpy(WTZ.yaw, subString, subStringNext - subString); // ��ȡ�����
						break;
					case 8:
						memcpy(WTZ.RTK_status, subString, subStringNext - subString); // ��ȡ�ƶ�վRTK״̬
						break;
					case 9:
						memcpy(WTZ.status_4G, subString, subStringNext - subString); // ��ȡ4G״̬
						break;
					case 10:
						memcpy(WTZ.quality_4G, subString, subStringNext - subString); // ��ȡ�̶���վ״̬
						break;
					default:
						break;
					}
					subString = subStringNext;
				}
			}
		}
		WTZ_Flag = 0; //��־λ��1
	}
  

}


/*****************************************************/
//  ��������Parase_RTK  ������
//  ��  ��: ����RTK����
//  ��  �룺��
//  ��  ������
/*****************************************************/
void Parase_RTK(void)
{
    extract_RTK_Buffer(); // ��ȡRTK����
    Parase_RMC();         // ����RMC����
    Parase_GGA();         // ����GGA����
    Parase_GSA();         // ����GSA����
    Parase_GSV();         // ����GSV����
    Parase_VTG();         // ����VTG����
    Parase_GLL();         // ����GLL����
    Parase_WTZ();         // ����RTK��̬����������
}
