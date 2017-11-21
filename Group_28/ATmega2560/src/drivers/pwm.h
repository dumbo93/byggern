/*
 * pwm.h
 *
 * Created: 01.11.2017 13:32:11
 *  Author: ingunnjv
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

void PWM_init( void );
void PWM_set_pulse_width(uint16_t pulse_width);

#endif /* PWM_H_ */