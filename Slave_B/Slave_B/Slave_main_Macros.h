/*
 * Slave_main_Macros.h
 *
 * Created: 9/8/2023 5:10:03 PM
 *  Author: 20100
 */ 


#ifndef SLAVE_MAIN_MACROS_H_
#define SLAVE_MAIN_MACROS_H_

/****************PREVENT MAGICAL NUMBERS************/
#define DUMMY_DATA				0xFF
#define NOTPRESSED				0xFF
#define AIR_COND_PORT			'C'
#define AIR_COND_PIN			 0
#define AIR_COND_EN_PIN			 2

#define ROOMS_PORT				'D'
#define ROOM1_PIN				 0
#define ROOM2_PIN				 1
#define ROOM3_PIN				 2 
#define ROOM4_PIN				 3 
#define TV_PIN					 4

#define TEMP_SENSOR_PORT		'A'
#define TEMP_SENSOR_PIN			 0
/***************************************************/
#define AIR_COND_IS_ON				0x01
#define AIR_COND_IS_OFF				0x00

#endif /* SLAVE_MAIN_MACROS_H_ */