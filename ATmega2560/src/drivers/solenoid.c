/*
 * solenoid.c
 *
 * Created: 15.11.2017 08:19:27
 *  Author: ingunnjv
 */ 

#include "solenoid.h"
#include "../setup.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int solenoid_timer_flag = 0;

void SOLENOID_init()
{
	// Set the correct pin as output
	// Choose A1: PF1
	DDRF |= (1 << DDF1);
	PORTF |= (1 << PF1);
	
	SOLENOID_timer_init();
}

void SOLENOID_pulse(uint8_t shoot)
{
	// This function should only be called if shoot has changed from 0 to 1
	// (message received from 162 only when this happens)
	if (shoot){
		// Start timer
		//set pin to 0
		PORTF &= ~(1 << PF1);
	}
}

void SOLENOID_timer_init(){
	//CTC mode
	TCCR4B |= (1 << WGM42);
	
	// Prescaler = 256
	TCCR4B |= (1 << CS42);
	
	// Set output compare value
	OCR4A = 0x5162;		// 20834, corresponds to f = 3Hz
	// Start timer
	TIMSK4 |= (1 << OCIE4A);
}

ISR(TIMER4_COMPA_vect){
	
	PORTF |= (1 << PF1);

}

