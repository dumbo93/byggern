/*
 * can.h
 *
 * Created: 11.10.2017 14:43:11
 *  Author: ingunnjv
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>

typedef struct can_msg{
	unsigned int id;
	uint8_t length;		// max 8
	uint8_t data[8];
	}can_msg;
	
enum interrupt_flags {no_flag, RX0, RX1};

#define ATmega162_ID	1
#define ATmega2560_ID	2

void CAN_init();
void CAN_msg_send(can_msg *message);
void CAN_msg_receive(can_msg *msg, uint8_t reg);
void CAN_handle_interrupt(can_msg *msg);

#endif /* CAN_H_ */