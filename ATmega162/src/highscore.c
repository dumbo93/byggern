/*
 * highscore.c
 *
 * Created: 17.11.2017 08:38:12
 *  Author: stined
 */ 
#include "highscore.h"
#include "drivers/oled.h"
#include "drivers/sram.h"

#include <stdlib.h>

void HIGHSCORE_add_score(uint16_t score,char *username, int start)
{
	highscore_info_t element;
	 for (int i = start; i<MAX_SCORES ;i++){
		element = HIGHSCORE_load_from_sram(i);
		if  (element.score == NULL){
			HIGHSCORE_load_to_sram(score, username, i);
			break;
		}
		else if (element.score < score){
			//score take this place and push the rest one back in the list
			HIGHSCORE_add_score(element.score, element.username, i+1);
			HIGHSCORE_load_to_sram(score, username, i);
			break;
		}
		else if (element.score > score){
			if (start == 0 && i == 4){
			//print to oled "username did not make it to the highscore"
			}
		}
	 }
}

highscore_info_t HIGHSCORE_load_from_sram(int number){
	highscore_info_t user;
	
	uint8_t score_msb = SRAM_retrieve((uint16_t)(NUM_HIGHSCORE_BYTES*number));
	uint8_t score_lsb = SRAM_retrieve((uint16_t)(NUM_HIGHSCORE_BYTES*number+1));
	user.score = score_msb << 8 | score_lsb;
	
	for (int i = NUM_HIGHSCORE_BYTES*number + NUM_SCORE_BYTES; i < NUM_HIGHSCORE_BYTES*number + NUM_HIGHSCORE_BYTES-1; i++){
		
		user.username[i] = SRAM_retrieve((uint16_t)i);
		printf("saving username: %d\n", user.username[i]);
	}
	printf("Return\n");
	return user;
}

void HIGHSCORE_load_to_sram(uint16_t score, char *username, int number){
	uint8_t score_lsb = score & 0xFF;
	uint8_t score_msb = score >> 8;
	SRAM_save(score_msb, (uint16_t)(NUM_HIGHSCORE_BYTES*number));
	SRAM_save(score_lsb, (uint16_t)(NUM_HIGHSCORE_BYTES*number+1));
	
	
	for (int i = NUM_HIGHSCORE_BYTES*number + NUM_SCORE_BYTES; i < NUM_HIGHSCORE_BYTES*number + NUM_HIGHSCORE_BYTES; i++){
		SRAM_save(username[i], (uint16_t)i);
		printf("Loaded to sram: %c\n", SRAM_retrieve((uint16_t)i));
	}
}

/*
char HIGHSCORE_get_username()
{
	
}

void HIGHSCORE_print()
{
	//int max_num_highscores = 5;
	//OLED_reset();
	//OLED_print(current_menu->name, 0);
	//char highscore[2];
	//char number[1];
	//uint8_t scores[max_num_highscores];
	//for (uint8_t i = 0; i < max_num_highscores; i++){
	//scores[(int)i] = SRAM_retrieve(i);
	//}
	////qsort(scores, max_num_highscores, sizeof(uint8_t), cmpfunc);
	//
	//for (uint8_t i = 0; i < max_num_highscores; i++){
	//OLED_goto_column(2);
	//itoa(i+1, number, 10);
	//OLED_print(number, i + 1);
	//
	//OLED_goto_column(20);
	//itoa(scores[i], highscore, 10);
	//strcat(highscore, "\n");
	//printf("%s",highscore);
	//OLED_print(highscore, i+1);
	//}
}

*/
void HIGHSCORE_clear()
{
	for (int i = 0; i < NUM_HIGHSCORE_BYTES*MAX_SCORES; i++){
		SRAM_save(NULL, (uint16_t)i);
	}
}
