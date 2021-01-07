#include "PWM.h"

 /*-------定时器PWM相关值-------*/
int time;
int occ;
int time_occ;
/*-------15位硬件PWM相关值---------*/
int val0,val1;

void Timer_PWM_init()
{
	TMOD = 0x00;
	TL0 = 0xec;//计数初值=65536-24Mhz/12分频/(100000)hz=65516
	TH0 = 0xff;
	TR0 = 1;//启动定时器0
	ET0 = 1;//使能定时器中断
	EA = 1;
}

void TM0_Isr() interrupt 1
{
	time+=1;
	if(time==1000)//0.01ms计数一次，计数1000次，频率为100hz
	{
		time=0;
		if(occ>0)  //将occ负值变为正值
		{
			time_occ=occ;
		}
		else
		{
			time_occ=-occ;
		}
	}
	if(time<=time_occ)//占空比=occ/1000%
	{
		PWM_Pin_1=1;
		PWM_Pin_2=1;
	}
	else
	{
		PWM_Pin_1=0;
		PWM_Pin_2=0;
	}
}


void PWM_init()
{
	P_SW2 = 0x80;  
	PWMCKS = 0x0f;  //选择计数器时钟为外部时钟16分频
	PWMC = 0x4e20;  //设置15位pwm计数器计数值为20000
	
	PWM0T1= 0x0000; //计数器值等于T1时，翻转为低电平（T1=T2时忽略T2）
	PWM0T2= 0x0000; //计数器值等于T2时，翻转为高电平（T1=T2时忽略T2）
	PWM0CR= 0x80;   //PWM初始电平为低，输出引脚为P20
	
	PWM7T1= 0x0000; //计数器值等于T1时，翻转为低电平（T1=T2时忽略T2）
	PWM7T2= 0x0000; //计数器值等于T2时，翻转为高电平（T1=T2时忽略T2）
	PWM7CR= 0x80;   //PWM初始电平为低，输出引脚为P27
	
	P_SW2 = 0x00;   
	PWMCR = 0xc0;   //使能PWM波形发生器，PWM计数器立即开始计数
	EA=1;
	
}

void PWM_Isr() interrupt 22
{
	if (PWMCFG & 0x80) 
	{	
		PWMCFG &= ~0x80; //清中断标志位
		_push_(P_SW2);
		P_SW2 |= 0x80;
		
		if(val0>=0)  //val6取绝对值
		{
			PWM0T1 = val0;
		}
		else
		{
			PWM0T1 = -val0;
		}
		
		if(val1>=0)  //val7取绝对值
		{
			PWM7T1 = val1;
		}
		else
		{
			PWM7T1 = -val1;
		}
		
		_pop_(P_SW2);
	}
}






