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
	uint8_t length;
	uint8_t data[8];
	}can_msg;

void CAN_init();


#endif /* CAN_H_ */