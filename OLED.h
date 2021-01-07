#ifndef _OLED_H
#define _OLED_H


#include "delay.h"
#include "speed.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define Max_Column	128
#define SIZE	16



sbit OLED_CS=P0^3; //片选
sbit OLED_RST =P0^5;//复位
sbit OLED_DC =P0^4;//数据/命令控制
sbit OLED_SCL=P0^7;//时钟 D0（SCLK)
sbit OLED_SDIN=P0^6;//D1（MOSI） 数据


#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;


void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y,u8 *chr);
void OLED_Init(void);
void timer1_init(void);

#endif