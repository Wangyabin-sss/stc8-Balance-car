#ifndef _speed_H
#define _speed_H


#include "delay.h"
#include "PID.h"

extern int number[2];
/*
INT0--P32   上升沿与下降沿
INT1--P33		上升沿与下降沿
INT2--P36		仅下降沿
INT3--P37		仅下降沿
INT4--P30		仅下降沿
*/

#define  Ps  160.0
#define  Is  0.95


void INT_init(void);
int speed_pwm(void);
int velocity(int encoder_left,int encoder_right);


#endif


