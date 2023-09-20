/*
 * UART_driver.h
 *
 * Created: 8/6/2023 8:19:15 PM
 *  Author: 20100
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <avr/io.h>
#define F_CPU 8000000Ul
#include <util/delay.h>

#include "MACROS.h"

void UART_vInit(unsigned long Baud);

void UART_vSendData(char data);

int UART_u8ReceiveData(void);

void UART_vSendString(char *ptr);




#endif /* UART_DRIVER_H_ */