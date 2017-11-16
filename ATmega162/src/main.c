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
	can_msg receive;
	int msg_type;
	int remaining_lives;
	
	cli();
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	printf("\n\n\nInit start\n");
	JOY_init();
	//printf("\n\n\nInit2\n");
	TOUCH_init();
	//printf("\n\n\nInit3\n");
	OLED_init();
	//printf("\n\n\nInit4\n");
	MENU_init();
	//printf("\n\n\nInit5\n");
	//
	SPI_init();
	MCP_init();
	CAN_init();
	//SRAM_init();
	
	printf("Init done\n");
	STATE_OPTION_set(menu);
	sei();
	//SRAM_test();
	
	int i = 0;
	while(1){
		//SRAM_save(100, 34);
		//uint8_t retrieved = SRAM_retrieve(34);
		//printf("Retrieved from SRAM (should be 100): %d\n", retrieved);
		switch (STATE_OPTION_get()){
			case menu:
				MENU_select_item();
				MENU_navigate();
				break;
			case game_init:
				SEND2CAN_send_speed(STATE_OPTION_get_speed());
				//print noe på oled
				STATE_OPTION_set(game);
				MENU_print_game_screen();
				remaining_lives = 3;
				// start timer
			case game:
				SEND2CAN_send_joy_pos_x();
				SEND2CAN_send_slider_pos();
				SEND2CAN_touch_button_pressed();
				//if (i >= 100){
					//for(uint8_t j = 0; j < 5; j++){
						//SRAM_save(99 - j, j);
					//}
					//for (uint8_t j = 0; j < 5; j++){
						//uint8_t score = SRAM_retrieve(j);
						//printf("Score: %d\n", score);
					//}
					
					//STATE_OPTION_set(menu);
				//}
				break;
			case game_pause:
				// pause timer
				if(JOY_button()){
					STATE_OPTION_set(game);
					MENU_print_game_screen();
					//continue timer
				}
				break;
			case game_over:
				//save to highscore?
				//stop timer. 
				//save to highscore? 
					// username and score, place in right place
				STATE_OPTION_set(menu);
				break;
			default:
				STATE_OPTION_set(menu);
				break;
		}
		i++;
		CAN_handle_interrupt(&receive);
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_LIVES:
				remaining_lives = remaining_lives-1;
				if(remaining_lives > 0){
					//pause
					STATE_OPTION_set(game_pause);
					MENU_print_pause_screen(remaining_lives);
					//stop timer temporarily
				}else{
					STATE_OPTION_set(game_over);
					//stop timer and save it somewhere
				}
				break;
			default:
				break;
		}
		
		_delay_ms(1);
	}
	return 0;
}
