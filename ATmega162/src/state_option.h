/*
 * state_option.h
 *
 * Created: 15.11.2017 13:53:18
 *  Author: ingunnjv
 */ 


#ifndef STATE_OPTION_H_
#define STATE_OPTION_H_

typedef enum{menu, game_init, game} state_t;
	
void STATE_OPTION_set(state_t new_state);
state_t STATE_OPTION_get(void);
void STATE_OPTION_set_speed(int new_speed);
int STATE_OPTION_get_speed(void);


#endif /* STATE_OPTION_H_ */