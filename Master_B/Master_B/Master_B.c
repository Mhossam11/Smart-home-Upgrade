/*
 * Master_B.c
 *
 * Created: 9/5/2023 12:07:31 AM
 *  Author: 20100
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>	//to be able to use the interrupt
#define F_CPU 8000000ul		//Micro controller Freq
#include <util/delay.h>		//used for delay 


#include "EEPROM_driver.h"
#include "LCD_driver.h"
#include "UART_driver.h"
#include "SPI_driver.h"
#include "LED_driver.h"
#include "Timer_driver.h"
#include "Master_main_macros.h"
#include "Communication_Messages.h"
#include "Show_Menu.h"
#include "EXT._Interrupt.h"

/**************** VARIABLE ****************/
char Key_Pressed=NOTPRESSED;						//variable will take the read from BLUETOOH_MODULE
volatile unsigned short Session_Counter=0;					//Timer counter (in ISR)
char show_menu=MAIN_MENU;							//variable used to know which menu we select
char TIME_OUT_FLAG=FALSE;							//Flag to know if the session time out or not
volatile char secondes_counter=0;
/*****************************************/
int main(void)
{
	/*************INITILIZATION***********/
	LCD_vInit();
	SPI_MasterInit();
	UART_vInit(BAUD_RATE);
	INT0_vInit();
	INT1_vInit();
	Timer1_wave_fastPWM_servo_postive(0);
	
	LED_vInit(MODES_LED_PORTS,BLOCK_MODE_LED_PIN);		//initialize BLOCK_MODE LED
	LED_vInit(MODES_LED_PORTS,ADMIN_MODE_LED_PIN);		//initialize ADMIN_MODE LED
	LED_vInit(MODES_LED_PORTS,GUEST_MODE_LED_PIN);		//initialize GUEST_MODE LED
	LED_vInit(MODES_LED_PORTS,LIVING_ROOM_LED1);
	LED_vInit(MODES_LED_PORTS,LIVING_ROOM_LED2);
	
	/*************************************/
	
	/**************VARIABLES**************/
	char i;												//counter used for loops
	
	char login_mode=NO_MODE;							//variable used to know which mode the user select
	char BLOCKED_MODE_FLAG=FALSE;						//FLAG to know if the session expired or not
	
	char pass[4]={NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED};	//array to save the password and check it	
	char pass_tries=MAX_PASS_TRIES;						//variable tell the maximum tries for the user to enter the password
	char tries_allowed_counter=I_COUNTER;				//counter to count the password tries allowed
	
	char Temp_Units=NOTPRESSED;							//variable take the units value from user
	char Temp_Tens=NOTPRESSED;							//variable take the Tens value from user
	char Tempreature=0;
	/*************************************/
	
	LCD_vSend_String("Welcome To Smart");
	LCD_Move_Cursor(2,1);
	LCD_vSend_String("Home System");
	_delay_ms(500);
	LCD_Clear_Screen();
	
	if((EEPROM_Read(EEPROM_ADMIN_STATUS_LOCATION)==0xFF) && (EEPROM_Read(EEPROM_GUEST_STATUS_LOCATION)==0xFF))//if the password didn't saved befor
	{	
		LCD_vSend_String("Login For");
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("First Time");
		_delay_ms(500);
		LCD_Clear_Screen();
		/*********** Save Guest passowrd for the first time ***********/
		LCD_vSend_String("Set Admin Pass");
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("Admin pass:");
		
		for(i=I_COUNTER;i<PASS_SIZE;i++)												//FOR loop to enter the password of the admin_mode
		{
			Key_Pressed=NOTPRESSED;												//remove the last value saved in it 
			do 
			{
				Key_Pressed=UART_u8ReceiveData();
			} while (Key_Pressed==NOTPRESSED);
			
			LCD_vSend_char(Key_Pressed);										//print the value of the password that the user enter
			_delay_ms(50);
			LCD_Move_Cursor(2,12+i);
			LCD_vSend_char(PASS_SYMBOL);										//print the password symbol
			EEPROM_Write((EEPROM_ADMIN_PASS1_LOCATION+i),Key_Pressed);	//save the  admin password in EEPROM
			_delay_ms(30);
		}
		i=I_COUNTER;															//remove the last value saved in it 
		EEPROM_Write(EEPROM_ADMIN_STATUS_LOCATION,0x00);						//write 0 in admin status location to know that the password already saved
		_delay_ms(30);
		/**************************************************************/
		
		/*********** Save Guest passowrd for the first time ***********/
		LCD_Clear_Screen();
		LCD_vSend_String("Set Guest Pass");
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("Guest Pass:");
		
		for(i=I_COUNTER;i<PASS_SIZE;i++)												//FOR loop to enter the password of the admin_mode
		{
			Key_Pressed=NOTPRESSED;												//remove the last value saved in it
			do
			{
				Key_Pressed=UART_u8ReceiveData();
			} while (Key_Pressed==NOTPRESSED);
			LCD_vSend_char(Key_Pressed);										//print the value of the password that the user enter
			_delay_ms(50);
			LCD_Move_Cursor(2,12+i);
			LCD_vSend_char(PASS_SYMBOL);										//print the password symbol
			EEPROM_Write((EEPROM_GUEST_PASS1_LOCATION+i),Key_Pressed);	//save the  Guest password in EEPROM
			_delay_ms(30);
		}
		i=I_COUNTER;															//remove the last value saved in it 
		EEPROM_Write(EEPROM_GUEST_STATUS_LOCATION,0x00);						//write 0 in Guest status location to know that the password already saved
		_delay_ms(30);
		/**************************************************************/
		LCD_Clear_Screen();
		LCD_vSend_String("Password saved");
		_delay_ms(500);
	}
	while(1)
    {
		Key_Pressed=NOTPRESSED;
		
		while(TIME_OUT_FLAG==TRUE)
		{
			Timer_Stop_CTC();
			
			Key_Pressed==NOTPRESSED;
			login_mode=NO_MODE;
			show_menu=MAIN_MENU;
			TIME_OUT_FLAG=FALSE;
			
			Session_Counter=0;
			
			LED_vTurnOFF(MODES_LED_PORTS,ADMIN_MODE_LED_PIN);
			LED_vTurnOFF(MODES_LED_PORTS,GUEST_MODE_LED_PIN);
			
			LCD_Clear_Screen();
			LCD_vSend_String("Session TimeOut");
			_delay_ms(500);
		}
		
		while(login_mode==NO_MODE)
		{
			if(BLOCKED_MODE_FLAG==TRUE)
			{
				pass_tries=MAX_PASS_TRIES;
				tries_allowed_counter=I_COUNTER;
				login_mode=NO_MODE;
				BLOCKED_MODE_FLAG=FALSE;
			
				LCD_Clear_Screen();
				LCD_vSend_String("Login Blocked");
				LCD_Move_Cursor(2,1);
				LCD_vSend_String("Wait 5 Sec");
				LED_vTurnOn(MODES_LED_PORTS,BLOCK_MODE_LED_PIN);	//turn on block mode led
				_delay_ms(BLOCK_MODE_TIME);							//wait 5sec
				LED_vTurnOFF(MODES_LED_PORTS,BLOCK_MODE_LED_PIN);	//turn off block mode led
			}
			
			Key_Pressed=NOTPRESSED;									//remove the last value saved in it 
			LCD_Clear_Screen();
			LCD_vSend_String("Select Mode:");
			LCD_Move_Cursor(2,1);
			LCD_vSend_String("1-Admin  2-Guest");
			
			do														//take the read from the user
			{
				Key_Pressed=UART_u8ReceiveData();
			} while (Key_Pressed==NOTPRESSED);
			
			if((Key_Pressed != CHECK_ADMIN_MODE) && (Key_Pressed != CHECK_GUEST_MODE))//if the user press another button not 1 or 2
			{
				LCD_Clear_Screen();
				LCD_vSend_String("Wrong Input!");
				_delay_ms(500);
				Key_Pressed=NOTPRESSED;								//remove the last value saved in it 
				continue;
			}
			
			switch(Key_Pressed)
			{
				case CHECK_ADMIN_MODE:								//check the ascii code that user enter 
					while(login_mode!=ADMIN_MODE)
					{
						LCD_Clear_Screen();
						LCD_vSend_String("Admin Mode");
						LCD_Move_Cursor(2,1);
						LCD_vSend_String("Admin Pass:");
						/*************check admin password**************/
						for(i=I_COUNTER;i<PASS_SIZE;i++)				//for loop to take the password from the user
						{
							do 
							{
								pass[i]=UART_u8ReceiveData();			//save the numbers that the user enter in array
							} while (pass[i]==NOTPRESSED);
							LCD_vSend_char(pass[i]);
							_delay_ms(50);
							LCD_Move_Cursor(2,12+i);
							LCD_vSend_char(PASS_SYMBOL);				//print password symbol *
						}
					
						if((EEPROM_Read(EEPROM_ADMIN_PASS1_LOCATION)==pass[0]) && (EEPROM_Read(EEPROM_ADMIN_PASS2_LOCATION)==pass[1]) && (EEPROM_Read(EEPROM_ADMIN_PASS3_LOCATION)==pass[2]) && (EEPROM_Read(EEPROM_ADMIN_PASS4_LOCATION)==pass[3]))
						{//if the password that the user enter is true
							LCD_Clear_Screen();
							LCD_vSend_String("Right password");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("Admin Mode");
							login_mode=ADMIN_MODE;								//save that user enter admin mode
							LED_vTurnOn(MODES_LED_PORTS,ADMIN_MODE_LED_PIN);	//turn on admin mode led
							_delay_ms(500);
							Timer_CTC_Init_interrupt();							//start the session counter 
							LCD_Clear_Screen();
						}
						/*************************************************************/
						else
						{
							pass_tries--;
							tries_allowed_counter++;
							//login_mode=NO_MODE;
								
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong password");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("Tries Allowed ");
							LCD_vSend_char(pass_tries+48);			//send asci code of allowed tries
							_delay_ms(500);
							
							if(tries_allowed_counter>2)
							{
								LCD_Clear_Screen();
								LCD_vSend_String("No Tries Allowed");
								LCD_Move_Cursor(2,1);
								LCD_vSend_String("  BLOCK MODE");
								BLOCKED_MODE_FLAG=TRUE;
								_delay_ms(500);
								break;
							}
						}												
					}//end of while loop											
				break;
				
				case CHECK_GUEST_MODE:
					while(login_mode!=GUEST_MODE)
					{
						LCD_Clear_Screen();
						LCD_vSend_String("Guest Mode");
						LCD_Move_Cursor(2,1);
						LCD_vSend_String("Guest Pass:");
						/*************check admin password**************/
						for(i=I_COUNTER;i<PASS_SIZE;i++)				//for loop to take the password from the user
						{
							do
							{
								pass[i]=UART_u8ReceiveData();			//save the numbers that the user enter in array
							}while (pass[i]==NOTPRESSED);
							
							LCD_vSend_char(pass[i]);
							_delay_ms(50);
							LCD_Move_Cursor(2,12+i);
							LCD_vSend_char(PASS_SYMBOL);				//print password symbol *
						}
					
						if((EEPROM_Read(EEPROM_GUEST_PASS1_LOCATION)==pass[0]) && (EEPROM_Read(EEPROM_GUEST_PASS2_LOCATION)==pass[1]) && (EEPROM_Read(EEPROM_GUEST_PASS3_LOCATION)==pass[2]) && (EEPROM_Read(EEPROM_GUEST_PASS4_LOCATION)==pass[3]))
						{//if the password that the user enter is true
							LCD_Clear_Screen();
							LCD_vSend_String("Right password");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("Guest Mode");
							login_mode=GUEST_MODE;								//save that user enter admin mode
							LED_vTurnOn(MODES_LED_PORTS,GUEST_MODE_LED_PIN);	//turn on admin mode led
							_delay_ms(500);
							Timer_CTC_Init_interrupt();							//start the session counter
							LCD_Clear_Screen();
						}
						/*************************************************************/
						else
						{
							pass_tries--;
							tries_allowed_counter++;
						
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong password");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("Tries Allowed ");
							LCD_vSend_char(pass_tries+48);			//send asci code of allowed tries
							_delay_ms(500);
						
							if(tries_allowed_counter>=3)
							{
								LCD_Clear_Screen();
								LCD_vSend_String("No Tries Allowed");
								LCD_Move_Cursor(2,1);
								LCD_vSend_String("  BLOCK MODE");
								BLOCKED_MODE_FLAG=TRUE;
								_delay_ms(500);
								break;
							}
						}
					}//end of while loop
				break;
				
				default:
				break;
			}//end of Modes_switch
						
		}//end of Selection mode			
		/***********************************************/
		while(TIME_OUT_FLAG!=TRUE)	//LOOP while session time_out didn't finished
		{
			Key_Pressed=NOTPRESSED;
			
			switch(show_menu)
			{
				case MAIN_MENU:
					do 
					{
						LCD_Clear_Screen();
						LCD_vSend_String("1-Room1 2-Room2");
						LCD_Move_Cursor(2,1);
						if(login_mode==ADMIN_MODE)				//if user select admin mode choose this option
						{
							LCD_vSend_String("3-Room3 4-More");
						}
						else if(login_mode==GUEST_MODE)  		//if user select guest mode choose this option
						{
							LCD_vSend_String("3-Room3 4-Room4");	
						}
						
						do 
						{
							if((Session_Counter>=ADMIN_TIME_OUT && login_mode==ADMIN_MODE) || (Session_Counter>=GUEST_TIME_OUT && login_mode==GUEST_MODE))	//if session time expired
							{
								TIME_OUT_FLAG=TRUE;
								break;
							}
							Key_Pressed=UART_u8ReceiveData();
						} while (Key_Pressed==NOTPRESSED);
						_delay_ms(100);
						
						if(Key_Pressed==ROOM1_SELECT)
						{
							show_menu=ROOM1_MENU;
						}
						else if(Key_Pressed==ROOM2_SELECT)
						{
							show_menu=ROOM2_MENU;
						}
						else if(Key_Pressed==ROOM3_SELECT)
						{
							show_menu=ROOM3_MENU;
						}
						else if((Key_Pressed==ROOM4_SELECT) && (login_mode==GUEST_MODE))
						{
							show_menu=ROOM4_MENU;
						}
						else if((Key_Pressed==ADMIN_MORE_SELECT) && (login_mode==ADMIN_MODE))
						{
							show_menu=MORE_MENU;
						}
						else if(Key_Pressed != NOTPRESSED)
						{
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong Input!");
							_delay_ms(500);
						}
					} while (((Key_Pressed<'1') || (Key_Pressed>'4') )&& TIME_OUT_FLAG==FALSE);	
				break;//end of MAIN menu
				
				case MORE_MENU:
					do 
					{
						Key_Pressed=NOTPRESSED;
						LCD_Clear_Screen();
						LCD_vSend_String("1-Room4 2-TV");
						LCD_Move_Cursor(2,1);
						LCD_vSend_String("3-Air Cond. 4-Ret");
						do 
						{
							if((Session_Counter>=ADMIN_TIME_OUT && login_mode==ADMIN_MODE) || (Session_Counter>=GUEST_TIME_OUT && login_mode==GUEST_MODE) )	//if session time expired
								{
									TIME_OUT_FLAG=TRUE;
									break;
								}
							
							Key_Pressed=UART_u8ReceiveData();
						} while (Key_Pressed==NOTPRESSED);
						_delay_ms(250);
						
						if (Key_Pressed==ROOM4_ADMIN_SELECT)
						{
							show_menu=ROOM4_MENU;
						}
						else if (Key_Pressed==TV_SELECT)
						{
							show_menu=TV_MENU;
						}
						else if (Key_Pressed==AIR_COND_SELECT)
						{
							show_menu=AIR_COND_MENU;
						}
						else if (Key_Pressed==ADMIN_RET_OPT)
						{
							show_menu=MAIN_MENU;
						}
						else
						{
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong Input!");
							_delay_ms(500);
						}
					} while (((Key_Pressed<'1') || (Key_Pressed>'4')) && TIME_OUT_FLAG==FALSE);
			 break;
			 
			 case AIR_COND_MENU:
				Key_Pressed=NOTPRESSED;
				do 
				{
					LCD_Clear_Screen();
					LCD_vSend_String("1-Set Tempreature");
					LCD_Move_Cursor(2,1);
					LCD_vSend_String("2-Control 3-Ret");
					do 
					{
						if((Session_Counter>=ADMIN_TIME_OUT) && (login_mode==ADMIN_MODE))	//if session time expired
						{
							TIME_OUT_FLAG=TRUE;
							break;
						}
						Key_Pressed=UART_u8ReceiveData();
					} while (Key_Pressed==NOTPRESSED);
					_delay_ms(250);
					if(Key_Pressed==SELECT_SET_TEMP)
					{
						show_menu=TEMPREATURE_MENU;
					}
					else if(Key_Pressed==SELECT_AIR_COND_CTRL)	
					{
						show_menu=AIR_COND_CTRL_MENU;
					}
					else if(Key_Pressed==SELECT_AIR_COND_RET)
					{
						show_menu=MORE_MENU;
					}		
					else
					{
						LCD_Clear_Screen();
						LCD_vSend_String("Wrong Input!");
						_delay_ms(500);
					}
					
				} while (((Key_Pressed<'1') && (Key_Pressed>'3')) && (TIME_OUT_FLAG==FALSE));												
			 break;
			 
			 case ROOM1_MENU:
				Menu_Options(ROOM1_MENU,login_mode);
				show_menu=MAIN_MENU;
			 break;
			 
			 case ROOM2_MENU:
				  Menu_Options(ROOM2_MENU,login_mode);
				  show_menu=MAIN_MENU;
			  break;
			  
			  case ROOM3_MENU:
				   Menu_Options(ROOM3_MENU,login_mode);
				   show_menu=MAIN_MENU;
			   break;
			   
			   case ROOM4_MENU:
					Menu_Options(ROOM4_MENU,login_mode);
					show_menu=MAIN_MENU;
			   break;
			   
			   case TV_MENU:
					 Menu_Options(TV_MENU,login_mode);
					 show_menu=MORE_MENU;
			   break;
			   
			   case AIR_COND_CTRL_MENU:
					Menu_Options(AIR_COND_CTRL_MENU,login_mode);
					show_menu=AIR_COND_MENU;
			   break;
			   
			   case TEMPREATURE_MENU:
					while(Tempreature==0 && TIME_OUT_FLAG==FALSE)
					{
						Key_Pressed=NOTPRESSED;
						LCD_Clear_Screen();
						LCD_vSend_String("Set Temp.=__");
						LCD_vSend_char(DEGREE_SYMBOL);
						LCD_vSend_char('C');
						LCD_Move_Cursor(1,11);
						/**********TO GET TENS NUMBER OF TEMP**************/
						do
						{
							if((Session_Counter>=ADMIN_TIME_OUT) && (login_mode==ADMIN_MODE))
							{
								TIME_OUT_FLAG=TRUE;
								break;
							}
							Key_Pressed=UART_u8ReceiveData();
						} while (Key_Pressed==NOTPRESSED);
						_delay_ms(250);
						
						if(TIME_OUT_FLAG==TRUE)
						{
							break;
						}
						
						if((Key_Pressed<'0') || (Key_Pressed>'9'))
						{
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong Input!");
							_delay_ms(500);
						}
						else
						{
							LCD_vSend_char(Key_Pressed);
							Temp_Tens=(Key_Pressed-VARIABLE_TO_GET_ASCII);
							Key_Pressed=NOTPRESSED;
						}
						/***************************************************/
						/**********TO GET UNITS NUMBER OF TEMP**************/
						do
						{
							if((Session_Counter>=ADMIN_TIME_OUT) && (login_mode==ADMIN_MODE))
							{
								TIME_OUT_FLAG=TRUE;
								break;
							}
							Key_Pressed=UART_u8ReceiveData();
						} while (Key_Pressed==NOTPRESSED);
						_delay_ms(250);
						
						if(TIME_OUT_FLAG==TRUE)
						{
							break;
						}
						if((Key_Pressed<'0') || (Key_Pressed>'9'))
						{
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong Input!");
							_delay_ms(500);
						}
						else
						{
							LCD_vSend_char(Key_Pressed);
							Temp_Units=(Key_Pressed-VARIABLE_TO_GET_ASCII);
							Key_Pressed=NOTPRESSED;
						}
						/***************************************************/
						Tempreature=(Temp_Tens*10)+(Temp_Units);
						SPI_MasterTransmitchar(SET_TEMP);
						_delay_ms(200);
						SPI_MasterTransmitchar(Tempreature);
						
						LCD_Clear_Screen();
						LCD_vSend_String("Tempreature set");
						_delay_ms(500);
					}
					show_menu=AIR_COND_MENU;
					break;
					
					default:
					break;					
			}	
		}    
	}
}

