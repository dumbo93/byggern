/*
 * setup.h
 *
 * Created: 13.09.2017 16:45:24
 *  Author: ingunnjv
 */ 


#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 4915200
#define FOSC 4915200	// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#endif /* SETUP_H_ */