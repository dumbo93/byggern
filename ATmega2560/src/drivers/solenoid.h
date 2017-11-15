/*
 * solenoid.h
 *
 * Created: 15.11.2017 08:19:37
 *  Author: ingunnjv
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#include <avr/io.h>
void SOLENOID_init( void );
void SOLENOID_pulse(uint8_t shoot);


#endif /* SOLENOID_H_ */