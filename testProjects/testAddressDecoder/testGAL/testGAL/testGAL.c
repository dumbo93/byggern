/*
 * testGAL.c
 *
 * Created: 06.09.2017 16:00:15
 *  Author: ingunnjv
 */ 


#include <avr/io.h>

int main(void)
{
	
	// Set port C as output
	// PC3 corresponds to a11, PC2 corresponds to a10 in the address decoder
	DDRC = 0xFF;
	
	/*
	//Test a10, a11 = 0, 0
	PORTC &= ~(1 << PC2);
	PORTC &= ~(1 << PC3);
	
	
	//Test a10, a11 = 0, 1
	PORTC = (1 << PC3);
	
	//Test a10, a11 = 1, 0
	PORTC = (1 << PC2);
	*/
	//Test a10, a11 = 1, 1
	PORTC = (1 << PC2)|(1 << PC3);
	
	return 0;
}