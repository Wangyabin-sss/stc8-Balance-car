#include "speed.h"

int number[2]={0,0};

void INT_init()
{
	IT0 = 0;//使能 INT0 上升沿和下降沿中断
	EX0 = 1;//使能 INT0 中断
	
	IT1 = 0;//使能 INT1 上升沿和下降沿中断
	EX1 = 1;//使能 INT1 中断
	
//	INTCLKO = EX2;//使能 INT2 下降沿中断
//	
//	INTCLKO |= EX3;//使能 INT3 下降沿中断
	
	EA = 1;
	
}


void INT0_Isr() interrupt 0  //INT0--P32电机1-A相
{
	
		if(motor_direction==1)
		{
			number[0]+=1;
		}
		else
		{
			number[0]-=1;
		}
	
}

void INT1_Isr() interrupt 2  //INT1--P33电机2-A相
{

		if(motor_direction==1)
		{
			number[1]+=1;
		}
		else
		{
			number[1]-=1;
		}
		
}

//void INT2_Isr() interrupt 10  //INT2--P36电机1-B相
//{
////		if(P32==1)
////		{
//			number[0]+=1;
////		}
////		else
////		{
////			number[0]-=1;
////		}
////		
//}

//void INT3_Isr() interrupt 11  //INT3--P37电机2-B相
//{
////		if(P33==0)
////		{
//			number[1]+=1;
////		}
////		else
////		{
////			number[1]-=1;
////		}
////		
//}

int speed_pwm()
{
	static float speed=0,position=0,spwm=0;
	static float speed_r=0;
	
	speed_r =(float)(number[0] + number[1])*0.8;
	number[0] = number[1] = 0;
	speed *= 0.8;	    		 //上一次的     //车轮速度滤波
	speed += speed_r*0.4;
	position += speed;               //积分得到位移
	
	if(position>3500)  position=3500;          //===积分限幅
	if(position<-3500)	position=-3500;         //===积分限幅
	
	spwm = Is*position + Ps*speed;   //PID：速度和位置
	
	return spwm;

	
}


int velocity(int Encoder_Left,int Encoder_Right)
{  
	static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral;
	float kp=8,ki=0.04;
	//=============速度PI控制器=======================//	
	Encoder_Least =(Encoder_Left+Encoder_Right)-0;  //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
	Encoder *= 0.7;		                         //===一阶低通滤波器       
	Encoder += Encoder_Least*0.3;	             //===一阶低通滤波器    
	Encoder_Integral +=Encoder;                                     //===积分出位移 积分时间：10ms
	Encoder_Integral=Encoder_Integral-Movement;                     //===接收遥控器数据，控制前进后退
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;          //===积分限幅
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;         //===积分限幅	
	Velocity=Encoder*kp+Encoder_Integral*ki; //===速度控制	

	return Velocity;
}


