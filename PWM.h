#ifndef _PWM_H
#define _PWM_H


#include "stc8.h"
#include "GPIO.h"

#define PWM_Pin_1 P20  //定时器输出PWM引脚定义，修改后要初始化相应引脚为推挽输出（在Timer_PWM_init里）
#define PWM_Pin_2 P27


/*---------比较值--------------*/
extern int occ;//定时器0输出PWM
extern int val0,val1;//15位增强型PWM，对应引脚为P20,P21


void Timer_PWM_init(void);//定时器PWM初始化
void PWM_init(void);//15位PWM初始化


#endif

