#include "oled.h"
#include "oledfont.h"
#include "type.h"

//IIC启动
void IIC_Start()
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

//IIC停止
void IIC_Stop()
{
    OLED_SCLK_Set() ;
//  OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void IIC_Wait_Ack()
{
    OLED_SCLK_Set() ;   //P3OUT|=BIT5
    OLED_SCLK_Clr();    //P3OUT&=~BIT5
}

// IIC Write byte
//IIC写入字节
void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;

    da=IIC_Byte;
    OLED_SCLK_Clr();    //P3OUT &= ~BIT5

    for(i=0;i<8;i++)
    {
        m=da;
        //  OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80)
        {
            OLED_SDIN_Set();    //P3OUT |= BIT6
        }
        else OLED_SDIN_Clr();   //P3OUT &= ~BIT6
            da=da<<1;

        OLED_SCLK_Set();    //P3OUT |= BIT5
        OLED_SCLK_Clr();    //P3OUT &= ~BIT5
    }
}

// IIC Write Command
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x00);            //write command
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
   IIC_Stop();
}

// IIC Write Data
void Write_IIC_Data(unsigned char IIC_Data)
{
    IIC_Start();
    Write_IIC_Byte(0x78);            //D/C#=0; R/W#=0
    IIC_Wait_Ack();
    Write_IIC_Byte(0x40);            //write data
    IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
    IIC_Stop();
}

//OLED写入字节
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
        Write_IIC_Data(dat);        //IIC，  数据
    else
        Write_IIC_Command(dat);     //IIC，命令
}

//填充图片
void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WR_Byte(0xb0+m,0);     //page0-page1
        OLED_WR_Byte(0x00,0);       //low column start address，低八位
        OLED_WR_Byte(0x10,0);       //high column start address，高八位

        for(n=0;n<128;n++)
            OLED_WR_Byte(fill_Data,1);
    }
}

// 延时，单位：ms
void Delay_1ms(unsigned int Del_1ms)
{
    unsigned char j;
    while(Del_1ms--)
    {
        for(j=0;j<123;j++);
    }
}

//OLED设置位置
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//OLED显示开启
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

// OLED显示关闭
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

// OLED清屏
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0;i<8;i++)    //y = 8 清屏y轴的8行
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD); //0111 0000 + i ，选中清屏的行
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);   //0001 0000
        for(n=0;n<128;n++)              //x = 128 清屏x轴的128列
            OLED_WR_Byte(0,OLED_DATA);
    }
}

//OLED开启
void OLED_On(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

/*
x:0~127    y:0~63    size:16/12
显示字符
OLED_ShowChar(0,0,'D',20);//只能显示单个字符
*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
    unsigned char c = 0,i = 0;
    c = chr-' ';

    if(x > Max_Column - 1)
    {
        x = 0;y = y+2;
    }

    if(Char_Size ==16)
    {
        OLED_Set_Pos(x,y);
        for(i = 0; i < 8; i++)
        OLED_WR_Byte( F8X16[c*16+i], OLED_DATA);
        OLED_Set_Pos(x,y+1);
        OLED_WR_Byte( F8X16[c*16+i+8], OLED_DATA);
    }

    else
    {
        OLED_Set_Pos(x,y);
        for(i = 0; i < 6; i++)
            OLED_WR_Byte(F6x8[c][i], OLED_DATA);
    }
}

/*
 * 求m的n次方
 * result = m * m * m * m....
 */
u32 oled_pow(u8 m,u8 n)
{
    u32 result = 1;
    while(n--) result *= m;
    return result;
}

/*
显示数字
x:行    y:列    num:要显示的数字    len:数字位数    size2:每一个数字的间隔
OLED_ShowNum(0,1,1234,4,8);
num的数字可以定义为变量，例：OLED_ShowNum(0,1,date,4,8);
*/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{
    u8 t,temp;
    u8 enshow = 0;
    for(t = 0; t < len; t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+size2*t,y,' ',size2);
                continue;
            }
            else
                enshow=1;
        }
        OLED_ShowChar(x+size2*t,y,temp+'0',size2);
    }
}

//根据具体使用情况修改
void OLED_ShowVI(u8 x,u8 y,u32 num,u8 size2)
{
    OLED_ShowNum( x+size2*4-1, y, num%10, 1, size2);
    OLED_ShowNum( x+size2*3-1, y, num/10%10, 1, size2);
    OLED_ShowNum( x+size2*2-1, y, num/100%10, 1, size2);
    OLED_ShowString( x+size2*1-1, y, ".", size2);
    OLED_ShowNum( x-1,y, num/1000, 1, size2);
}

//显示字符串
//OLED_ShowString(0,4,"DZCXXH",8);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {
        OLED_ShowChar(x,y,chr[j],Char_Size);
        x+=8;
        if(x>120)
        {
            x=0;
            y+=2;
        }
        j++;
    }
}

//显示汉字
//使用：OLED_ShowCHinese(0,4,0);    //"电"
//x：行    y：列    no:数组中第几个汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{
    u8 t,adder=0;
    OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(LHR[2*no][t],OLED_DATA);
        adder+=1;
    }
    OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(LHR[2*no+1][t],OLED_DATA);
        adder+=1;
      }
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;

    if(y1%8==0)
        y=y1%8;
    else
        y=y1%8+1;

    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

//OLED初始化模块
void OLED_Init(void)
{
    //若使用其他端口，这里要修改为对应端口
    P6DIR |= BIT3+BIT6;             //设置为输出

    OLED_WR_Byte(0xAE,OLED_CMD);    //显示关闭
    OLED_WR_Byte(0x00,OLED_CMD);    //设置低列地址
    OLED_WR_Byte(0x10,OLED_CMD);    //设置高位列地址
    OLED_WR_Byte(0x40,OLED_CMD);    //设置起始行地址
    OLED_WR_Byte(0xB0,OLED_CMD);    //设置页面地址
    OLED_WR_Byte(0x81,OLED_CMD);    //联合控制
    OLED_WR_Byte(0xFF,OLED_CMD);    //128
    OLED_WR_Byte(0xA1,OLED_CMD);    //设置段重映射
    OLED_WR_Byte(0xA6,OLED_CMD);    //--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);    //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);    //--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);    //Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);    //-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);

    OLED_WR_Byte(0xD5,OLED_CMD);    //set osc division
    OLED_WR_Byte(0x80,OLED_CMD);

    OLED_WR_Byte(0xD8,OLED_CMD);    //set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);

    OLED_WR_Byte(0xD9,OLED_CMD);    //Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);

    OLED_WR_Byte(0xDA,OLED_CMD);    //set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);

    OLED_WR_Byte(0xDB,OLED_CMD);    //set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);

    OLED_WR_Byte(0x8D,OLED_CMD);    //set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);

    OLED_WR_Byte(0xAF,OLED_CMD);    //打开oled面板
}

