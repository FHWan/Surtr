#ifndef UART_H_
#define UART_H_

void UART_Init();            //初始化函数，固定9600bps
void senfchar(char s);
void sendstring(unsigned char *p);

#endif
