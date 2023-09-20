/*
 * Show_Menu.c
 *
 * Created: 9/7/2023 11:20:04 PM
 *  Author: 20100
 */ 
#include "Show_Menu.h"

/********externed from main************/
extern char Key_Pressed;
extern char show_menu;
/*************************************/

void Menu_Options(const char Selected_Room,const char Selected_mode)
{
	/*************** VARIABLES ********************/
	char Receive;									//variable to Exchange the data with slave
	char Status_Code=DUMMYDATA;						//variable to carry the status of the room
	char TURN_ON_CODE=DUMMYDATA;					//variable to carry the on message of the room	
	char TURN_OFF_CODE=DUMMYDATA;					//variable to carry the on message of the room	
	/**********************************************/
	Key_Pressed=NOTPRESSED;

	do 
	{	
		switch(Selected_Room)
		{
			case ROOM1_MENU:
				Status_Code=ROOM1_STATUS;
				TURN_ON_CODE=ROOM1_TURN_ON;
				TURN_OFF_CODE=ROOM1_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("Room1 S:");
			break;	
		
			case ROOM2_MENU:
				Status_Code=ROOM2_STATUS;
				TURN_ON_CODE=ROOM2_TURN_ON;
				TURN_OFF_CODE=ROOM2_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("Room2 S:");
			break;
		
			case ROOM3_MENU:
				Status_Code=ROOM3_STATUS;
				TURN_ON_CODE=ROOM3_TURN_ON;
				TURN_OFF_CODE=ROOM3_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("Room3 S:");
			break;
		
			case ROOM4_MENU:
				Status_Code=ROOM4_STATUS;
				TURN_ON_CODE=ROOM4_TURN_ON;
				TURN_OFF_CODE=ROOM4_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("Room4 S:");
			break;
		
			case TV_MENU:
				Status_Code=TV_STATUS;
				TURN_ON_CODE=TV_TURN_ON;
				TURN_OFF_CODE=TV_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("TV S:");
			break;
		
			case AIR_COND_CTRL_MENU:
				Status_Code=AIR_COND_STATUS;
				TURN_ON_CODE=AIR_COND_TURN_ON;
				TURN_OFF_CODE=AIR_COND_TURN_OFF;
				LCD_Clear_Screen();
				LCD_vSend_String("Air Cond. S:");
			break;
		}
			SPI_MasterTransmitchar(Status_Code);
			_delay_ms(150);
			Receive=SPI_MasterTransmitchar(DUMMYDATA);
			
			if(Receive == ON_STATUS)
			{
				LCD_vSend_String("ON");
			}
			else if(Receive == OFF_STATUS)
			{
				LCD_vSend_String("OFF");
			}
			LCD_Move_Cursor(2,1);
			LCD_vSend_String("1-ON 2-OFF 3-Ret");			
			
			do 
			{
				Key_Pressed=UART_u8ReceiveData();
			} while (Key_Pressed==NOTPRESSED);
			_delay_ms(200);
			if (Key_Pressed == '1')
			{
				SPI_MasterTransmitchar(TURN_ON_CODE);
			}
			else if (Key_Pressed == '2')
			{
				SPI_MasterTransmitchar(TURN_OFF_CODE);
			}
			else if (Key_Pressed == '3')
			{
				show_menu=MAIN_MENU;
			}
			else
			{
				LCD_Clear_Screen();
				LCD_vSend_String("Wrong Input!");
				_delay_ms(500);
			}
			
	} while((Key_Pressed<'1') || (Key_Pressed>'3'));
}