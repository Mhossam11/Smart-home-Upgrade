/*
 * Slave_B.c
 *
 * Created: 9/5/2023 12:26:01 AM
 *  Author: 20100
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000Ul		//Micro controller Freq
#include <util/delay.h>		//used for delay


#include "SPI_driver.h"
#include "LED_driver.h"
#include "Timer_driver.h"
#include "MOTORS.h"
#include "Communication_Messages.h"
#include "Slave_main_Macros.h"
#include "ADC_driver.h"

volatile char counter=0;							//counter count ticks of Timer
volatile char Temp_user_set=24;						//variable take the value of tempreature from the user
volatile char Temp_ADC_READ=0;						//variable take LM35 sensor reading
volatile char LAST_AIR_COND_STATUS=AIR_COND_IS_OFF;		//variable take LM35 sensor reading
int main(void)
{
	/*************INITILIZATION***********/
	ADC_vInit();								//INITIALIZE ADC
	SPI_SlaveInit();
	
	DC_Motor_vInit(AIR_COND_PORT,AIR_COND_PIN);//INITIALIZE motor
	
	LED_vInit(ROOMS_PORT,ROOM1_PIN);			//INITIALIZE ROOM1
	LED_vInit(ROOMS_PORT,ROOM2_PIN);			//INITIALIZE ROOM2
	LED_vInit(ROOMS_PORT,ROOM3_PIN);			//INITIALIZE ROOM3
	LED_vInit(ROOMS_PORT,ROOM4_PIN);			//INITIALIZE ROOM4
	LED_vInit(ROOMS_PORT,TV_PIN);				//INITIALIZE ROOM4
	_delay_ms(500);
	/*************************************/
	/****************variables****************/
	unsigned char Send=DUMMY_DATA;
	unsigned char Receive=DUMMY_DATA;
	

	/*****************************************/
    while(1)
    {
		Receive=SPI_SlaveReceiverchar(DUMMY_DATA);//take order from master
		
		switch(Receive)
		{
			/****************slave ask for the status of room********************/
			case ROOM1_STATUS:
				if(LED_u8Read(ROOMS_PORT,ROOM1_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(LED_u8Read(ROOMS_PORT,ROOM1_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;
			
			case ROOM2_STATUS:
				if(LED_u8Read(ROOMS_PORT,ROOM2_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(LED_u8Read(ROOMS_PORT,ROOM2_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;
			
			case ROOM3_STATUS:
				if(LED_u8Read(ROOMS_PORT,ROOM3_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(LED_u8Read(ROOMS_PORT,ROOM3_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;
			
			case ROOM4_STATUS:
				if(LED_u8Read(ROOMS_PORT,ROOM4_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(LED_u8Read(ROOMS_PORT,ROOM4_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;
			
			case TV_STATUS:
				if(LED_u8Read(ROOMS_PORT,TV_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(LED_u8Read(ROOMS_PORT,TV_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;	
			
			case AIR_COND_STATUS:
				if(DC_Motor_u8Read(AIR_COND_PORT,AIR_COND_PIN)==1)
				{
					Send=ON_STATUS;
				}
				else if(DC_Motor_u8Read(AIR_COND_PORT,AIR_COND_PIN)==0)
				{
					Send=OFF_STATUS;
				}
				SPI_SlaveReceiverchar(Send);
			break;
			/****************slave ask for the status of room********************/
			
			/****************slave ask to on a room********************/
			case ROOM1_TURN_ON:
				LED_vTurnOn(ROOMS_PORT,ROOM1_PIN);
			break;
			
			case ROOM2_TURN_ON:
				LED_vTurnOn(ROOMS_PORT,ROOM2_PIN);
			break;
			
			case ROOM3_TURN_ON:
				LED_vTurnOn(ROOMS_PORT,ROOM3_PIN);
			break;
			
			case ROOM4_TURN_ON:
				LED_vTurnOn(ROOMS_PORT,ROOM4_PIN);
			break;
			
			case TV_TURN_ON:
				LED_vTurnOn(ROOMS_PORT,TV_PIN);
			break;	
			
			case AIR_COND_TURN_ON:
				Timer_CTC_Init_interrupt();
				DC_Motor_Start(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
			break;
			/*********************************************************/
			
			/****************slave ask to off a room********************/
				case ROOM1_TURN_OFF:
					LED_vTurnOFF(ROOMS_PORT,ROOM1_PIN);
				break;
				
				case ROOM2_TURN_OFF:
					LED_vTurnOFF(ROOMS_PORT,ROOM2_PIN);
				break;
				
				case ROOM3_TURN_OFF:
					LED_vTurnOFF(ROOMS_PORT,ROOM3_PIN);
				break;
				
				case ROOM4_TURN_OFF:
					LED_vTurnOFF(ROOMS_PORT,ROOM4_PIN);
				break;
				
				case TV_TURN_OFF:
					LED_vTurnOFF(ROOMS_PORT,TV_PIN);
				break;
				
				case AIR_COND_TURN_OFF:
					Timer_CTC_Stop();
					DC_Motor_Stop(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
				break;
				
				case SET_TEMP:
					Temp_user_set=SPI_SlaveReceiverchar(DUMMY_DATA);
				break;
				/**********************************************************************/
		}
		
    }
}

ISR(TIMER0_COMP_vect)
{
	counter++;
	if(counter>=10)
	{
		counter=0;
		Temp_ADC_READ=(0.25*ADC_u16Read());
		if(Temp_ADC_READ>=(Temp_user_set+1))
		{
			DC_Motor_Start(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
			LAST_AIR_COND_STATUS=AIR_COND_IS_ON;
		}
		else if(Temp_ADC_READ<=(Temp_user_set-1))
		{
			DC_Motor_Stop(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
			LAST_AIR_COND_STATUS=AIR_COND_IS_OFF;
		}
		else if(Temp_ADC_READ==Temp_user_set)
		{
			if(LAST_AIR_COND_STATUS==AIR_COND_IS_ON)
			{
				DC_Motor_Start(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
			}
			else if(LAST_AIR_COND_STATUS==AIR_COND_IS_OFF)
			{
				DC_Motor_Stop(AIR_COND_PORT,AIR_COND_PIN,AIR_COND_EN_PIN);
			}
		}
	}	
}