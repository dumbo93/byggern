/*
 * spi.h
 *
 * Created: 11.10.2017 10:56:58
 *  Author: ingunnjv
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_init( void );
uint8_t SPI_transmit_receive(uint8_t data);
void SPI_set_ss( int val );

#endif /* SPI_H_ */