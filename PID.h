#ifndef _PID_H
#define _PID_H

#include "MPU6050.h"

extern bit motor_direction;

#define P 1320
#define D 38
sbit AIN1 = P2^3;
sbit AIN2 = P2^1;
sbit BIN1 = P2^5;
sbit BIN2 = P2^6;
sbit STBY = P2^4;


float Kalman_Filter(float angle_m, float gyro_m);//angleAx 和 gyroGy  卡尔曼滤波
float angle_average(float a_angle); //平均值滤波
void yijielvbo(float a_angle,float *angle,float g_speed);  //一阶滤波
float A_angle(void); //加速度计计算角度
float G_speed(void); //陀螺仪计算角度
int PID_PWM(float a_angle,float acc);//传入滤波后角度，陀螺仪角速度
void Motor_control(int pwm,float a_angle);



#endif