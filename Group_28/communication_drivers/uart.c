/*
 * uart.c
 *
 * Created: 30.08.2017 17:32:44
 *  Author: ingunnjv
 */ 

#include "uart.h"

#if defined(__AVR_ATmega2560__)
#include "../ATmega2560/src/setup.h"
#endif

#if defined(__AVR_ATmega162__)
#include "../ATmega162/src/setup.h"
#endif

#include <avr/io.h>
#include <stdio.h>


void UART_Init( unsigned int ubrr )
{
	// Set baud rate
	UBRR0H |= (unsigned char)(ubrr>>8);
	UBRR0L |= (unsigned char)ubrr;
	
	// Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	#if defined(__AVR_ATmega162__)
	UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	#endif
	#if defined(__AVR_ATmega2560__)
	UCSR0C |= (1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	#endif
	
	fdevopen(&UART_Transmit, &UART_Recieve);
}

void UART_Transmit (unsigned char data)
{
	// Wait for empty transmit buffer
	while (!( UCSR0A & (1<<UDRE0))); 
	
	// Put data into buffer, sends the data
	UDR0 = data;  
}

unsigned char UART_Recieve (void)
{
	// Wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));  

	// Get and return received data from buffer
	return UDR0;  
}