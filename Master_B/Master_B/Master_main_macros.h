/*
 * Master_main_macros.h
 *
 * Created: 9/5/2023 12:14:16 AM
 *  Author: 20100
 */ 


#ifndef MASTER_MAIN_MACROS_H_
#define MASTER_MAIN_MACROS_H_

/***********************TIME**************************/
#define BLOCK_MODE_TIME			5000		//TIME delay for blocked mode
#define ADMIN_TIME_OUT			1000		//admin session time 30sec
#define GUEST_TIME_OUT			1000		//guest session time
/****************************************************/
/****************PREVENT MAGICAL NUMBERS************/
#define BAUD_RATE				9600	//baud rate used for UART in master and slave

#define MODES_LED_PORTS					'C'		//ALL MODES lED CONNECTED TO PORT C
#define BLOCK_MODE_LED_PIN				0		//PIN CONNECTED TO BLOCK_MODE LED
#define ADMIN_MODE_LED_PIN				1		//PIN CONNECTED TO ADMIN_MODE LED
#define GUEST_MODE_LED_PIN	   			2		//PIN CONNECTED TO GUEST_MODE LED
#define LIVING_ROOM_LED1				3		//pin connected to living room led1
#define LIVING_ROOM_LED2				4		//pin connected to living room led2

#define NOTPRESSED						0xFF	
#define DUMMYDATA						0xFF

#define I_COUNTER						0		//USED FOR LOOPS

#define MAX_PASS_TRIES					3		//MAXIMUM PASSWORD TRIES
#define PASS_SIZE						4		//SIZE OF THE PASSWORD MODE

#define PASS_SYMBOL						'*'		//TO PRINT *
#define DEGREE_SYMBOL					0xDF	//TO PRINT THE DEGREE SYMBOL

#define VARIABLE_TO_GET_ASCII			48		//TO GET ANY ASCII CODE

/***************************************************/

/*************EEPROM LOCATIONS*********************/
#define EEPROM_ADMIN_STATUS_LOCATION	0x20	//STATUS LOCATION TO KNOW IF THE PASSWORD SET BEFOR OR NOT
#define EEPROM_ADMIN_PASS1_LOCATION		0x21	//SAVE 1st NUMBER IN THE ADMIN PASSWORD
#define EEPROM_ADMIN_PASS2_LOCATION		0x22	//SAVE 2nd NUMBER IN THE ADMIN PASSWORD
#define EEPROM_ADMIN_PASS3_LOCATION		0x23	//SAVE 3rd NUMBER IN THE ADMIN PASSWORD
#define EEPROM_ADMIN_PASS4_LOCATION		0x24	//SAVE 4th NUMBER IN THE ADMIN PASSWORD

#define EEPROM_GUEST_STATUS_LOCATION	0x30	//STATUS LOCATION TO KNOW IF THE PASSWORD SET BEFOR OR NOT
#define EEPROM_GUEST_PASS1_LOCATION		0x31	//SAVE 1st NUMBER IN THE ADMIN PASSWORD
#define EEPROM_GUEST_PASS2_LOCATION		0x32	//SAVE 2nd NUMBER IN THE ADMIN PASSWORD
#define EEPROM_GUEST_PASS3_LOCATION		0x33	//SAVE 3rd NUMBER IN THE ADMIN PASSWORD
#define EEPROM_GUEST_PASS4_LOCATION		0x34	//SAVE 4th NUMBER IN THE ADMIN PASSWORD
/**************************************************/

/******************USER MODES**********************/
#define  NO_MODE						0
#define  ADMIN_MODE						1
#define  GUEST_MODE						2

#define CHECK_ADMIN_MODE			   '1'
#define CHECK_GUEST_MODE			   '2'

/**************************************************/

/*********************LOGIC************************/
#define TRUE							1
#define FALSE							0
/**************************************************/

/***********************MENU**********************/
//THEY ARE USED IN => SWITCH(SHOW_MENU)
#define MAIN_MENU						1
#define MORE_MENU						2
#define ROOM1_MENU						3
#define ROOM2_MENU						4
#define ROOM3_MENU						5
#define ROOM4_MENU						6
#define TV_MENU							7
#define AIR_COND_MENU					8
#define AIR_COND_CTRL_MENU				9
#define TEMPREATURE_MENU			    10
/***********************************************/
/******************SELECTION_MENU***************/
//THEY ARE USED WHEN USER PRESS ANY BUTTON IN THE KEYPAD TO SELECT ANY ROOM

		/*MAIN_MENU*/
#define ROOM1_SELECT					'1'
#define ROOM2_SELECT					'2'
#define ROOM3_SELECT					'3'
#define ROOM4_SELECT					'4'	//CASE GUEST MODE
#define ADMIN_MORE_SELECT				'4' //CASE ADMIN MODE
		/**********/
		/*MORE_MENU*/
#define ROOM4_ADMIN_SELECT				'1'
#define TV_SELECT						'2'	
#define AIR_COND_SELECT					'3'
#define ADMIN_RET_OPT					'4'
		/**********/
		/*AIR_COND_MENU*/
#define SELECT_SET_TEMP					'1'
#define SELECT_AIR_COND_CTRL			'2'
#define SELECT_AIR_COND_RET				'3' 
		/**************/				
/**********************************************/
#endif /* MASTER_MAIN_MACROS_H_ */