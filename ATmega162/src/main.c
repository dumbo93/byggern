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
#include "menu.h"
#include "drivers/spi.h"
#include "drivers/MCP2515.h"
#include "drivers/can.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>

int main( void ){
	
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	//JOY_init();
	//TOUCH_init();
	//OLED_init();
	//MENU_init();
	SPI_init();
	MCP_init();
	CAN_init();
	
	
	
	

	return 0;
}
