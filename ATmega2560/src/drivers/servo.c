/*
 * servo.c
 *
 * Created: 01.11.2017 14:34:13
 *  Author: ingunnjv
 */ 
#include "servo.h"
#include "counter.h"
#include <stdlib.h>


void SERVO_set_position(uint8_t sign, uint8_t pos)
{
	float pulse_width_ms;
	if (pos == 0){
		pulse_width_ms = NEUTRAL;
	}
	else if (sign == POSITIVE){
		pulse_width_ms = pos/100 * (MAX - NEUTRAL) + NEUTRAL; //Scaled between NEUTRAL and MAX
	}
	else if (sign == NEGATIVE){
		pos = abs(pos - 100);	// Max deflection to the left is now 0, and neutral is 100
		pulse_width_ms = pos/100 * (NEUTRAL - MIN) + MIN; // Scaled between MIN and NEUTRAL
	}
	else {
		pulse_width_ms = NEUTRAL;
	}
	
	if ( pulse_width_ms > MAX){ pulse_width_ms = MAX; }
	else if ( pulse_width_ms < MIN ){ pulse_width_ms = MIN; }
	
	COUNTER_set_pulse_width(pulse_width_ms);
}
