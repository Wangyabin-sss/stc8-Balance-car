#include "PID.h"

bit motor_direction;

//卡尔曼滤波参数与函数

float dt=0.008;//注意：dt的取值为kalman滤波器采样时间
float angle, angle_dot;//角度和角速度
float PP[2][2] = {{ 1, 0 },{ 0, 1 }};
float Pdot[4] ={ 0,0,0,0};
float Q_angle=0.001, Q_gyro=0.005; //角度数据置信度,角速度数据置信度
float R_angle=0.5 ,C_0 = 1;
float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

//卡尔曼滤波

float Kalman_Filter(float angle_m, float gyro_m)//angleAx 和 gyroGy

{
        angle+=(gyro_m-q_bias) * dt;
        angle_err = angle_m - angle;
        Pdot[0]=Q_angle - PP[0][1] - PP[1][0];
        Pdot[1]=- PP[1][1];
        Pdot[2]=- PP[1][1];
        Pdot[3]=Q_gyro;
        PP[0][0] += Pdot[0] * dt;
        PP[0][1] += Pdot[1] * dt;
        PP[1][0] += Pdot[2] * dt;
        PP[1][1] += Pdot[3] * dt;
        PCt_0 = C_0 * PP[0][0];
        PCt_1 = C_0 * PP[1][0];
        E = R_angle + C_0 * PCt_0;
        K_0 = PCt_0 / E;
        K_1 = PCt_1 / E;
        t_0 = PCt_0;
        t_1 = C_0 * PP[0][1];
        PP[0][0] -= K_0 * t_0;
        PP[0][1] -= K_0 * t_1;
        PP[1][0] -= K_1 * t_0;
        PP[1][1] -= K_1 * t_1;
        angle += K_0 * angle_err; //最优角度
        q_bias += K_1 * angle_err;
        angle_dot = gyro_m-q_bias;//最优角速度
        return angle;
}


float angle_average(float a_angle)
{
	u8 i;
	float angle,a[5];
	
	a[0]=a[1];
	a[1]=a[2];
	a[2]=a[3];
	a[3]=a[4];
	a[4]=a_angle;
	
	angle=(a[0]+a[1]+a[2]+a[3]+a[4])/5;
	return angle;
}

void yijielvbo(float a_angle,float *angle,float g_speed)
{
	float k=0.98;
	*angle=(1-k)*a_angle+k*(*angle+g_speed*0.006);
}

float A_angle(void) //加速度计计算角度
{
	int Ax,Az;
	float a,A_angle;
	Ax=GetData(ACCEL_XOUT_H);
	Az=GetData(ACCEL_ZOUT_H);
	a=(float)Ax/Az;
	A_angle=atan(a)*57.3;
	return A_angle;
}

float G_speed(void) //陀螺仪计算角度,传入时间间隔
{
	int Gy;
	float G_speed;
	Gy=GetData(GYRO_YOUT_H);
	G_speed=(float)Gy/16.4;
	return G_speed;
}


int PID_PWM(float angle,float acc)//传入滤波后角度，陀螺仪角速度
{
	int PWM;
	PWM=P*angle+D*acc;
	return PWM;
}

void Motor_control(int pwm,float a_angle)
{
	if(pwm>=0)
	{
		AIN1=0;
		AIN2=1;
		BIN1=1;
		BIN2=0;
		motor_direction=1;
	}
	if(pwm<0)
	{
		AIN1=1;
		AIN2=0;
		BIN1=0;
		BIN2=1;
		motor_direction=0;
	}
	
	if(a_angle>=40||a_angle<=-40)
	{
		STBY=0;
	}
	else
	{
		STBY=1;
	}
}






