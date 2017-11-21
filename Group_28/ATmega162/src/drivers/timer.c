/*
 * timer.c
 *
 * Created: 17.11.2017 15:19:45
 *  Author: stined
 */ 
#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

int current_time = 0;

void TIMER_init()
{
	//CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Prescaler = 256
	TCCR1B |= (1 << CS12);
	
	// Set output compare value
	OCR1A = 0x4B00;		// 19200, corresponds to match every second
}

ISR(TIMER1_COMPA_vect)
{
	current_time = current_time + 1;
}

void TIMER_start()
{
	TIMSK |= (1 << OCIE1A);
	current_time = 0;
}

int TIMER_stop()
{
	TIMSK &= ~(1 << OCIE1A);
	return current_time;
}