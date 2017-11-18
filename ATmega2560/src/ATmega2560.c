/*
 * ATmega2560.c
 *
 * Created: 20.10.2017 15:04:51
 *  Author: ingunnjv
 */ 


#include "setup.h"
#include "../../communication_drivers/uart.h"
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
	
	UART_Init( MYUBRR );
	printf("Initializations\n");
	CAN_init();
	COUNTER_init();
	ADC_init_2560();
	MOTOR_init();
	SOLENOID_init();
	CONTROLLER_init_timer();
	printf("\n\n\nInit done\n");
	sei();
	
	MOTOR_find_limits();

	can_msg receive;
	can_msg send;
	int msg_type;
	int y;
	int u;
	int reference = 127;
	int val;
	int prev_value = 0;
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
				reference = CONTROLLER_set_reference(receive.data[1]);
				break;
			case CAN_TOUCH_BUTTON:
				SOLENOID_pulse(1);
				
				break;
			case CAN_SPEED:
				printf("Starting game\n");
				MOTOR_set_max_velocity(receive.data[1]);
				MOTOR_find_limits();
				break;
			default:
				break;
		}
		
		val = IR_read();
		printf("IR val: %d\n", val);
		if (val - prev_value != 0){
			if (val == 0){
				send.id = ATmega2560_ID;
				send.data[0] = CAN_LIVES;
				send.length = 1;
				CAN_msg_send(&send);
				printf("MESSAGE SENT TO NODE 1\n");
			}
			prev_value = val;
		}
		
		y = MOTOR_read_scaled_encoder();
		if (y < 0){ y = 0; }
		if (y > 255){ y = 255; }
		u = CONTROLLER_run(y, reference);
		MOTOR_set_dir(u < 0);
		MOTOR_set_velocity((uint8_t)u);		
	}
	
	return 0;
}
