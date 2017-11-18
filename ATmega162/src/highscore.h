/*
 * highscore.h
 *
 * Created: 17.11.2017 08:38:28
 *  Author: stined
 */ 


#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <avr/io.h>

#define MAX_SCORES 6
#define NUM_SCORE_BYTES 2
#define NUM_USERNAME_BYTES 11
#define NUM_HIGHSCORE_BYTES 14

typedef struct highscore_info highscore_info_t;


typedef struct highscore_info {
	uint16_t score;
	char name[NUM_USERNAME_BYTES];
};

void HIGHSCORE_add_score(uint16_t score,char *name, int start);
highscore_info_t HIGHSCORE_load_from_eeprom(int number);
void HIGHSCORE_load_to_eeprom(uint16_t score, char *name, int number);
char HIGHSCORE_get_username();
void HIGHSCORE_print();
void HIGHSCORE_clear();

#endif /* HIGHSCORE_H_ */