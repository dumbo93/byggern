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
#include "drivers/counter.h"
#include "drivers/servo.h"
#include "drivers/adc_2560.h"
#include "drivers/ir.h"
#include "count_score.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>
#include <avr/interrupt.h>

int main( void ){
	cli();
	// Initializations
	UART_Init( MYUBRR );
	//printf("UART\n");
	//SPI_init();
	////printf("SPI\n");
	//MCP_init();
	////printf("MCP\n");
	//CAN_init();
	////printf("CAN\n");
	//COUNTER_init();
	
	ADC_init_2560();
	//printf("COUNTER\n");
	printf("\n\n\nInit done\n");
	sei();
	//can_msg send;
	//send.id = ATmega2560_ID;
	//send.length = 6;
	//send.data[0] = 'H';
	//send.data[1] = 'e';
	//send.data[2] = 'l';
	//send.data[3] = 'l';
	//send.data[4] = 'o';
	//send.data[5] = '\0';
	//can_msg receive;
	uint8_t value;
	
	while(1){
		//CAN_handle_interrupt(&receive);
//
		//printf("\n\nReceived message (x, y): (%d, %d) \n",receive.data[0], receive.data[1]);
		//printf("Received id: %d \n", receive.id);
		//printf("Received length: %d  \n", receive.length);
		//SERVO_set_position(receive.data[0]);
		
		value = IR_read();
		printf("Avg IR signal: %d\n", value);
		COUNT_SCORE_get();
		
		_delay_ms(100);
		
	}
	
	

	return 0;
}
