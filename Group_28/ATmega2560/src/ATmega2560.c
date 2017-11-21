/*
 * ATmega2560.c
 *
 * Created: 20.10.2017 15:04:51
 *  Author: ingunnjv
 */ 

#include "../../communication_drivers/uart.h"
#include "../../communication_drivers/can.h"
#include "drivers/pwm.h"
#include "drivers/servo.h"
#include "drivers/adc_2560.h"
#include "drivers/ir.h"
#include "drivers/solenoid.h"
#include "drivers/motor.h"
#include "controller.h"
#include "setup.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main( void ){
	can_msg receive;
	can_msg send;
	int msg_type;
	int y;
	int u;
	int ir_val;
	int prev_ir_val = 0;
	int pos_reference = 127;
	
	cli();
	UART_Init( MYUBRR );
	CAN_init();
	PWM_init();
	ADC_init_2560();
	MOTOR_init();
	SOLENOID_init();
	CONTROLLER_init_timer();
	sei();
	
	MOTOR_find_limits();
	CONTROLLER_set_reference(pos_reference);
	
	while(1){
		CAN_handle_interrupt(&receive);
		
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_JOY_POS_X:
				SERVO_set_position(receive.data[1]);
				break;
			case CAN_SLIDER_POS_R:
				pos_reference = CONTROLLER_set_reference(receive.data[1]);
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
		
		ir_val = IR_read();
		if (ir_val - prev_ir_val != 0){
			if (ir_val == 0){
				send.id = ATmega2560_ID;
				send.data[0] = CAN_LIVES;
				send.length = 1;
				CAN_msg_send(&send);
			}
			prev_ir_val = ir_val;
		}
		
		y = MOTOR_read_scaled_encoder();
		if (y < 0){ y = 0; }
		if (y > 255){ y = 255; }
		u = CONTROLLER_run(y, pos_reference);
		MOTOR_set_dir(u < 0);
		MOTOR_set_velocity((uint8_t)u);		
	}
	
	return 0;
}
