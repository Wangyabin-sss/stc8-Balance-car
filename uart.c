#include "uart.h"

void Uart1_Init(void) //使用定时器2做波特率发生器
{		
	GPIO_init(GPIO_P3,GPIO_Pin_0,GPIO_PullUp);//设置P3.0为准双向口
	GPIO_init(GPIO_P3,GPIO_Pin_1,GPIO_OUT_PP);//设置P3.1为推挽输出
	
	SCON = 0x50;
	T2L = 0xcc;		//115200
	T2H = 0xff;
	AUXR = 0x15;		//启动定时器2
	ES = 1;				//使能串口中断
	EA = 1;
}

void U1SendData(u8 ch)
{
		
    SBUF = ch;                  //写数据到UART数据寄存器
		while(TI == 0);             //在停止位没有发送时，TI为0即一直等待
		TI = 0;  	//清除TI位（该位必须软件清零）
		
}

void UartSendStr(u8 *p)
{
	while (*p)
	{
		U1SendData(*p++);
	}
}

void UART1_Isr() interrupt 4
{
	if (TI)
	{
		TI = 0;//清中断标志
	}
	if (RI)
	{
		RI = 0;//清中断标志
	}
}


char putchar(char c)
{
	ES=0;
	U1SendData(c);
	ES=1;
	return c;
}
	























