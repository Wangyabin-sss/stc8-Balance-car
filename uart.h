#ifndef _uart_H
#define _uart_H

#include "stc8.h"
#include "delay.h"
#include "stdio.h"
#include "GPIO.h"

void Uart1_Init(void);
void U1SendData(u8 ch);
void UartSendStr(u8 *p);


#endif


