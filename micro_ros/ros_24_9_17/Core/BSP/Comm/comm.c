#include "comm.h"
#include "main.h"
extern UART_HandleTypeDef huart1;

uint8 temp = 0;
uint8  USART_RX_BUF[USART_REC_LEN]; 	//接收缓冲
uint16 USART_RX_STA = 0;         			//接收状态
uint8 aRxBuffer[1];			//HAL库USART接收Buffer

uint8 KDCOM_Check(KDRobot* buf)
{
    return '\n';
}

uint8 KDCOM_GetCmd(KDRobot* buf)
{
    return buf->buf[0];
}

uint8 KDCOM_GetCmdPara(KDRobot* buf, uint8 paraNum)
{
    if(paraNum > 3 || paraNum < 1)
        return 0;
    return buf->buf[paraNum];
}

float KDCOM_GetCmdData(KDRobot* buf)
{
    return *(float*)&(buf->buf[4]);
}

float KDCOM_GetData(KDRobot* buf, uint8 dataNum)
{
    if(dataNum > 2 || dataNum < 1)
        return 0;
    return *(float*)&(buf->buf[(dataNum - 1) * 4]);
}

uint8* KDCOM_SetCmd(KDRobot* buf, uint8 cmd, uint8 para1, uint8 para2, uint8 para3, float data)
{
    buf->head = 'C';
    buf->buf[0] = cmd;
    buf->buf[1] = para1;
    buf->buf[2] = para2;
    buf->buf[3] = para3;
    *(float*)&buf->buf[4] = data;
    buf->check = KDCOM_Check(buf);
    return (uint8*)buf;
}

uint8* KDCOM_SetData(KDRobot* buf, uint8 channel, float data1, float data2)
{
    buf->head = '0' + channel;
    *(float*)&buf->buf[0] = data1;
    *(float*)&buf->buf[4] = data2;
    buf->check = KDCOM_Check(buf);
    return (uint8*)buf;
}
//0 finish
//1 error head
//2 check error
// uint8 KDCOM_Process(uint8* buf, uint8 *channel, float (*p)[4], float (*i)[4], float (*d)[4], float (*traget)[4], float (*actual)[4], 
//                     uint8 *start, uint8 *stop, float *data1, float *data2)
uint8 KDCOM_Process(uint8* buf, uint8 *channel, float *p[4], float *i[4], float *d[4], float *traget[4], float *actual[4], 
                    uint8 *start, uint8 *stop, float *data1, float *data2)
{
	KDRobot *kdrobot = (KDRobot*)buf;
    if(KDCOM_Check(kdrobot) == kdrobot->check)
    {
        if(buf[0] == 'D')
        {
            if(data1)
            {
                *data1 = KDCOM_GetData((KDRobot*)buf, 1);
            }
            if(data2)
            {
                *data2 = KDCOM_GetData((KDRobot*)buf, 2);
            }
        }
        else if(buf[0] == 'C')
        {
            switch (buf[1])
            {
            case 1:
                if(buf[2])//p
                {//write 1
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    *(p)[*channel] = KDCOM_GetCmdData(kdrobot);
                }
                else
                {
                    KDRobot kd;//read 0
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    KDCOM_SendData(KDCOM_SetCmd(&kd, 1, 1, 0, 0, *(p)[*channel]), sizeof(KDRobot));
                }
                break;
            case 2:
                if(buf[2])
                {
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    *(i)[*channel] = KDCOM_GetCmdData(kdrobot);
                }
                else
                {
                    KDRobot kd;//read 0
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    KDCOM_SendData(KDCOM_SetCmd(&kd, 2, 1, 0, 0, *(i)[*channel]), sizeof(KDRobot));
                }
                break;
            case 3:
                if(buf[2])
                {
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    *(d)[*channel] = KDCOM_GetCmdData(kdrobot);
                }
                else
                {
                    KDRobot kd;//read 0
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    KDCOM_SendData(KDCOM_SetCmd(&kd, 3, 1, 0, 0, *(d)[*channel]), sizeof(KDRobot));
                }
                break;
            case 4:
                if(buf[2])
                {
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    *(traget)[*channel] = KDCOM_GetCmdData(kdrobot);
                }
                else
                {
                    KDRobot kd;//read 0
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    KDCOM_SendData(KDCOM_SetCmd(&kd, 4, 1, 0, 0, *(traget)[*channel]), sizeof(KDRobot));
                }
                break;
            case 6:
                if(!buf[2])
                {
                    KDRobot kd;//read 0
                    *channel = KDCOM_GetCmdPara(kdrobot, 2);
                    KDCOM_SendData(KDCOM_SetCmd(&kd, 6, 1, 0, 0, *(actual)[*channel]), sizeof(KDRobot));
                }
                break;
            case 7:
                *start = 1;
                break;
            case 8:
                *stop = 1;
                break;
            case 5:
            default:
                break;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 2;
    }
    return 0;
}
