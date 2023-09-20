/*
 * MOTORS.c
 *
 * Created: 9/8/2023 4:26:00 PM
 *  Author: 20100
 */ 
#include "MOTORS.h"

void DC_Motor_vInit(char portname,char enable_pin)	//enter the first pin of the motor 
{
	DIO_set_PINDir(portname,enable_pin,1);			//Set the direction of IN1 output
	DIO_set_PINDir(portname,(enable_pin+1),1);		//Set the direction of IN2 output
	DIO_set_PINDir(portname,(enable_pin+2),1);		//Set the direction of EN output
}

void DC_Motor_Start(char portname,char pinnumber,char enable_pin)
{
	DIO_Write(portname,pinnumber,1);				//start rotation of motor in the direction the user need
	DIO_Write(portname,enable_pin,1);				//write 1 to enable bit
}

void DC_Motor_Stop(char portname,char pinnumber,char enable_pin)
{
	DIO_Write(portname,pinnumber,0);				//stop rotation of motor in the direction the user need
	DIO_Write(portname,enable_pin,0);				//write 0 to stop enable bit
}

char DC_Motor_u8Read(char portname,char pinnumber)
{
	DIO_u8read(portname,pinnumber);
}