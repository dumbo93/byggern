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
	printf("\n\n\nInit done\n");
	sei();
	can_msg send;
	send.id = ATmega2560_ID;
	send.length = 4;
	send.data[0] = 'H';
	send.data[1] = 'e';
	send.data[2] = 'i';
	send.data[3] = '\0';
	can_msg receive;
	
	while(1){
		//printf("While loop\n");
		CAN_msg_send(&send);
		//printf("Message sent\n");
		_delay_us(200);
		CAN_handle_interrupt(&receive);
		//printf("Message received\n");
		printf("\n\nSent message: %s \t Received message: %s \n", send.data, receive.data);
		printf("Sent id: %d \t Received id: %d \n", send.id, receive.id);
		printf("Sent length: %d \t Received length: %d \n", send.length, receive.length);
		_delay_ms(2000);
	}
	
	

	return 0;
}
