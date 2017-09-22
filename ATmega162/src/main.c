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
//#include <stdio.h>

int main( void ){
	
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	JOY_init();
	TOUCH_init();
	//OLED_init();
	
	int button = 0;
	JOY_direction_t test;
	TOUCH_slider_pos_t slider;
	//OLED_reset();
	//
	//for(int line = 0; line < NUM_LINES; line++){
		//for (int col = 0; col < NUM_COLUMNS; col++){
			//OLED_write_data(0xFF);
		//}
	
	//OLED_clear_line( 4 );
	while (1)
	{	
		button = JOY_button();
		test = JOY_get_direction();
		slider = TOUCH_get_slider_position();
		//printf("Button pressed: %d \n",button);
		//printf("Button pressed: %d, \t Direction: %d \n",button, test);
		printf("Slider left: %d \t Slider right: %d \n",slider.left_slider, slider.right_slider);
	}
	
	
	
	return 0;
}
