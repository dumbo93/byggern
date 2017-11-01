/*
 * joy2can.c
 *
 * Created: 25.10.2017 10:35:12
 *  Author: ingunnjv
 */ 

#include "joy2can.h"
#include "joystick.h"
#include "../../../communication_drivers/can.h"
#include <stdlib.h>

void JOY2CAN_send_pos()
{
	JOY_position_t pos = JOY_get_position();
	can_msg msg;
	int sign_x = POSITIVE;
	int sign_y = POSITIVE;
	
	msg.id = ATmega162_ID;
	if (pos.x < 0){
		sign_x = NEGATIVE;
		pos.x = abs(pos.x);
	}
	if (pos.y < 0){
		sign_y = NEGATIVE;
		pos.y = abs(pos.y);
	}
	
	
	msg.data[0] = sign_x;
	msg.data[1] = pos.x;
	msg.data[2] = sign_y;
	msg.data[3] = pos.y;
	msg.length = 4;
	CAN_msg_send(&msg);
	printf("\n\nSent message (x, y): %d (%d, %d) %d \n",msg.data[0], msg.data[1], msg.data[3], msg.data[2]);
	printf("Sent id: %d \n", msg.id);
	printf("Sent length: %d  \n", msg.length);
}