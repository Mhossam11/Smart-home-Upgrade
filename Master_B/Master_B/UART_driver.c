/*
 * UART_driver.c
 *
 * Created: 8/6/2023 8:19:01 PM
 *  Author: 20100
 */ 
#include "UART_driver.h"

void UART_vInit(unsigned long Baud)
{
	unsigned short UBRR;
	UBRR=(F_CPU/(16*Baud))-1;				//equation of asynchronous normal mode 
	
	UBRRH=(unsigned char)(UBRR>>8);		//high byte of ubrr value
	UBRRL=(unsigned char)(UBRR);		//low byte of ubrr value
	
	SET_BIT(UCSRB,TXEN);				//enable transmiter
	SET_BIT(UCSRB,RXEN);				//enable receiver
	
	UCSRC=0x86;										//set URSEL=1 to access UCSRC,set UCSZ1 and UCSZ0  useful data 8-bit
	//UCSRC|=(1<<8)|(1<<2)|(1<<1);
}


void UART_vSendData(char data)
{
	while(READ_BIT(UCSRA,UDRE)==0);			//wait tol ma howa msh empty
	UDR=data;								//put the data in transmitter buffer
}


int UART_u8ReceiveData(void)
{
	while(READ_BIT(UCSRA,RXC)==0);			//wait until receiving complete
	return UDR;
}

void UART_vSendString(char *ptr)
{
	while(*ptr!=0)							//tol ma howa msh be null yb3t 7rf 7rf bltarteb
	{
		UART_vSendData(*ptr);
		ptr++;
		_delay_ms(100);
	}
}
