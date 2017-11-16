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
#include "drivers/solenoid.h"
#include "drivers/motor.h"

#include "count_score.h"
#include "controller.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main( void ){
	cli();
	printf("Initializations\n");
	UART_Init( MYUBRR );
	SPI_init();
	MCP_init();
	CAN_init();
	COUNTER_init();
	ADC_init_2560();
	MOTOR_init();
	SOLENOID_init();
	printf("Init almost done\n");
	CONTROLLER_init_timer();
	printf("\n\n\nInit done\n");
	sei();
	
	MOTOR_find_limits();

	can_msg receive;
	can_msg send;
	uint8_t value;
	int msg_type;
	uint8_t twi_message[1];
	int16_t velocity;
	float encoder_pos;
	int y;
	int u;
	int reference = 127;
	uint8_t joy_pos = 127;
	uint8_t prev_lives = 3;
	uint8_t lives;
	CONTROLLER_set_reference(reference);
	
	while(1){
		CAN_handle_interrupt(&receive);
		
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_JOY_POS_X:
				printf("\n\nReceived joystick position: (%d) \n",receive.data[1]);
				SERVO_set_position(receive.data[1]);
				break;
			case CAN_SLIDER_POS_R:
				printf("\n\nReceived slider pos (x): (%d) \n", receive.data[1]);
				//reference =(float)receive.data[1];
				//printf("\t\t\t Received data before: %d\n", receive.data[1]);
				//printf("\t\t\t Reference before: %d\n", (int)reference);
				reference = CONTROLLER_set_reference(receive.data[1]);
				//printf("\t\t\t Reference after: %d\n", (int)reference);
				break;
			case CAN_TOUCH_BUTTON:
				SOLENOID_pulse(1);
				break;
			case CAN_SPEED:
				MOTOR_find_limits();
				MOTOR_set_max_velocity(receive.data[1]);
				break;
			default:
				break;
		}
		
		//
		//lives = COUNT_SCORE_get();
		//if(lives != prev_lives){
			//send.id = ATmega2560_ID;
			//send.data[0] = CAN_LIVES;
			//send.data[1] = lives;
			//send.length = 2;
			//CAN_msg_send(&send);
			//prev_lives = lives;
		//}
		
		
		y = MOTOR_read_scaled_encoder();
		if (y < 0){ y = 0; }
		if (y > 255){ y = 255; }
		u = CONTROLLER_run(y, reference);
		MOTOR_set_dir(u < 0);
		//printf("\t\t\t Reference: %d\n", (int)reference);
		//printf("\t\t\t Received data: %d\n", receive.data[1]);
		MOTOR_set_velocity((uint8_t)u);		
		

		
		
		
		//_delay_us(500);
		
	}
	
	

	return 0;
}
