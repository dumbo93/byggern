/*
 * eeprom.h
 *
 * Created: 18.11.2017 07:42:58
 *  Author: ingunnjv
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

void EEPROM_write(uint8_t data, unsigned int address);

uint8_t EEPROM_read(unsigned int address);

#endif /* EEPROM_H_ */