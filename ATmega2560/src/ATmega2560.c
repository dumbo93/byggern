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

#include "drivers/motor.h"
#include "count_score.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>
#include <avr/interrupt.h>

int main( void ){
	cli();
	// 
	printf("Initializations\n");
	UART_Init( MYUBRR );
	//printf("UART\n");
	SPI_init();
	//printf("SPI\n");
	MCP_init();
	//printf("MCP\n");
	CAN_init();
	//printf("CAN\n");
	COUNTER_init();
	printf("COUNTER\n");
	
	ADC_init_2560();
	printf("ADC init\n");
	
	printf("TWI init\n");
	MOTOR_init();
	
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
	can_msg receive;
	uint8_t value;
	int msg_type;
	uint8_t twi_message[1];
	int velocity;
	
	while(1){
		CAN_handle_interrupt(&receive);
		
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_SLIDER_POS_R:
				printf("\n\nReceived slider position: (%d) \n",receive.data[1]);
				//printf("Received id: %d \n", receive.id);
				//printf("Received length: %d  \n", receive.length);
				SERVO_set_position(receive.data[1]);
				break;
			case CAN_JOY_POS_X:
				printf("\n\nReceived joystick pos (x): (%d) \n", receive.data[1]);
				//printf("Received id: %d \n", receive.id);
				//printf("Received length: %d  \n", receive.length);
				velocity = receive.data[1] - 127;
				if (velocity < 0){
					//retning venstre 
					MOTOR_set_dir(0);
					velocity = abs(velocity);
					MOTOR_set_velocity((uint8_t)velocity);
				}
				else{
					//retning høyre
					MOTOR_set_dir(1);
					MOTOR_set_velocity((uint8_t)velocity);
				}
				
				break;
		}
		
		

		
		//value = IR_read();
		//printf("\nAvg IR signal: %d\n\n", value);
		//COUNT_SCORE_get();
		
		_delay_ms(50);
		
	}
	
	

	return 0;
}
