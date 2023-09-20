/*
 * EXT.c
 *
 * Created: 9/15/2023 5:31:26 PM
 *  Author: 20100
 */ 
#include "EXT._Interrupt.h"

void INT0_vInit(void)
{	
	sei();	//enable I-bit
	
	DIO_set_PINDir(INT_0_1_PORT,INT0_PIN,0);//set int0 pin input
	
	SET_BIT(MCUCR,ISC00);		//go to ISR when sensing rising edge on int0 pin
	SET_BIT(MCUCR,ISC01);
	
	SET_BIT(GICR,INT0);
}

void INT1_vInit(void)
{
	sei();
	
	DIO_set_PINDir(INT_0_1_PORT,INT1_PIN,0);
	
	SET_BIT(MCUCR,ISC00);		//go to ISR when sensing rising edge on int1 pin
	SET_BIT(MCUCR,ISC01);
	
	SET_BIT(GICR,INT1);
}