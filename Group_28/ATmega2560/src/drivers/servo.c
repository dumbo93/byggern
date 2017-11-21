/*
 * servo.c
 *
 * Created: 01.11.2017 14:34:13
 *  Author: ingunnjv
 */ 
#include "servo.h"
#include "pwm.h"

#include <stdlib.h>

void SERVO_set_position(uint8_t pos)
{
	uint16_t pulse_width = MIN + (uint16_t)pos;
	if ( pulse_width > MAX){ pulse_width = MAX; }
	else if ( pulse_width < MIN ){ pulse_width = MIN; }
		
	PWM_set_pulse_width(pulse_width);
}