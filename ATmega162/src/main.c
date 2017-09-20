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

#include <avr/io.h>
#include <util/delay.h>

int main( void ){
	
	UART_Init( MYUBRR );
	JOY_init();
	JOY_position_t pos;
	JOY_direction_t dir;
	int buttonPress_l = 0;
	int buttonPress_r = 0;
	
	TOUCH_slider_pos_t slider_pos;
	
	
	while(1){
		/*
		pos = JOY_get_position();
		
		dir = JOY_get_direction();
		printf("Y: %d %% \t X: %d %% \t Direction: %d \n", pos.y, pos.x, dir);
		*/
		
		/*
		int posY = ADC_read(Y_POS_CHANNEL);
		_delay_ms(1);
		int posX = ADC_read(X_POS_CHANNEL);
		printf("Y: %d %% \t X: %d %%\n", (int)posY, (int)posX);
		*/
		
		buttonPress_l = TOUCH_button(LEFT_BUTTON);
		buttonPress_r = TOUCH_button(RIGHT_BUTTON);
		//printf("Left: %d \t Right %d \n", buttonPress_l, buttonPress_r);
		
		slider_pos = TOUCH_get_slider_position();
		printf("Left slider: %d \t Right slider: %d \n", slider_pos.left_slider, slider_pos.right_slider);
		
		
	}
	
	return 0;
}
