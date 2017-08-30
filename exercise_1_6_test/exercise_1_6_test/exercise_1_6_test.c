/*
 * exercise_1_6_test.c
 *
 * Created: 30.08.2017 14:55:17
 *  Author: ingunnjv
 */ 


#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// port A are output
	DDRA = 1;
	
    while(1)
    {
        //TODO:: Please write your application code 
		// PIN A 0 is set to 1
		PORTA |= (1 << PA0);
		
		_delay_ms(1000);
		
		PORTA &= ~(1 << PA0);
		
		_delay_ms(1000);
		
    }
}