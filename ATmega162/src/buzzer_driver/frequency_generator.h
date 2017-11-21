/*
 * frequency_generator.h
 *
 * Created: 19.11.2017 16:38:32
 *  Author: ingunnjv
 */ 


#ifndef FREQUENCY_GENERATOR_H_
#define FREQUENCY_GENERATOR_H_

#include <avr/io.h>

void FREQUENCY_GENERATOR_init(void);
void FREQUENCY_GENERATOR_start(uint8_t start);
void FREQUENCY_GENERATOR_play(uint8_t match);



#endif /* FREQUENCY_GENERATOR_H_ */