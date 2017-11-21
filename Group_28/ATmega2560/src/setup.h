/*
 * setup.h
 *
 * Created: 20.10.2017 15:25:26
 *  Author: ingunnjv
 */ 


#ifndef SETUP_H_
#define SETUP_H_

#define F_CPU 16000000
#define FOSC 16000000	// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


#endif /* SETUP_H_ */