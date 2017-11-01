/*
 * ATmega2560.c
 *
 * Created: 20.10.2017 15:04:51
 *  Author: ingunnjv
 */ 


#include "setup.h"
#include "../../communication_drivers/uart.h"
#include "../../communication_drivers/spi.h"
#include "../../communication_drivers/MCP2515.h"
#include "../../communication_drivers/can.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>
#include <avr/interrupt.h>

int main( void ){
	cli();
	// Initializations
	UART_Init( MYUBRR );
	SPI_init();
	MCP_init();
	CAN_init();
	//while(1){printf("\n\n\nInit done\n");}
	printf("\n\n\nInit done\n");
	sei();
	can_msg send;
	send.id = ATmega2560_ID;
	send.length = 6;
	send.data[0] = 'H';
	send.data[1] = 'e';
	send.data[2] = 'l';
	send.data[3] = 'l';
	send.data[4] = 'o';
	send.data[5] = '\0';
	can_msg receive;
	
	while(1){
		printf("While loop\n");
		//CAN_msg_send(&send);
		//printf("Message sent\n");
		_delay_us(200);
		CAN_handle_interrupt(&receive);
		//printf("Message received\n");
		//printf("\n\nSent message: %s \t Received message: %s \n", send.data, receive.data);
		//printf("Sent id: %d \t Received id: %d \n", send.id, receive.id);
		//printf("Sent length: %d \t Received length: %d \n", send.length, receive.length);
		printf("\n\nReceived message (x, y): %d (%d, %d) %d \n",receive.data[0], receive.data[1], receive.data[3], receive.data[2] );
		printf("Received id: %d \n", receive.id);
		printf("Received length: %d  \n", receive.length);
		_delay_ms(2000);
	}
	
	

	return 0;
}
