/*
 * servo.h
 *
 * Created: 01.11.2017 14:34:04
 *  Author: ingunnjv
 */ 


#ifndef SERVO_H_
#define SERVO_H_

// MAX = TOP*2ms/20ms
// MIN = TOP*1ms/20ms
// 20ms is the period
#define MAX 500
#define NEUTRAL 375
#define MIN 250

#define POSITIVE 1
#define NEGATIVE 0

#include <avr/io.h>

void SERVO_set_position(uint8_t pos);

#endif /* SERVO_H_ */