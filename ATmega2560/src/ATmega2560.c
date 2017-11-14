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
	printf("\n\n\nInit done\n");
	sei();
	
	MOTOR_find_limits();

	can_msg receive;
	uint8_t value;
	int msg_type;
	uint8_t twi_message[1];
	int16_t velocity;
	float encoder_pos;
	float y;
	float u;
	float reference;
	uint8_t prev_data = 0;
	
	while(1){
		CAN_handle_interrupt(&receive);
		
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_JOY_POS_X:
				if (receive.data[1] != prev_data){
					//printf("\n\nReceived slider position: (%d) \n",receive.data[1]);
					SERVO_set_position(receive.data[1]);
					prev_data=receive.data[1];
				}

				break;
			case CAN_SLIDER_POS_R:
				//printf("\n\nReceived joystick pos (x): (%d) \n", receive.data[1]);
				reference =(float)receive.data[1];
				//printf("\t\t\t Received data before: %d\n", receive.data[1]);
				//printf("\t\t\t Reference before: %d\n", (int)reference);
				reference = CONTROLLER_set_reference(receive.data[1]);
				//printf("\t\t\t Reference after: %d\n", (int)reference);
				break;
			case CAN_TOUCH_BUTTON:
				//solenoid
		}
		y = MOTOR_read_scaled_encoder();
		if (y < 0){ y = 0; }
		u = CONTROLLER_run(y, reference);
		MOTOR_set_dir(y > reference);
		//printf("\t\t\t Reference: %.1f\n", (int)reference);
		//printf("\t\t\t Received data: %d\n", receive.data[1]);
		MOTOR_set_velocity(u);		
		

		
		//value = IR_read();
		//printf("\nAvg IR signal: %d\n\n", value);
		//COUNT_SCORE_get();
		
		_delay_us(500);
		
	}
	
	

	return 0;
}
