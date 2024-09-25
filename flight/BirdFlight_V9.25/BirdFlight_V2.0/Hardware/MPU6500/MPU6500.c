/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者 	:Xiluna Tech
 * 文件名 :MPU6500.c
 * 描述   :MPU6500初始化配置文件
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/

#include "MPU6500.h"
#include "explore_systick.h"

#define Buf_SIZE  10	  

int16_t  MPU6500_FIFO[7][Buf_SIZE];
uint8_t Gyro_Off_started = 0;
int16_t lastAx,lastAy,lastAz,
		lastGx,lastGy,lastGz;
static int16_t Gx_offset=0,Gy_offset=0,Gz_offset=0;


static void MPU6500_writeReg(u8 reg, u8 data)
{
	MPU6500_CSL();
	SPI3_ReadWrite_Byte(reg);
	SPI3_ReadWrite_Byte(data);
	MPU6500_CSH();	
}

void MPU6500_initialize(void)
{     
	
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x80);           // 复位
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_SIGNAL_PATH_RESET,0x07);
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x03);           // 使用内部20M时钟
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_SMPLRT_DIV,0x00);           // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_ACCEL_CONFIG,0x10);         // +-8G accel
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_FF_THR,0x04);               // 加计低通滤波器  20Hz
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_GYRO_CONFIG,0x18);          // +-2000 gyro
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_CONFIG, 0x03);              // 内部低通巴特沃斯滤波器  截止频率 176Hz
		delay_ms(20);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_2,0x00);
		delay_ms(20);
}


void MPU6500_readGyro_Acc(int16_t *gyro,int16_t *acc)
{
	static u8 buf[14];
	static int16_t gx,gy,gz;
	static int16_t ax,ay,az;
	MPU6500_CSL();
	SPI3_readRegs(MPU6500_RA_ACCEL_XOUT_H,14,buf);
	MPU6500_CSH();
	//acc
	ax = 	(int16_t)(((int16_t)buf[0]) << 8 | buf[1]);
	ay = 	(int16_t)(((int16_t)buf[2]) << 8 | buf[3]);
	az = 	(int16_t)(((int16_t)buf[4]) << 8 | buf[5]);
	//temp
//	MPU6500_NewVal(&MPU6500_FIFO[3][0],(int16_t)(((int16_t)buf[6]) << 8 | buf[7]));
	//gyro
//	MPU6500_NewVal(&MPU6500_FIFO[4][0],(int16_t)(((int16_t)buf[8]) << 8 | buf[9]));
//	MPU6500_NewVal(&MPU6500_FIFO[5][0],(int16_t)(((int16_t)buf[10]) << 8 | buf[11]));
//	MPU6500_NewVal(&MPU6500_FIFO[6][0],(int16_t)(((int16_t)buf[12]) << 8 | buf[13]));
	

	
	gx =  (int16_t)(((int16_t)buf[8]) << 8 | buf[9]);
  gy =  (int16_t)(((int16_t)buf[10]) << 8 | buf[11]);
  gz =  (int16_t)(((int16_t)buf[12]) << 8 | buf[13]);
	
	gyro[0] = gx - Gx_offset;	//gyro
	gyro[1] = gy - Gy_offset;
	gyro[2] = gz - Gz_offset;
	
				
	acc[0] = ax; //acc
	acc[1] = ay;
	acc[2] = az;	
}



void MPU6500_Init_Offset(void)
{
	  unsigned int i;
    int16_t temp[3],temp2[3];
    int32_t tempgx=0,tempgy=0,tempgz=0;
    Gx_offset=0;
    Gy_offset=0;
    Gz_offset=0;

    for(i=0;i<5000;i++){
        delay_us(200);
        MPU6500_readGyro_Acc(temp,temp2);
        tempgx += temp[0];
        tempgy += temp[1];
        tempgz += temp[2];

    }
    Gx_offset=tempgx/5000;
    Gy_offset=tempgy/5000;
    Gz_offset=tempgz/5000;
}


//------------------End of File----------------------------

