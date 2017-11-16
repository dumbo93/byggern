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
	
	int val = IR_read();
	//printf("IR value: %d\n", val);
	
	if (val != prev_value){
		if (val == 0){
			lives--;
			printf("SCORE!! Number of lives left: %d\n", lives);
		}
	}
	prev_value = val;
	return lives;
}

