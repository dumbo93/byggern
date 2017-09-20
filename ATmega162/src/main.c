/*
 * main.c
 *
 * Created: 11.09.2017 17:32:44
 *  Author: ingunnjv
 */ 
#include "setup.h"
#include "drivers/uart.h"
#include "drivers/sram.h"
#include "drivers/adc.h"
#include "drivers/joystick.h"
#include "drivers/touch_panel.h"
#include "drivers/oled.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main( void ){
	
	UART_Init( MYUBRR );
	OLED_init();
	OLED_reset();
	
	for(int line = 0; line < NUM_LINES; line++){
		for (int col = 0; col < NUM_COLUMNS; col++){
			OLED_write_data(0xFF);
		}
	}
	OLED_clear_line( 4 );
	
	
	
	return 0;
}
