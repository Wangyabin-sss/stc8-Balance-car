#ifndef _iic_H
#define _iic_H

#include "delay.h"


/**********************
引脚别名定义
***********************/	
sbit   SCL=P0^0;			//IIC时钟引脚定义
sbit   SDA=P0^1;			//IIC数据引脚定义



void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(bit ack);
bit I2C_RecvACK(void);
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(bit n);  //0ack 1nack

#endif




