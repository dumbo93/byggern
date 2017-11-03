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
	JOY_position_t pos = JOY_read_adc();
	can_msg msg;
	msg.id = ATmega162_ID;
	msg.data[0] = pos.x;
	msg.data[1] = pos.y;
	msg.length = 2;
	CAN_msg_send(&msg);
	printf("\n\nSent message (x, y): (%d, %d) \n",msg.data[0], msg.data[1]);
	printf("Sent id: %d \n", msg.id);
	printf("Sent length: %d  \n", msg.length);
}