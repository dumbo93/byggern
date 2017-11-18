/*
 * highscore.c
 *
 * Created: 17.11.2017 08:38:12
 *  Author: stined
 */ 
#include "highscore.h"
#include "drivers/oled.h"
#include "drivers/eeprom.h"

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
			if (start == 0 && i == 4){
			//print to oled "name did not make it to the highscore"
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


char HIGHSCORE_get_username()
{
	
}

void HIGHSCORE_print()
{
	int max_num_highscores = 5;
	highscore_info_t user;
	OLED_printf("#  Score   User\n");
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
