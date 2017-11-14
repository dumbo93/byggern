/*
 * controller.h
 *
 * Created: 10.11.2017 10:47:47
 *  Author: ingunnjv
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <avr/io.h>

float CONTROLLER_set_reference(uint8_t reference);
uint8_t CONTROLLER_run(float y, float reference);


#endif /* CONTROLLER_H_ */