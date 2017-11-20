/*
 * highscore.c
 *
 * Created: 17.11.2017 08:38:12
 *  Author: stined
 */ 
#include "highscore.h"
#include "drivers/oled.h"
#include "drivers/eeprom.h"
#include "drivers/joystick.h"
#include "setup.h"
#include <util/delay.h>
#include <stdlib.h>

//When we use add_score somewhere else in the project, start = 0
void HIGHSCORE_add_score(uint16_t score, char *name, int start)
{
	highscore_info_t element;
	 for (int i = start; i < MAX_SCORES; i++){
		element = HIGHSCORE_load_from_eeprom(i);
		if  (element.score == 0){
			HIGHSCORE_load_to_eeprom(score, name, i);
			break;
		}
		else if (element.score < score){
			//score take this place and push the rest one back in the list
			HIGHSCORE_add_score(element.score, element.name, i + 1);
			HIGHSCORE_load_to_eeprom(score, name, i);
			break;
		}
		else if (element.score > score){
			if (start == 0 && i == MAX_SCORES-1){
				OLED_reset();
				OLED_pos(4,0);
				OLED_printf(" %s is \n not in the top 6", name);
				_delay_ms(3000);
			}
		}
	 }
}

highscore_info_t HIGHSCORE_load_from_eeprom(int number){
	highscore_info_t user;
	
	uint8_t score_msb = EEPROM_read(NUM_HIGHSCORE_BYTES*number);
	uint8_t score_lsb = EEPROM_read(NUM_HIGHSCORE_BYTES*number + 1);
	user.score = score_msb << 8 | score_lsb;
	
	for (int i = 0; i < NUM_USERNAME_BYTES; i++){
		user.name[i] = EEPROM_read(i + NUM_HIGHSCORE_BYTES*number + NUM_SCORE_BYTES);
	}
	return user;
}

void HIGHSCORE_load_to_eeprom(uint16_t score, char *name, int number){
	uint8_t score_lsb = score & 0xFF;
	uint8_t score_msb = score >> 8;
	EEPROM_write(score_msb, NUM_HIGHSCORE_BYTES*number);
	EEPROM_write(score_lsb, NUM_HIGHSCORE_BYTES*number + 1);
	
	for (int i = 0; i < NUM_USERNAME_BYTES; i++){
		EEPROM_write(name[i], i + NUM_HIGHSCORE_BYTES*number + NUM_SCORE_BYTES);
	}
}


void HIGHSCORE_get_username(char* username)
{
	int i = 0;
	int line = 1;
	int prev_line = 1;
	char ch = 'a';
	HIGHSCORE_print_character_list(ch);
	HIGHSCORE_highlight_letter(line, prev_line);
	
	while(i < NUM_USERNAME_BYTES - 1){
		if (JOY_button()){
			while(JOY_button());
			username[i] = ch;
			i++;
		}
		switch(JOY_get_direction()){
			
			case UP:
			while(JOY_get_direction() == UP){
				if (ch > 'a'){
					ch--;
					if (line == 1)
						HIGHSCORE_print_character_list(ch);
				}
				if (line > 1){
					prev_line = line;
					line--;
				}
				HIGHSCORE_highlight_letter(line, prev_line);
				_delay_ms(200);
			}
			break;
			
			case DOWN:
			while(JOY_get_direction() == DOWN){
				if (ch < 'z'){
					ch++;
					if (line == 7)
						HIGHSCORE_print_character_list(ch - 6);
						//OLED_pos(3,50);
						//OLED_printf("%s",username);
				}
				if (line < 7){
					prev_line = line;
					line++;
				}
				HIGHSCORE_highlight_letter(line, prev_line);
				_delay_ms(200);
			}
			break;
			
			case RIGHT:
			while(JOY_get_direction() == RIGHT);
			username[i] = '\0';
			i = NUM_USERNAME_BYTES - 1;
			
			
			default:
			break;
		}
	}
	username[NUM_USERNAME_BYTES - 1] = '\0';
	
}

void HIGHSCORE_highlight_letter(int line, int prev_line)
{
	OLED_pos(prev_line, 0);
	OLED_printf("  ");
	OLED_pos(line, 0);
	OLED_print_arrow();
	
}

void HIGHSCORE_print_character_list(char start){
	OLED_reset();
	OLED_printf("CHOOSE A NAME   FINISH ->\n");
	for (char c = start; c < start + 7; c++){
		OLED_goto_column(11);
		OLED_printf("%c\n", c);
	}
}

void HIGHSCORE_print()
{
	int max_num_highscores = 5;
	highscore_info_t user;
	OLED_reset();
	OLED_printf("Highscores");
	OLED_pos(1, 0);
	OLED_printf("#  Score");
	OLED_goto_column(55);
	OLED_printf("User\n");
	for (int i = 0; i < max_num_highscores; i++){
		user = HIGHSCORE_load_from_eeprom(i);
		OLED_printf("%d  %d", i+1, user.score);
		OLED_goto_column(55);
		OLED_printf("%s\n",user.name);
		//OLED_goto_column(0);
	}
}


void HIGHSCORE_clear()
{
	for (int i = 0; i < NUM_HIGHSCORE_BYTES*MAX_SCORES; i++){
		EEPROM_write(0, i);
	}
}
