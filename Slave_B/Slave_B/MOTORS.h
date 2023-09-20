/*
 * MOTORS.h
 *
 * Created: 9/8/2023 4:25:39 PM
 *  Author: 20100
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#include "DIO_driver.h"
#include "MACROS.h"

void DC_Motor_vInit(char portname,char enable_pin);	//enter the first pin of the motor 

void DC_Motor_Start(char portname,char pinnumber,char enable_pin);

void DC_Motor_Stop(char portname,char pinnumber,char enable_pin);

char DC_Motor_u8Read(char portname,char pinnumber);





#endif /* MOTORS_H_ */