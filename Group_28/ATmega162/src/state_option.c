/*
 * state_option.c
 *
 * Created: 15.11.2017 13:52:53
 *  Author: ingunnjv
 */ 
#include "state_option.h"

state_t state = menu;
int speed;

void STATE_OPTION_set(state_t new_state)
{
	state = new_state;
}

state_t STATE_OPTION_get(void)
{
	return state;
}

void STATE_OPTION_set_speed(int new_speed)
{
	speed = new_speed;
}

int STATE_OPTION_get_speed(void)
{
	return speed;
}