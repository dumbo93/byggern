/*
 * spi.c
 *
 * Created: 11.10.2017 10:56:48
 *  Author: ingunnjv
 */ 
#include "spi.h"
#include "../ATmega162/src/bit_manipulation.h"

#if defined(__AVR_ATmega162__)
#include "../ATmega162/src/setup.h"
#endif
#if defined(__AVR_ATmega2560__)
#include "../ATmega2560/src/setup.h"
#endif

#include <avr/io.h>
#include <util/delay.h>

void SPI_init( void )
{
	// Set MOSI, SCK and SS output
	#if defined(__AVR_ATmega162__)
	DDRB |= (1 << DDB5)|(1 << DDB7)|(1 << DDB4);
	#endif
	#if defined(__AVR_ATmega2560__)
	DDRB |= (1 << DDB2)|(1 << DDB1)|(1 << DDB0) | (1 << DDB7);
	#endif
	
	// Enable SPI, Master, set clock rate
	SPCR = (1 << MSTR)|(1 << SPR0);
	
	SPCR |= (1 << SPE);
}

uint8_t SPI_transmit_receive(uint8_t data)
{
	// Start transmission (write to data register)
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
	_delay_us(200);
	
	return SPDR;
	
}

// Set _SS to 1 or 0
void SPI_set_ss( int val )
{
	#if defined(__AVR_ATmega162__)
	if (val == 1){
		set_bit(PORTB, PB4);
	}
	else if (val == 0){
		clear_bit(PORTB, PB4);
	}
	#endif
	
	#if defined(__AVR_ATmega2560__)
	if (val == 1){
		set_bit(PORTB, PB7);
	}
	else if (val == 0){
		clear_bit(PORTB, PB7);
	}
	#endif
	
}
