/*
 * menu.h
 *
 * Created: 27.09.2017 13:26:44
 *  Author: ingunnjv
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_item_info menu_item_info_t;

	
typedef struct menu_item_info {
	char *name;
	menu_item_info_t *parent;
	menu_item_info_t *child[7];
	int child_num;
	void (*functionPtr)(void);
};


void MENU_init( void );

void MENU_print_menu();

void MENU_print_highscores();
void MENU_delete_highscores();

void MENU_select_item();

void MENU_navigate();

void MENU_highlight_item( void );

void MENU_print_pause_screen(int remaining_lives);

void MENU_print_game_screen(void);

void MENU_print_game_over_screen(int score);

void MENU_print_cleared_highscores();



#endif /* MENU_H_ */