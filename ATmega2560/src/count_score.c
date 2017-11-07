/*
 * count_score.c
 *
 * Created: 07.11.2017 15:33:15
 *  Author: ingunnjv
 */ 
#include "drivers/ir.h"
#include "count_score.h"

int COUNT_SCORE_get(){
	static int score;
	static uint8_t prev_value;
	
	int value = IR_read();
	
	if (value != prev_value){
		if (value == 0){
			score++;
			printf("SCORE!! New score is: %d\n", score);
		}
	}
	prev_value = value;
}

