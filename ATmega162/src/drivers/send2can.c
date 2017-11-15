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

void SEND2CAN_send_joy_pos_x()
{
	static JOY_position_t prev_joy_pos;
	JOY_position_t joy_pos = JOY_read_adc();
	can_msg msg;
	if(abs(joy_pos.x - prev_joy_pos.x) > 5){
		msg.id = ATmega162_ID;
		msg.data[0] = CAN_JOY_POS_X;
		msg.data[1] = joy_pos.x;
		msg.length = 2;
		CAN_msg_send(&msg);
		printf("\n\nSent joystick position (x): (%d) \n",msg.data[1]);
		prev_joy_pos = joy_pos;
	}
}

void SEND2CAN_send_slider_pos()
{
	static TOUCH_slider_pos_t prev_slider_pos;
	TOUCH_slider_pos_t slider_pos = TOUCH_get_slider_position();
	can_msg msg;
	
	if(abs(slider_pos.right_slider - prev_slider_pos.right_slider) > 5){
		msg.id = ATmega162_ID;
		msg.data[0] = CAN_SLIDER_POS_R;
		msg.data[1] = slider_pos.right_slider;
		msg.length = 2;
		CAN_msg_send(&msg);
		printf("\n\nSent slider position: (%d) \n",msg.data[1]);
		prev_slider_pos = slider_pos;
	}
	
}

void SEND2CAN_touch_button_pressed()
{
	static int prev_button_pressed;
	can_msg msg;
	
	int button_pressed = TOUCH_button();
	if(button_pressed == 1 && prev_button_pressed == 0){
		msg.id = ATmega162_ID;
		msg.data[0] = CAN_TOUCH_BUTTON;
		msg.data[1] = button_pressed;
		msg.length = 2;
		CAN_msg_send(&msg);
		printf("\n\nSent button press (x): (%d) \n",msg.data[1]);
	}
	prev_button_pressed = button_pressed;
}

void SEND2CAN_send_speed(int speed){
	can_msg msg;
	msg.id = ATmega162_ID;
	msg.data[0] = CAN_SPEED;
	msg.data[1] = (uint8_t)speed;
	msg.length = 2;
	CAN_msg_send(&msg);
}
