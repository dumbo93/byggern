/*
 * pwm.h
 *
 * Created: 19.11.2017 16:38:32
 *  Author: ingunnjv
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

void PWM_init(void);
void PWM_start(uint8_t start);
void PWM_play(uint8_t match);



#endif /* PWM_H_ */