/******session timeout********/
ISR(TIMER0_COMP_vect)//ISR for session timeout
{
	Session_Counter++;
}

/*****************************/
/********for living room AND GARGAE***********/

ISR(INT0_vect)//ISR to turn on livingroom led
{
	LED_vTurnOn(MODES_LED_PORTS,LIVING_ROOM_LED1);
	LED_vTurnOn(MODES_LED_PORTS,LIVING_ROOM_LED2);
	Timer2_OverFlow_Init_interrupt();//start timer 2 go to ISR every 1 sec;
}

ISR(INT1_vect)//ISR to turn on livingroom led
{
	Timer1_wave_fastPWM_servo_postive(90);
	Timer2_OverFlow_Init_interrupt();//start timer 2 go to ISR every 1 sec;
}

ISR(TIMER2_OVF_vect)//ISR to count the time of the living room leds
{
	secondes_counter++;
	if(secondes_counter>=5)
	{
		secondes_counter=0;
		LED_vTurnOFF(MODES_LED_PORTS,LIVING_ROOM_LED1);
		LED_vTurnOFF(MODES_LED_PORTS,LIVING_ROOM_LED2);
		
		Timer1_wave_fastPWM_servo_postive(0);
		Timer2_Stop_OverFlow();
	}
}
/************************************/