/*
 * highscore.h
 *
 * Created: 17.11.2017 08:38:28
 *  Author: stined
 */ 


#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <avr/io.h>

#define MAX_SCORES 5
#define NUM_SCORE_BYTES 2
#define NUM_USERNAME_BYTES 12
#define NUM_HIGHSCORE_BYTES 14

typedef struct highscore_info highscore_info_t;


typedef struct highscore_info {
	uint16_t score;
	char username[NUM_USERNAME_BYTES];
};

void HIGHSCORE_add_score(uint16_t score,char *username, int start);
highscore_info_t HIGHSCORE_load_from_sram(int number);
void HIGHSCORE_load_to_sram(uint16_t score, char *username, int number);
char HIGHSCORE_get_username();
void HIGHSCORE_print();
void HIGHSCORE_clear();

#endif /* HIGHSCORE_H_ */