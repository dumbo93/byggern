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
#include "../../communication_drivers/uart.h"
#include "../../communication_drivers/can.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main( void )
{
	can_msg receive;
	int msg_type;
	int remaining_lives = 3;
	int score = 0;
	char username[NUM_USERNAME_BYTES];
	
	cli();
	UART_Init( MYUBRR );
	ADC_init();
	JOY_init();
	TOUCH_init();
	MENU_init();
	CAN_init();
	TIMER_init();
	SEND2CAN_init();
	
	//printf("Init done\n");
	sei();
	STATE_OPTION_set(menu);

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
				SEND2CAN_send_messages();
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
				_delay_ms(4000);
				HIGHSCORE_get_username(username);
				HIGHSCORE_add_score(score, username, 0);
				
				STATE_OPTION_set(menu);
				MENU_start_menu();
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
					}
					else if (STATE_OPTION_get() == game){
					score = score + TIMER_stop();
					STATE_OPTION_set(game_over);
				}
				break;
			default:
				break;
		}
		_delay_ms(5);
	}
	return 0;
}


