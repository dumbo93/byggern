/*
 * main.c
 *
 * Created: 11.09.2017 17:32:44
 *  Author: ingunnjv
 */ 

#include "drivers/uart.h"
#include "drivers/sram.h"

int main( void ){

	sram_main();
	// uart_test();
	
	return 0;
}
