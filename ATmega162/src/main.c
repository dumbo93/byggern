/*
 * main.c
 *
 * Created: 11.09.2017 17:32:44
 *  Author: ingunnjv
 */ 
#include "setup.h"
#include "menu.h"
#include "drivers/sram.h"
#include "drivers/adc.h"
#include "drivers/joystick.h"
#include "drivers/touch_panel.h"
#include "drivers/oled.h"
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
	ADC_init();
	
	JOY_init();
	//TOUCH_init();
	//OLED_init();
	//MENU_init();
	SPI_init();
	MCP_init();
	CAN_init();
	printf("\n\n\nInit done\n");
	sei();
	//can_msg send = {.id = 1, .length = 1, .data = 130};
	can_msg send;
	send.id = ATmega162_ID;
	send.length = 4;
	send.data[0] = 'H';
	send.data[1] = 'o';
	send.data[2] = 'l';
	send.data[3] = '\0';
	can_msg receive;
	
	while(1){
		////printf("While loop\n");
		//CAN_msg_send(&send);
		////printf("Message sent\n");
		//_delay_us(200);
		//CAN_handle_interrupt(&receive);
		//printf("Message received\n");
		//printf("\n\nSent message: %s \t Received message: %s \n", send.data, receive.data);
		//printf("Sent id: %d \t Received id: %d \n", send.id, receive.id);
		//printf("Sent length: %d \t Received length: %d \n", send.length, receive.length);
		//printf("\n\nSent message: %s \n", send.data);
		//printf("Sent id: %d \n", send.id);
		//printf("Sent length: %d \n", send.length);
		
		JOY2CAN_send_pos();
		_delay_ms(2000);
	}
	
	

	return 0;
}
