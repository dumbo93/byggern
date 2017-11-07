/*
 * ir.h
 *
 * Created: 07.11.2017 13:40:34
 *  Author: ingunnjv
 */ 


#ifndef IR_H_
#define IR_H_

#include <avr/io.h>

uint8_t IR_read();
int IR_is_blocked();

#endif /* IR_H_ */