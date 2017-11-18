/*
 * main.c
 *
 * Created: 11.09.2017 17:32:44
 *  Author: ingunnjv
 */ 
#include "setup.h"
#include "menu.h"
#include "state_option.h"
#include "highscore.h"
#include "drivers/adc.h"
#include "drivers/joystick.h"
#include "drivers/touch_panel.h"
#include "drivers/send2can.h"
#include "drivers/timer.h"
#include "drivers/oled.h"
#include "../../communication_drivers/uart.h"
#include "../../communication_drivers/can.h"

#include <avr/io.h>
#include <util/delay.h>
//#include <stdio.h>
#include <avr/interrupt.h>



int main( void ){
	can_msg receive;
	int msg_type;
	int remaining_lives = 3;
	int score = 0;
	
	cli();
	// Initializations 
	UART_Init( MYUBRR );
	ADC_init();
	JOY_init();
	TOUCH_init();
	MENU_init();
	CAN_init();
	TIMER_init();
	
	
	printf("Init done\n");
	STATE_OPTION_set(menu);
	sei();
	//HIGHSCORE_clear();
	//HIGHSCORE_add_score(10, "hei",0);
	//HIGHSCORE_add_score(100, "hallo",0);
	//HIGHSCORE_add_score(15, "yo",0);
	//HIGHSCORE_add_score(360, "jippiiii",0);
	//char testname[12];
	//testname[0] = 't';
	//testname[1] = 'e';
	//testname[2] = 's';
	//testname[3] = 't';
	//testname[4] = 't';
	//testname[5] = 'e';
	//testname[6] = 's';
	//testname[7] = 't';
	//testname[8] = 't';
	//testname[9] = 'e';
	//testname[10] = 's';
	////testname[11] = '\0';
	//HIGHSCORE_add_score(83, testname,0);


	
	while(1){

		switch (STATE_OPTION_get()){
			case menu:
				MENU_select_item();
				MENU_navigate();
				break;
			case game_init:
				SEND2CAN_send_speed(STATE_OPTION_get_speed());
				MENU_print_game_screen();
				remaining_lives = 3;
				score = 0;
				TIMER_start();
				STATE_OPTION_set(game);
				break;
			case game:
				SEND2CAN_send_joy_pos_x();
				SEND2CAN_send_slider_pos();
				SEND2CAN_touch_button_pressed();
				break;
			case game_pause:
				if(JOY_button()){
					STATE_OPTION_set(game);
					MENU_print_game_screen();
					TIMER_start();
				}
				break;
			case game_over:
				MENU_print_game_over_screen(score);
				_delay_ms(5000);
				//save to highscore? 
					// username and score, place in right place
				// print a game over screen?
				
				STATE_OPTION_set(menu);
				MENU_init();
				break;
			default:
				STATE_OPTION_set(menu);
				break;
		}
		CAN_handle_interrupt(&receive);
		msg_type = receive.data[0];
		switch(msg_type){
			case CAN_LIVES:
				if(remaining_lives > 1 && STATE_OPTION_get() == game){
					score = score + TIMER_stop();
					remaining_lives = remaining_lives - 1;
					STATE_OPTION_set(game_pause);
					MENU_print_pause_screen(remaining_lives);
				}else if (STATE_OPTION_get() == game){
					score = score + TIMER_stop();
					STATE_OPTION_set(game_over);
					
					//stop timer and save it somewhere
				}
				break;
			default:
				break;
		}
		
		_delay_ms(50);
	}
	return 0;
}
