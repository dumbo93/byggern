/*
 * driver.c
 *
 * Created: 30.08.2017 17:32:44
 *  Author: ingunnjv
 */ 

#include "driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


// main fjernes paa sikt naar programmet utvides
int main( void){
	unsigned char msg;
	
	UART_Init ( MYUBRR );
	
	while(1){
		msg = UART_Recieve();
		printf("%c\n", msg);
		//UART_Transmit('h');
		//printf("jeg vil sove 'zzzzzzz'\n1 sau, 2 sau, 3 sau ...\n\n");
		_delay_ms(1000);
	}
	return 0;
}

void UART_Init( unsigned int ubrr ){
	/* 
	Set baud rate
	 */
	UBRR0H |= (unsigned char)(ubrr>>8);
	UBRR0L |= (unsigned char)ubrr;
	/* 
	Enable receiver and transmitter
	 */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	/* 
	Set frame format: 8data, 2stop bit
	 */
	UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	
	fdevopen(&UART_Transmit, &UART_Recieve);
}

// transmit data
void UART_Transmit (unsigned char data)
{
	// Wait for empty transmit buffer
	while (!( UCSR0A & (1<<UDRE0))); 
	
	// Put data into buffer, sends the data
	UDR0 = data;  
}

// function to receive data
unsigned char UART_Recieve (void)
{
	//Wait for data to be received
	while(!(UCSR0A) & (1<<RXC0));  
	
	//Get and return received data from buffer
	return UDR0;  
}