/*
 * EXT.h
 *
 * Created: 9/15/2023 5:31:35 PM
 *  Author: 20100
 */ 


#ifndef EXT._INTERRUPT_H_
#define EXT._INTERRUPT_H_

#include "DIO_driver.h"
#include "MACROS.h"
#include <avr/io.h>
#include <avr/interrupt.h>


#define INT0_PIN		 2
#define INT1_PIN		 3
#define INT_0_1_PORT	'D'


void INT0_vInit(void);
void INT1_vInit(void);

#endif /* EXT._INTERRUPT_H_ */