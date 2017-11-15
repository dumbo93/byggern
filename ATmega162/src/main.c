/*
 * main.c
 *
 * Created: 11.09.2017 17:32:44
 *  Author: ingunnjv
 */ 
#include "setup.h"
#include "menu.h"
#include "state_option.h"
#include "drivers/sram.h"
#include "drivers/adc.h"
#include "drivers/joystick.h"
#include "drivers/touch_panel.h"
#include "drivers/oled.h"
#include "drivers/send2can.h"
#include "../../communication_drivers/uart.h"
#include "../../communication_drivers/spi.h"
#include "../../communication_drivers/MCP2515.h"
#include "../../communication_drivers/can.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>
#include <avr/interrupt.h>



int main( void ){
	cli();
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	
	JOY_init();
	TOUCH_init();
	OLED_init();
	MENU_init();
	
	SPI_init();
	MCP_init();
	CAN_init();
	
	printf("\n\n\nInit done\n");
	STATE_OPTION_set(menu);
	sei();
	
	while(1){

		switch (STATE_OPTION_get()){
			case menu:
			MENU_select_item();
			MENU_navigate();
				break;
			case game_init:
				SEND2CAN_send_speed(STATE_OPTION_get_speed());
				//print noe på oled
				STATE_OPTION_set(game);
			case game:
				SEND2CAN_send_joy_pos_x();
				SEND2CAN_send_slider_pos();
				SEND2CAN_touch_button_pressed();
				break;
			default:
				STATE_OPTION_set(menu);
				break;
		}
		_delay_ms(1);
	}
	
	

	return 0;
}
