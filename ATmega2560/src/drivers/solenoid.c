/*
 * solenoid.c
 *
 * Created: 15.11.2017 08:19:27
 *  Author: ingunnjv
 */ 

#include "solenoid.h"
#include "../setup.h"
#include <util/delay.h>


void SOLENOID_init()
{
	// Set the correct pin as output
	// Choose A1: PF1
	DDRF |= (1 << DDF1);
	PORTF |= (1 << PF1);
}

void SOLENOID_pulse(uint8_t shoot)
{
	// This function should only be called if shoot has changed from 0 to 1
	// (message received from 162 only when this happens)
	if (shoot){
		//set pin to 1 or 0
		PORTF &= ~(1 << PF1);
		// wait a little
		_delay_ms(500);
		// set pin to 0 or 1 (opposite of above)
		PORTF |= (1 << PF1);
		
		
	}
}