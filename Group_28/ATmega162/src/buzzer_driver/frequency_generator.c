/*
 * frequency_generator.c
 *
 * Created: 19.11.2017 16:38:20
 *  Author: ingunnjv
 */ 

#include "frequency_generator.h"
#include "../setup.h"
#include <util/delay.h>


void FREQUENCY_GENERATOR_init(void)
{
	//Timer0-ctc mode and prescaler=64
	TCCR0 |= (1<<WGM01);
	TCCR0 &= ~(1<<WGM00);
	// Compare output mode: toggle OC0 on compare match
	TCCR0 |= (1 << COM00);
	TCCR0 &= ~(1 << COM01);
	DDRB |= (1 << PB0);

}

void FREQUENCY_GENERATOR_start(uint8_t start)
{
	if (start > 0){
		// prescaler=64
		TCCR0 |= (1<<CS01) | (1<<CS00);
		TCCR0 &= ~(1<<CS02);
	}
	else{
		TCCR0 &= ~(1<<CS02) & ~(1<<CS01) & ~(1<<CS00);
		TCNT0 = 0;
	}
}

void FREQUENCY_GENERATOR_play(uint8_t match)
{
	if (match > 0){
		FREQUENCY_GENERATOR_start(0);
		_delay_ms(2);
		OCR0 = match;
		FREQUENCY_GENERATOR_start(1);
	}
	else{
		FREQUENCY_GENERATOR_start(0);
	}
}