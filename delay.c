#include "delay.h"


void delay_us(u16 us)//@24MHz
{
	u16 i;
	for(i=0;i<us;i++)
	{
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();
	}
	
}


void delay_ms(u16 ms)
{
	u16 m;
	for(m=0;m<ms;m++)
	{
		delay_us(1000);
	}
	
}
