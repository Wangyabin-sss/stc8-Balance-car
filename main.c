#include "uart.h"
#include "MPU6050.h"
#include "PID.h"
#include "GPIO.h"
#include "PWM.h"
#include "OLED.h"
#include "speed.h"

/*------------已使用的硬件资源--避免重复使用-----------

定时器0中断做PWM发生器
定时器1中断做OLED显示
定时器2做波特率发生器
外部中断P32、P33、P36、P37做编码器测速

引脚：IIC--SCL=P00，SDA=P01
			定时器PWM--P04 硬件PWM--P20与P21
			电机控制引脚--AIN1 = P2^3;
										AIN2 = P2^1;
										BIN1 = P2^5;
										BIN2 = P2^6;
										STBY = P2^4;
										
			OLED引脚--OLED_CS=P0^3; //片选
								OLED_RST =P0^5;//复位
								OLED_DC =P0^4;//数据/命令控制
								OLED_SCL=P0^7;//时钟 D0（SCLK)
								OLED_SDIN=P0^6;//D1（MOSI） 数据
*/


void Systeminit(void)
{
	P_SW2 = 0x80;
  XOSCCR = 0xc0;			//启动外部晶振
  while (!(XOSCCR & 1));//等待时钟稳定
  CLKDIV = 0x00;			//时钟不分频
  CKSEL = 0x01;			//选择外部晶振
  P_SW2 = 0x00;
}



void main()
{
	int PWM=0;
	float angle=0,a_angle=0,g_speed=0;

	Systeminit();  //使用外部晶振
	delay_ms(10);
//	P2M0 = 0xff;//设置 P2.0~P2.7 为推挽输出模式
//  P2M1 = 0x00;
//	P0M0 = 0xff;//设置 P0.0~P0.7 为推挽输出模式
//  P0M1 = 0x00;
	
//	OLED_Init();  //OLED初始化
	delay_ms(10);
	InitMPU6050(); //mpu6050初始化
	delay_ms(10);
	Uart1_Init();  //串口初始化
	delay_ms(10);
//	Timer_PWM_init();
	PWM_init();   //硬件PWM初始化
	delay_ms(10);
	INT_init();
	delay_ms(10);

	
	while(1)
	{	P55=0;
		
		a_angle=-A_angle();
		g_speed=G_speed();
		angle=Kalman_Filter(a_angle,g_speed)-0.78;
//		angle=angle_average(a_angle);
//		yijielvbo(a_angle,&angle,g_speed);
		
//		printf("%f—%f—%f\n",angle,a_angle,g_speed);
		
//		PWM=PID_PWM(angle,g_speed);
		PWM=PID_PWM(angle,g_speed)+speed_pwm();  //pid_pwm有正负 speed_pwm也要有正负
//		PWM=speed_pwm();
//		PWM=PID_PWM(angle,g_speed)+velocity(number[0],number[1]);
//		PWM=velocity(number[0],number[1]);
		
//		occ=PWM;
		val1=val0=PWM;
		
		Motor_control(PWM,angle);
		
		delay_ms(8);
		
	}
	
	
}







