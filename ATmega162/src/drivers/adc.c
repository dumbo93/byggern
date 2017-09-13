/*
 * adc.c
 *
 * Created: 13.09.2017 11:40:49
 *  Author: ingunnjv
 */ 
#include "../bit_manipulation.h"
#include <avr/io.h>

int ADC_init(void)
{
	set_bit(MCUCR, SRE);
	set_bit(SFIOR, XMM2);
	
	// Set the interrupt pin to input
	clear_bit(DDRD, PD3);
	return 0;
}

uint8_t ADC_read(uint8_t channel)
{
	volatile uint8_t *ext_adc = (uint8_t *) 0x1400; // Start address for the ADC
	
	if (channel > 3){ return 0; }
	*ext_adc = 0x04 | channel; // bitwise OR
	
	// wait until interrupt is low, which means we can read the converted data
	loop_until_bit_is_clear(PIND, PD3);
	
	return *ext_adc;
	
}
