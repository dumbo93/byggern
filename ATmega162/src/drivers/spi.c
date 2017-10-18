/*
 * spi.c
 *
 * Created: 11.10.2017 10:56:48
 *  Author: ingunnjv
 */ 
#include "spi.h"
#include "../setup.h"
#include "../bit_manipulation.h"
#include <avr/io.h>
#include <util/delay.h>

void SPI_init( void )
{
	// Enable SPI, Master, set clock rate
	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
	
	// Set MOSI, SCK and SS output
	DDRB = (1 << DDB5)|(1 << DDB7)|(1 << DDB4);
}

uint8_t SPI_transmit_receive(uint8_t data)
{
	// Start transmission (write to data register)
	SPDR = data;
	// Wait for transmission complete
	//printf("Hello from SPI transmit receive 1\n");
	while(!(SPSR & (1 << SPIF)));
	//printf("Hello from SPI transmit receive 2\n");
	
	return SPDR;
}

// Set _SS to 1 or 0
void SPI_set_ss( int val )
{
	if (val == 1){
		set_bit(PORTB, PB4);
	}
	else if (val == 0){
		clear_bit(PORTB, PB4);
	}
}
