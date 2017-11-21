/*
 * servo.h
 *
 * Created: 01.11.2017 14:34:04
 *  Author: ingunnjv
 */ 


#ifndef SERVO_H_
#define SERVO_H_

// MAX = TOP*2ms/20ms = 500
// MIN = TOP*1ms/20ms = 250
#define MAX		0x01F4
#define MIN		0x00FA

#define POSITIVE 1
#define NEGATIVE 0

#include <avr/io.h>

void SERVO_set_position(uint8_t pos);

#endif /* SERVO_H_ */