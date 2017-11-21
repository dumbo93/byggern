/*
 * eeprom.c
 *
 * Created: 18.11.2017 07:42:49
 *  Author: ingunnjv
 */ 

#include "eeprom.h"

#include <avr/interrupt.h>


void EEPROM_write(uint8_t data, unsigned int address)
{
	cli();
	
	// Wait for completion of previous write
	while(EECR & (1 << EEWE));
	
	// Set up address and data registers
	EEAR = address;
	EEDR = data;
	
	// Write logical one to Master Write Enable
	EECR |= (1 << EEMWE);
	
	// Start eeprom write
	EECR |= (1 << EEWE);
	
	sei();
}

uint8_t EEPROM_read(unsigned int address)
{
	// Wait for completion of previous write
	while(EECR & (1 << EEWE));
	
	// Set up address register
	EEAR = address;
	
	// Start eeprom read
	EECR |= (1 << EERE);
	
	return EEDR;
}