/*
 * Timer_driver.c
 *
 * Created: 7/25/2023 11:37:23 PM
 *  Author: 20100
 */ 
#include "MACROS.h"
#include <avr/io.h>
#include <avr/interrupt.h>	//to be able to use the interrupt

/***********timer0************/
void Timer_Stop_CTC(void)
{
	CLR_BIT(TCCR0,CS00);			//let the prescaler=1024
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);	
}
void Timer_CTC_Init_interrupt(void)
{
	OCR0=78;						//load 78 in OCR0 78*0.000128-> byro7 lel ISR kol 10msec
		
	SET_BIT(TCCR0,WGM01);			//enable CTC mode WGM01=1,WGM00=0
	CLR_BIT(TCCR0,WGM00);
	
	SET_BIT(TCCR0,CS00);			//let the prescaler=1024
	SET_BIT(TCCR0,CS02); 
	CLR_BIT(TCCR0,CS01);
	
	sei();							//enable I-bet
	SET_BIT(TIMSK,OCIE0);			//enable ctc inttterupt bit 
}
/*****************************/

/************timer2************/
void Timer2_OverFlow_Init_interrupt(void)
{
	SET_BIT(ASSR,AS2);				//3SHAN YA5OD EL CLOCK MN EXTERNAL CRYSTAL 
	
	SET_BIT(TCCR2,CS22);			//SELECT PRESCALER 128 3shan yro7 el ISR kol sanya bzbt
	SET_BIT(TCCR2,CS20);
	
	sei();
	SET_BIT(TIMSK,TOIE2);			//enable interrupt
}
void Timer2_Stop_OverFlow(void)
{
	CLR_BIT(TCCR2,CS22);
	CLR_BIT(TCCR2,CS20);
}
/****************************/

/**************timer1********/
void Timer1_wave_fastPWM_servo_postive(double value)
{
	
	SET_BIT(DDRD,5);				//set pin OC1A o/p
	
	SET_BIT(TCCR1B,WGM13);			//SET FAST PWM SIGNAL WITH TOP ICR1A
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	
	OCR1A=(((value*0.00555555555)+1.5)*1000);				//on time
	ICR1=(19999);						//top of fast pw, 3shan b3d 20000 3ada ybd2 y3ed mn el awl(periodic)
	//20msec
	
	
	
	SET_BIT(TCCR1B,CS11);		//set   prescaler=8

	
	SET_BIT(TCCR1A,COM1A1);			//(non inverting mode) clear OCR1A on compare match and set at bottom
	
}

/***************************/