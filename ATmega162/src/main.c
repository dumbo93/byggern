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

#include <avr/io.h>
#include <util/delay.h>

int main( void ){
	
	UART_Init( MYUBRR );
	JOY_init();
	JOY_position_t pos;
	JOY_direction_t dir;
	int buttonPress = 0;
	
	
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
		
		buttonPress = JOY_button(JOY_BUTTON);
		printf("%d \n", buttonPress);
		
		
	}
	
	return 0;
}
