/*
 * counter.c
 *
 * Created: 01.11.2017 13:31:58
 *  Author: ingunnjv
 */ 

#include "../setup.h"
#include "counter.h"
#include <avr/io.h>

void COUNTER_init()
{
	// Clear OC1A on compare match, set OC1A at BOTTOM (non-inverting)
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
	
	// Set to mode 14 (Fast PWM)
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	
	// Set prescaler to 1/8
	TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
	
	// Set TOP
	// frequency = 50 Hz
	// trekke fra 1?
	ICR1 = F_CPU/(64*50);
	
	// Set OC1A to output
	DDRB |= (1 << DDB5);
}

void COUNTER_set_pulse_width(float pulse_width_ms)
{
	OCR1A = F_CPU/64/1000 * pulse_width_ms;
}