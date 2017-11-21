/*
 * joy2can.c
 *
 * Created: 25.10.2017 10:35:12
 *  Author: ingunnjv
 */ 

#include "send2can.h"
#include "joystick.h"
#include "touch_panel.h"
#include "../../../communication_drivers/can.h"

#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t send2can_interrupt_flag = 0;

void SEND2CAN_init()
{
	// CTC mode, prescaler = 1024
	TCCR2 |= (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20);
	// Synchronous mode
	ASSR &= ~(1 << AS2);
	
	// Enable interrupt
	TIMSK |= (1 << OCIE2);
	
	// Compare match = 240 (f = 20 Hz)
	OCR2 = 0xF0;
}

void SEND2CAN_send_messages()
{
	if (send2can_interrupt_flag){
		SEND2CAN_send_joy_pos_x();
		SEND2CAN_send_slider_pos();
		SEND2CAN_touch_button_pressed();
		send2can_interrupt_flag = 0;
	}
}

void SEND2CAN_send_joy_pos_x()
{
	static JOY_position_t prev_joy_pos;
	can_msg msg;
	
	JOY_position_t joy_pos = JOY_read_adc();
	if(abs(joy_pos.x - prev_joy_pos.x) > 5){
		msg.id = JOYSTICK_ID;
		msg.data[0] = CAN_JOY_POS_X;
		msg.data[1] = joy_pos.x;
		msg.length = 2;
		CAN_msg_send(&msg);
		prev_joy_pos = joy_pos;
	}
}

void SEND2CAN_send_slider_pos()
{
	static TOUCH_slider_pos_t prev_slider_pos;
	can_msg msg;
	
	TOUCH_slider_pos_t slider_pos = TOUCH_get_slider_position();
	if(abs(slider_pos.right_slider - prev_slider_pos.right_slider) > 5){
		msg.id = SLIDER_ID;
		msg.data[0] = CAN_SLIDER_POS_R;
		msg.data[1] = slider_pos.right_slider;
		msg.length = 2;
		CAN_msg_send(&msg);
		prev_slider_pos = slider_pos;
	}
	
}

void SEND2CAN_touch_button_pressed()
{
	static int prev_button_pressed;
	can_msg msg;
	
	int button_pressed = TOUCH_button();
	if(button_pressed == 1 && prev_button_pressed == 0){
		msg.id = TOUCH_BUTTON_ID;
		msg.data[0] = CAN_TOUCH_BUTTON;
		msg.data[1] = button_pressed;
		msg.length = 2;
		CAN_msg_send(&msg);
	}
	prev_button_pressed = button_pressed;
}

void SEND2CAN_send_speed(int speed)
{
	can_msg msg;
	msg.id = GAME_SPEED_ID;
	msg.data[0] = CAN_SPEED;
	msg.data[1] = (uint8_t)speed;
	msg.length = 2;
	CAN_msg_send(&msg);
}

ISR(TIMER2_COMP_vect)
{
	send2can_interrupt_flag = 1;
}

