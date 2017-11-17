/*
 * touch_panel.c
 *
 * Created: 20.09.2017 08:45:00
 *  Author: ingunnjv
 */ 

#include "touch_panel.h"
#include "adc.h"
#include "../setup.h"
#include "../bit_manipulation.h"
#include <util/delay.h>

void TOUCH_init( void ){
	
	// Initialize PORT B, pin 1 and 2 as input
	clear_bit(DDRB, PINB1);
	clear_bit(DDRB, PINB2);
	
}

int TOUCH_button( void ){

	if (test_bit(PINB, PB1) || test_bit(PINB, PB2)){
		return 1;
	}
	return 0;
}

TOUCH_slider_pos_t TOUCH_read_adc( void ){
	TOUCH_slider_pos_t pos;
	pos.left_slider = ADC_read(LEFT_SLIDER_CHANNEL);
	_delay_ms(1);
	pos.right_slider = ADC_read(RIGHT_SLIDER_CHANNEL);
	
	return pos;
}

TOUCH_slider_pos_t TOUCH_get_slider_position(){
	TOUCH_slider_pos_t current_pos = TOUCH_read_adc();
	return current_pos;
}		