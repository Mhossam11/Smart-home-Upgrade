/*
 * Show_Menu.h
 *
 * Created: 9/7/2023 11:20:17 PM
 *  Author: 20100
 */ 


#ifndef SHOW_MENU_H_
#define SHOW_MENU_H_

#include "Timer_driver.h"
#include "SPI_driver.h"
#include "LCD_driver.h"
#include "Master_main_macros.h"
#include "Communication_Messages.h"

#define F_CPU 8000000ul
#include <util/delay.h>

void Menu_Options(const char Selected_Room,const char Selected_mode);


#endif /* SHOW_MENU_H_ */