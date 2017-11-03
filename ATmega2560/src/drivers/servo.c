/*
 * servo.c
 *
 * Created: 01.11.2017 14:34:13
 *  Author: ingunnjv
 */ 
#include "servo.h"
#include "counter.h"
#include <stdlib.h>


void SERVO_set_position(uint8_t pos)
{

	float pulse_width_ms;
	pulse_width_ms = (float)pos/255 * (MAX - MIN) + MIN; //Scaled between MIN and MAX
	
	if ( pulse_width_ms > MAX){ pulse_width_ms = MAX; }
	else if ( pulse_width_ms < MIN ){ pulse_width_ms = MIN; }
	COUNTER_set_pulse_width(pulse_width_ms);
}
