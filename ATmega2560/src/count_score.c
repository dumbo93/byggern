/*
 * count_score.c
 *
 * Created: 07.11.2017 15:33:15
 *  Author: ingunnjv
 */ 
#include "drivers/ir.h"
#include "count_score.h"

int COUNT_SCORE_get(){
	static int lives = 3;
	static uint8_t prev_value;
	
	int value = IR_read();
	
	if (value != prev_value){
		if (value == 0){
			lives--;
			printf("SCORE!! Number of lives left: %d\n", lives);
		}
	}
	prev_value = value;
	return lives;
}

