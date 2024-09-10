#include "ec20.h"
#include <stdlib.h>
#include "usart.h"
#include <stdio.h>
#include "delay.h"
#include "cJSON.h"
#include <string.h>


uint8_t temperature;     // 温度
uint8_t humidity;        // 湿度
float noise = 0;		 // 噪音
float pm = 0;     		 // PM2.5
float Lux = 0;     		 // 光强
float UV = 0;            // 紫外线值
int UVindex = 0;		 //紫外线等级
double latitude = 0;     // 纬度
double longitude = 0;    // 经度


static char *strx;
static uint8_t count = 0; // 定义变量

void Clear_Buffer(void)//清空缓存
{
	u8 i;
	for(i=0;i<Rxcouter;i++)
	RxBuffer[i]=0;//缓存
	Rxcouter=0;

}



void EC20_4G_Reset(void) // 重启模块
{
    printf("AT+CFUN=1,1\r\n"); // 发送AT指令 重启模块 会断电
}

uint8_t EC20_init_check(uint8_t res)
{
    USART2_RX_Flag = 0;
    count = res;           // 读取初始化状态
    uint8_t reset_cnt = 0; // 定义重启次数
    while (count != 0x0F)
    {
        switch (count)
        {
        case 0:
					  Clear_Buffer();	 
            printf("ATI\r\n");                                               // 发送AT指令
            delay_ms(300);                                                   // 延时300ms
            strx = strstr((const char *)&RxBuffer, (const char *)"OK"); // 判断是否有OK
            printf1(">--EC20-->> ATI\r\n");                                  // 发送AT指令
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            delay_ms(300);  // 延时300ms
					  delay_ms(500);  // 延时500ms
          
            USART2_RX_Flag = 0;
            reset_cnt++;
            if (strx != NULL) // 判断是否有OK
            {
                count = 1; // 有OK，进入下一步
            }
            else
            {
                count = 0; // 没有OK，重新发送AT指令
                if (reset_cnt % 3 == 1)
                {
                    printf1(">--print-->> EC20 RESET\r\n");
                    printf("\r\n");
                    EC20_4G_Reset(); // 重启模块
                }
                delay_ms(3000); // 延时3s
                break;
            }
            // break;
        case 1:
					  Clear_Buffer();	
            printf("ATE0\r\n");                                             // 发送ATE0指令 关闭回显
            delay_ms(300);                                                  // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK"); // 判断是否有OK
            printf1(">--EC20-->> ATE0\r\n");                                // 发送ATE0指令 关闭回显
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
         	  delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 2;
            }
            else
            {
                count = 1;
                break;
            }
            // break;
        case 2:
					  Clear_Buffer();	
            printf("AT+CPIN?\r\n");                          // 发送AT+CPIN?指令 检测SIM卡是否插入
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"READY");
            printf1(">--EC20-->> AT+CPIN?\r\n"); // 发送AT+CPIN?指令 检测SIM卡是否插入
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
           	  delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 3;
            }
            else
            {
                count = 2;
                break;
            }
            // break;
        case 3:
					  Clear_Buffer();	
            printf("AT+CREG?\r\n");                          // 发送AT+CREG?指令 检测网络是否注册
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"+CREG: 0,1");
            printf1(">--EC20-->> AT+CREG?\r\n"); // 发送AT+CREG?指令 检测网络是否注册
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
         	  delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 4;
            }
            else
            {
                count = 3;
                break;
            }
            // break;
        case 4:
					  Clear_Buffer();	
            printf("AT+CSQ\r\n");                            // 发送AT+CSQ指令 检测信号强度
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"+CSQ:");
            printf1(">--EC20-->> AT+CSQ\r\n"); // 发送AT+CSQ指令 检测信号强度
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
        	  delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 5;
            }
            else
            {
                count = 4;
                break;
            }
            // break;
        case 5:
					  Clear_Buffer();	
            printf("AT+CGREG?\r\n");                         // 发送AT+CGREG?指令 检测是否注册到GPRS网络
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"+CGREG: 0,1");
            printf1(">--EC20-->> AT+CGREG?\r\n"); // 发送AT+CGREG?指令 检测是否注册到GPRS网络
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
        	  delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 6;
            }
            else
            {
                count = 5;
                break;
            }
            // break;
        case 6:
					  Clear_Buffer();	
            printf("AT+CGATT?\r\n");                         // 发送AT+CGATT?指令 检测是否附着网络
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"+CGATT: 1");
            printf1(">--EC20-->> AT+CGATT?\r\n"); // 发送AT+CGATT?指令 检测是否附着网络
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
						delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 7;
            }
            else
            {
                count = 6;
                break;
            }
            // break;
        case 7:
					  Clear_Buffer();	
            printf("AT+QGPS=1\r\n");                         // 发送AT+QGPS=1指令 打开GPS
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QGPS=1\r\n"); // 发送AT+QGPS=1指令 打开GPS
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
						delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            count = 8;
        case 8:
					  Clear_Buffer();	
            printf("AT+QMTDISC=0\r\n");                      // 发送AT+QMTDISC=0指令 断开MQTT连接
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QMTDISC=0\r\n"); // 发送AT+QMTDISC=0指令 断开MQTT连接
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
        	  delay_ms(500);  // 延时500ms
            if (strx != NULL)
            {
                count = 9;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 9:
					  Clear_Buffer();	
            printf("AT+QIDEACT=1\r\n");                      // 发送AT+QIDEACT=1指令 断开GPRS连接
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QIDEACT=1\r\n"); // 发送AT+QIDEACT=1指令 断开GPRS连接
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
          	delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 10;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 10:
					  Clear_Buffer();	
            printf("AT+QIACT=1\r\n");                        // 发送AT+QICLOSE=0指令 断开TCP连接
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QIACT=1\r\n"); // 发送AT+QICLOSE=0指令 断开TCP连接
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
           	delay_ms(500);  // 延时500ms
            if (strx != NULL)
            {
                count = 11;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 11:
					  Clear_Buffer();	
            printf("AT+QMTCFG=\"qmtping\",0,30\r\n");        // 发送AT+QMTCFG='qmtping',0,30指令 设置MQTT心跳时间为30秒
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QMTCFG='qmtping',0,30\r\n"); // 发送AT+QMTCFG='qmtping',0,30指令 设置MQTT心跳时间为30秒
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
          	delay_ms(500);  // 延时500ms
            if (strx != NULL)
            {
                count = 12;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 12:
					  Clear_Buffer();	
            printf("AT+QMTCFG=\"recv/mode\",0,0,1\r\n");     // 发送AT+QMTCFG='recv/mode',0,0,1指令 设置MQTT接收模式为1
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QMTCFG=\"recv/mode\",0,0,1\r\n"); // 发送AT+QMTCFG='recv/mode',0,0,1指令 设置MQTT接收模式为1
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
          	delay_ms(500);  // 延时500ms
            if (strx != NULL)
            {
                count = 13;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 13:
					  Clear_Buffer();	
            printf("AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n");              // 发送AT+QMTOPEN=0, "",1883指令 连接MQTT服务器
            delay_ms(300);                                                 // 延时300ms
            printf1(">--EC20-->> AT+QMTOPEN=0,\"x.x.x.x\",1883\r\n"); // 发送AT+QMTOPEN=0, "",1883指令 连接MQTT服务器
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            strx = strstr((const char *)RxBuffer, (const char *)"+QMTOPEN: 0,0");
            printf1(" %s\r\n", RxBuffer);
          	delay_ms(500);  // 延时500ms
            USART2_RX_STA = 0;
            if (strx != NULL)
            {
                count = 14;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 14:
						Clear_Buffer();	
            printf("AT+QMTCONN=0,\"light\",\"root\",\"xxxxxxxxxx\"\r\n"); // 发送AT+QMTCONN=0, "",1883指令 连接数据库
            delay_ms(300);                                           // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"+QMTCONN: 0,0,0");
            printf1(">--EC20-->> AT+QMTCONN=0,\"light\",\"root\",\"xxxxxxxxxx\"\r\n"); // 发送AT+QMTCONN=0, "",1883指令 连接数据库
            delay_ms(300);
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
           	 delay_ms(500);  // 延时500ms
            if (strx != NULL)
            {
                count = 15;
            }
            else
            {
                count = 8;
                break;
            }
            // break;
        case 15:
            printf1(">--print-->> EC20初始化成功\r\n");
            count = 15;
            return count;
        default:
            printf1(">--print-->> EC20初始化失败\r\n");
            break;
        }
    }
    return count;
}

void Mqtt_Senddata(void)
{
    count = 1;
    /* 构建JSON上报数据 */
    // 创建JSON数据对象
    cJSON *payload_data = cJSON_CreateObject();
    // 定义JSON字符串
    char *payload_message;  
    // 添加设备ID
    cJSON_AddItemToObject(payload_data, "DeviceID", cJSON_CreateString("1001"));
    // 添加温度
    cJSON_AddItemToObject(payload_data, "temperature", cJSON_CreateNumber(temperature));
    // 添加经度
    cJSON_AddItemToObject(payload_data, "lon", cJSON_CreateNumber(longitude));
    // 添加纬度
    cJSON_AddItemToObject(payload_data, "lat", cJSON_CreateNumber(latitude));
    // 添加湿度
    cJSON_AddItemToObject(payload_data, "humidity", cJSON_CreateNumber(humidity));
	// 添加紫外线等级
    cJSON_AddItemToObject(payload_data, "UVindex", cJSON_CreateNumber(UVindex));
	// 添加PM2.5
    cJSON_AddItemToObject(payload_data, "pm", cJSON_CreateNumber(pm));
	// 添加噪音
    cJSON_AddItemToObject(payload_data, "noise", cJSON_CreateNumber(noise));
	// 添加噪音
    cJSON_AddItemToObject(payload_data, "Lux", cJSON_CreateNumber(Lux));
	
	
	
	
	
	
	
	
	
   
	cJSON *temperature_item = cJSON_GetObjectItem(payload_data, "temperature"); // 获取温度项
	if (temperature_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(temperature_item, temperature); // 更新温度值
	}
	cJSON *longitude_item = cJSON_GetObjectItem(payload_data, "lon"); // 获取经度项
	if (longitude_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(longitude_item, longitude); // 更新经度值
	}
	cJSON *latitude_item = cJSON_GetObjectItem(payload_data, "lat"); // 获取纬度项
	if (latitude_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(latitude_item, latitude); // 更新纬度值
	}
	cJSON *humidity_item = cJSON_GetObjectItem(payload_data, "humidity"); // 获取湿度项
	if (humidity_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(humidity_item, humidity); // 更新湿度值
	}
	cJSON *UVindex_item = cJSON_GetObjectItem(payload_data, "UVindex"); // 获取紫外线项
	if (UVindex_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(UVindex_item, UVindex); // 更新紫外线值
	}
	cJSON *pm_item = cJSON_GetObjectItem(payload_data, "pm"); // 获取PM2.5项
	if (pm_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(pm_item, pm); // 更新PM2.5值
	}
	cJSON *noise_item = cJSON_GetObjectItem(payload_data, "noise"); // 获取噪音项
	if (noise_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(noise_item, noise); // 更新噪音值
	}
	cJSON *Lux_item = cJSON_GetObjectItem(payload_data, "Lux"); // 获取光强项
	if (Lux_item != NULL) { // 判断该项是否存在
		cJSON_SetNumberValue(Lux_item, Lux); // 更新光强值
	}

	// 将JSON数据对象转换为字符串
	payload_message = cJSON_PrintUnformatted(payload_data);
    while(count != 0x02)
    {
        switch (count)
        {
        case 1:
					  Clear_Buffer();	
            printf("AT+QMTPUBEX=0,0,0,0,\"light\",%d\r\n",strlen((char *)payload_message));  // 发送AT+QMTPUB=0,0,0,0,'port'指令 发布话题
            delay_ms(300);  // 延时300ms
            printf("%s\r\n",payload_message);  // 发送JSON字符串
            delay_ms(300);      // 延时300ms
            strx = strstr((const char*)RxBuffer,(const char*)"+QMTPUBEX: 0,0,0");
            printf1(">--EC20-->> AT+QMTPUB=0,0,0,0,\"light\",%d\r\n",strlen((char *)payload_message));  // 发送AT+QMTPUB=0,0,0,0,'port'指令 发布话题
            delay_ms(100);
            printf1(">--JSON-->> %s\r\n",payload_message);
            delay_ms(300);      // 延时300ms
            /********************/
            /*		释放内存	 */
            /********************/
            cJSON_Delete(payload_data);  // 释放JSON数据对象
            free(payload_message);  // 释放JSON字符串
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n",RxBuffer);
            USART2_RX_STA = 0;
            if(strx != NULL)
            {
                count = 2;
            }
            else
            {
                count = 0;
                break;
            }
        case 2:
            printf1(">--print-->> 发布成功\r\n");
            break;
        case 0:
            printf1(">--print-->> 发布失败\r\n");
            printf1(">--print-->> MQTT连接重建\r\n");
            EC20_4G_Reset();  // EC20重启
            delay_ms(3000);
            EC20_init_check(0);  // MQTT连接重建
            break;
        default:
            printf1(">--print-->> 发布失败\r\n");
            printf1(">--print-->> MQTT连接重建\r\n");
            EC20_4G_Reset();  // EC20重启
            delay_ms(3000);
            EC20_init_check(0);  // MQTT连接重建
            break;
        }
    }
}



_GPRMC_Typedef GPRMC; // 定义GPRMC结构体
// 解析UTC时间
void Parse_UTCTime(void)
{
    int hour, minute, second;
    int decimal;
    // 分离出 HH、MM、SS 和 SS.SS 部分
    sscanf(GPRMC.UTCtime, "%2d%2d%2d.%2d", &hour, &minute, &second, &decimal);
    // 转换北京时间
    hour += 8;
    // 计算时间
    sprintf(GPRMC.Time, "%2d:%2d:%2d.%2d", hour, minute, second, decimal);
}

// 解析经纬度
void Parse_gps_data(void)
{
    int lat_d, lon_d; // dd分量
    int lat_temp0, lon_temp0, lat_temp1, lon_temp1;

    // 分离出 ddmm.mmmm 部分
    sscanf(GPRMC.latitude, "%2d%2d.%4d", &lat_d, &lat_temp0, &lat_temp1);
    sscanf(GPRMC.longitude, "%3d%2d.%4d", &lon_d, &lon_temp0, &lon_temp1);

    // 保留有效位数
    GPRMC.lat = (double)lat_d + (double)lat_temp0 / 60 + (double)((double)lat_temp1 / 600000);
    GPRMC.lat = floor(GPRMC.lat * 10000000 + 0.5) / 10000000;
    GPRMC.lon = (double)lon_d + (double)lon_temp0 / 60 + (double)((double)lon_temp1 / 600000);
    GPRMC.lon = floor(GPRMC.lon * 10000000 + 0.5) / 10000000;
}

// 解析 $GPRMC 消息
void PARSE_GPRMC(void)
{
    char *subString;
    char *subStringNext;
    char i = 0;
    for (i = 0; i <= 6; i++) // 获取6段数据
    {
        if (i == 0)
        {
            subString = strstr((const char *)USART2_RX_BUF, ","); // 查找逗号
        }
        else
        {
            subString++;                                          // 偏移到逗号后面
            if ((subStringNext = strstr(subString, ",")) != NULL) // 查找下一个逗号
            {
                switch (i)
                {
                case 1:
                    memcpy(GPRMC.UTCtime, subString, subStringNext - subString); // 获取UTC时间
                    break;
                case 2:
                    memcpy(GPRMC.GPS_sta, subString, subStringNext - subString); // 获取定位状态，A=有效定位，V=无效定位
                    break;
                case 3:
                    memcpy(GPRMC.latitude, subString, subStringNext - subString); // 获取纬度信息(度分)
                    break;
                case 4:
                    memcpy(GPRMC.latitudeHemi, subString, subStringNext - subString); // 获取纬度半球(N/S)
                    break;
                case 5:
                    memcpy(GPRMC.longitude, subString, subStringNext - subString); // 获取经度信息(度分)
                    break;
                case 6:
                    memcpy(GPRMC.longitudeHemi, subString, subStringNext - subString); // 获取经度半球(E/W)
                    break;
                default:
                    break;
                }
                subString = subStringNext;
            }
        }
    }
    Parse_UTCTime();                    // 解析UTC时间
    Parse_gps_data();                   // 解析经纬度
    printf1("Time:%s\r\n", GPRMC.Time); // 打印UTC时间
    printf1("lat:%f\r\n", GPRMC.lat);   // 打印纬度信息(度分)
    printf1("lon:%f\r\n", GPRMC.lon);   // 打印经度信息(度分)
    latitude = GPRMC.lat;               // 纬度
    longitude = GPRMC.lon;              // 经度
}



// GPS数据解析
void GPS_Analysis(void)
{
    static uint8_t GPS_ENABLE = 0; // GPS使能标志位

		Clear_Buffer();	 
    printf("AT+QGPSGNMEA=\"RMC\"\r\n");              // 发送AT+QGPSGNMEA="RMC"指令 获取GPS数据
    delay_ms(300);                                   // 延时300ms
    strx = strstr((const char *)RxBuffer, (const char *)"OK");
    printf1(">--EC20-->> AT+QGPSGNMEA=\"RMC\"\r\n"); // 发送AT+QGPSGNMEA="RMC"指令 获取GPS数据
    delay_ms(100);                                   // 延时100ms
    printf1("<--EC20--<< \r\n");
    printf1(" %s\r\n", RxBuffer);
    USART2_RX_STA = 0;
    if (strx != NULL)
    {
        GPS_ENABLE = 0; // GPS使能
                        // 如果接收到完整的 $GPRMC 消息
        if (strstr((const char *)RxBuffer, "$GPRMC") != NULL && strchr((const char *)RxBuffer, '\n') != NULL)
        {
            // 解析消息
            PARSE_GPRMC();
        }
    }
    else
    {
        if (ENABLE > 6)
        {
            printf1(">--printf1-->> GPS重启\r\n");           // 重启成功
						Clear_Buffer();	 
            printf("AT+QGPSEND\r\n");                        // 发送AT+QGPSEND指令 关闭GPS
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf1(">--EC20-->> AT+QGPSEND\r\n"); // 发送AT+QGPSEND指令 关闭GPS
            delay_ms(100);                         // 延时100ms
            printf1("<--EC20--<< \r\n");
            printf1(" %s\r\n", RxBuffer);
            USART2_RX_STA = 0;
						Clear_Buffer();	 
            printf("AT+QGPS=0\r\n");                         // 发送AT+QGPS=0指令 关闭GPS
            delay_ms(300);                                   // 延时300ms
            /* GPS重启 */
						Clear_Buffer();	 
            printf("AT+QGPS=1\r\n");                         // 发送AT+QGPS=1指令 打开GPS
            delay_ms(300);                                   // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            printf("AT+QGPSCFG=\"gpsnmeatype\",1\r\n"); // 发送AT+QGPSCFG="gpsnmeatype",1指令 设置GPS输出数据格式为GGA
            delay_ms(300);                              // 延时300ms
            strx = strstr((const char *)RxBuffer, (const char *)"OK");
            if (strx != NULL)
            {
                printf1(">--printf1-->> GPS重启成功\r\n"); // 重启成功
            }
            else
            {
                printf1(">--printf1-->> GPS重启失败\r\n"); // 重启失败
            }
        }
        printf1(">--printf1-->> GPS数据正在加载,请稍后...\r\n"); // 重启成功
    }
    GPS_ENABLE++; // GPS使能标志位自增

}

