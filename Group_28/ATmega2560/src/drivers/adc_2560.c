/*
 * adc.c
 *
 * Created: 07.11.2017 13:11:46
 *  Author: ingunnjv
 */ 

#include "adc_2560.h"

void ADC_init_2560( void )
{
	// Enable ADC and set prescaler to 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t ADC_read_2560( void )
{
	// Reference selection: AVCC w/ external capacitor at AREF. Left adjust result
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait until conversion is complete
	while(ADCSRA & (1 << ADSC));
	
	// Read converted data
	return ADCH;
}