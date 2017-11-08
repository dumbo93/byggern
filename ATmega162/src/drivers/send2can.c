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

void SEND2CAN_send_joy_pos_x()
{
	JOY_position_t pos = JOY_read_adc();
	can_msg msg;
	msg.id = ATmega162_ID;
	msg.data[0] = CAN_JOY_POS_X;
	msg.data[1] = pos.x;
	msg.length = 2;
	CAN_msg_send(&msg);
	printf("\n\nSent joystick position (x): (%d) \n",msg.data[1]);
	printf("Sent id: %d \n", msg.id);
	printf("Sent length: %d  \n", msg.length);
}

void SEND2CAN_send_slider_pos()
{
	TOUCH_slider_pos_t pos = TOUCH_get_slider_position();
	
	can_msg msg;
	msg.id = ATmega162_ID;
	msg.data[0] = CAN_SLIDER_POS_R;
	msg.data[1] = pos.right_slider;
	msg.length = 2;
	CAN_msg_send(&msg);
	printf("\n\nSent slider position: (%d) \n",msg.data[1]);
}