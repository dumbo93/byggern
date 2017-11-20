/*
 * controller.c
 *
 * Created: 10.11.2017 10:47:36
 *  Author: ingunnjv
 */ 
#include "controller.h"
#include "setup.h"
#include <stdlib.h>
#include <math.h>
#include <avr/interrupt.h>

int Kp = 110; //1.1*100
int Ki = 10; //1*10
int Kd = 100; //Kd * 1000

volatile int run_controller_flag = 0;

void CONTROLLER_init_timer()
{
	// OC3A disconnected. Normal port operation	
	// Normal mode (mode 0) (everything is zero initially)
	
	// Set prescaler to 1/64
	TCCR3B |= (1 << CS31) | (1 << CS30);
	
	//Set the desired output compare match that will generate a timer interrupt
	// Choose dt = 0.1 -> OCR3A = 12500
	OCR3A = 0x30D4;
	
	//Enable output compare interrupt 3A
	TIMSK3 |= (1 << OCIE3A);
}

int CONTROLLER_set_reference(uint8_t reference)
{
	int reff;
	reff = abs(reference - 0xFF); // 255 is rightmost position, 0 is leftmost position
	return reff;
	
}

int CONTROLLER_run(int y, int reference)
{
	static int integral;
	int error;
	static int u;
	static int prev_err;
	int derivative;
	int dt = 1; //0.1*10
	
	switch(run_controller_flag){
		case 0:
			break;
		case 1:
			error = reference - y;
			if (abs(error) > 10){
				integral = integral + error*dt;
			}
			derivative = (error - prev_err)/dt;
			u = Kp*error + Ki*integral + Kd*derivative;
			prev_err = error;
			run_controller_flag = 0;
			break;
			
	}
	return (int)u/100;
	
}

ISR(TIMER3_COMPA_vect){
	TCNT3 = 0;
	run_controller_flag = 1;
}