/*
 * servo.h
 *
 * Created: 01.11.2017 14:34:04
 *  Author: ingunnjv
 */ 


#ifndef SERVO_H_
#define SERVO_H_


#define MAX 2.1
#define NEUTRAL 1.5
#define MIN 0.9

#define POSITIVE 1
#define NEGATIVE 0

#include <avr/io.h>

void SERVO_set_position(uint8_t pos);

#endif /* SERVO_H_ */