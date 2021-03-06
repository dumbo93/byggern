/*
 * adc.c
 *
 * Created: 13.09.2017 11:40:49
 *  Author: ingunnjv
 */ 
#include "../bit_manipulation.h"
#include "../memory_mapping.h"
#include "../setup.h"

#include <avr/io.h>
#include <util/delay.h>

int ADC_init(void)
{
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	// Set the interrupt pin to input
	DDRD &= ~(1 << PD3);
	return 0;
}

uint8_t ADC_read(uint8_t channel)
{
	// Start address for the ADC
	volatile uint8_t *ext_adc = (uint8_t *) ADC_DATA_ADDRESS; 
	
	// Bitwise OR
	if (channel > 3){ return 0; }
	*ext_adc = 0x04 | channel; 
	
	// Wait until interrupt is low, which means we can read the converted data
	loop_until_bit_is_clear(PIND, PD3);
	_delay_us(200);
	
	return *ext_adc;
}
