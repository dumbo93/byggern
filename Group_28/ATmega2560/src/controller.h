/*
 * controller.h
 *
 * Created: 10.11.2017 10:47:47
 *  Author: ingunnjv
 */ 

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <avr/io.h>

void CONTROLLER_init_timer( void );
int CONTROLLER_set_reference(uint8_t reference);
int CONTROLLER_run(int y, int reference);

#endif /* CONTROLLER_H_ */