/*
 * counter.h
 *
 * Created: 01.11.2017 13:32:11
 *  Author: ingunnjv
 */ 


#ifndef COUNTER_H_
#define COUNTER_H_
#include <avr/io.h>

void COUNTER_init();
void COUNTER_set_pulse_width(uint16_t pulse_width);

#endif /* COUNTER_H_ */