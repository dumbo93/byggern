/*
 * spi.h
 *
 * Created: 11.10.2017 10:56:58
 *  Author: ingunnjv
 */ 


#ifndef SPI_H_
#define SPI_H_


void SPI_init( void );
char SPI_transmit_receive(char cData);
void SPI_set_ss( int val );

#endif /* SPI_H_ */