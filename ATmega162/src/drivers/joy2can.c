/*
 * joy2can.c
 *
 * Created: 25.10.2017 10:35:12
 *  Author: ingunnjv
 */ 

#include "joy2can.h"
#include "joystick.h"
#include "../../../communication_drivers/can.h"

void JOY2CAN_send_dir()
{
	JOY_direction_t dir = JOY_get_direction();
	can_msg msg = {.id = ATmega162_ID, .data = dir, .length = 1};
	CAN_msg_send(&msg);
}