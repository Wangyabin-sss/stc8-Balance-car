#include "iic.h"


//*************************************************************************************************
//I2C起始信号
//*************************************************************************************************
void I2C_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay_us(5);                 //延时
    SDA = 0;                    //产生下降沿
    delay_us(5);                 //延时
    SCL = 0;                    //拉低时钟线
}
//*************************************************************************************************
//I2C停止信号
//*************************************************************************************************
void I2C_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    delay_us(5);                 //延时
    SDA = 1;                    //产生上升沿
    delay_us(5);                 //延时
}
//**************************************************************************************************
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
//**************************************************************************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay_us(5);                 //延时
    SCL = 0;                    //拉低时钟线
    delay_us(5);                 //延时
}
//****************************************************************************************************
//I2C接收应答信号
//****************************************************************************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    delay_us(5);                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    delay_us(5);                 //延时
    return CY;
}
//*****************************************************************************************************
//向I2C总线发送一个字节数据
//*****************************************************************************************************
void I2C_SendByte(u8 dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        delay_us(5);             //延时
        SCL = 0;                //拉低时钟线
        delay_us(5);             //延时
    }
    I2C_RecvACK();
}
//*****************************************************************************************************
//从I2C总线接收一个字节数据
//******************************************************************************************************
u8 I2C_RecvByte(bit n)
{
    u8 i;
    u8 dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        delay_us(5);             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        delay_us(5);             //延时
    }
    I2C_SendACK(n);//发送nACK  or  ACK   
    return dat;
}


/*********************************END FILE*************************************/


