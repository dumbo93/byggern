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

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>

int main( void ){
	
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	JOY_init();
	TOUCH_init();
	OLED_init();
	MENU_init();
	
	
	//OLED_smiley();

	
	//int button = 0;
	//JOY_direction_t test;
	//TOUCH_slider_pos_t slider;
	//printf("Start\n");
	//OLED_reset();
	//char a[15] = "funker dette?\n";
	//OLED_print(a, 1);
	//char b[20] = "funker det naa?\n";
	//OLED_print(b, 2);
	//printf("End\n");
	//char c[20] = "funker dette da?";
	//OLED_print(c, 3);

	//
	//for(uint8_t line = 0; line < NUM_LINES; line = line +1){
		//OLED_pos(line, 0);
		//for (uint8_t col = 0; col < NUM_COLUMNS; col++){
			//OLED_write_data(0xff);
		//}
	//}
	//uint8_t line_nr = 7;
	//OLED_clear_line( line_nr );
	//
	//while (1)
	//{	
		//button = JOY_button();
		//test = JOY_get_direction();
		//slider = TOUCH_get_slider_position();
		//printf("Button pressed: %d \n",button);
		////printf("Button pressed: %d, \t Direction: %d \t Slider left: %d \t Slider right: %d \n",button, test, slider.left_slider, slider.right_slider);
		////printf("Slider left: %d \t Slider right: %d \n",slider.left_slider, slider.right_slider);
	//}
	//

	return 0;
}
