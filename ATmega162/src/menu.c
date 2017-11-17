/*
 * menu.c
 *
 * Created: 27.09.2017 13:26:36
 *  Author: ingunnjv
 */ 

#include "menu.h"
#include "state_option.h"
#include "drivers/oled.h"
#include "drivers/joystick.h"
#include "drivers/sram.h"

#include <stdlib.h>
#include <string.h>

menu_item_info_t main_menu, play_game, highscores, settings, slow_speed, medium_speed, fast_speed, clear_highscores, contrast_level, invert_screen,contrast_low,contrast_medium,contrast_high;

menu_item_info_t main_menu ={
	.name = "Main menu",
	.parent = NULL,
	.child[0] = &play_game,
	.child[1] = &highscores,
	.child[2] = &settings,
	.child_num = 3,
};

menu_item_info_t play_game = {
	.name = "Play game",
	.parent = &main_menu,
	.child[0] = &slow_speed,
	.child[1] = &medium_speed,
	.child[2] = &fast_speed,
	.child_num = 3,
};

menu_item_info_t highscores ={
	.name = "Highscores",
	.parent = &main_menu,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t settings ={
	.name = "Settings",
	.parent = &main_menu,
	.child[0] = &clear_highscores,
	.child[1] = &contrast_level,
	.child[2] = &invert_screen,
	.child_num = 3,
};

menu_item_info_t slow_speed = {
	.name = "Slow",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t medium_speed = {
	.name = "Medium",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t fast_speed = {
	.name = "Fast",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t clear_highscores ={
	.name = "Clear Highscores",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t contrast_level ={
	.name = "Contrast level",
	.parent = &settings,
	.child[0] = &contrast_low,
	.child[1] = &contrast_medium,
	.child[2] = &contrast_high,
	.child_num = 3,
};

menu_item_info_t invert_screen ={
	.name = "Invert screen",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t contrast_low ={
	.name = "Low",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};
menu_item_info_t contrast_medium ={
	.name = "Medium",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};
menu_item_info_t contrast_high ={
	.name = "High",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t *current_menu;
menu_item_info_t *current_child;
int line;



void MENU_init( void ){
	OLED_init();
	current_menu = &main_menu;
	current_child = main_menu.child[0];
	line = 1;
	MENU_print_menu();
	MENU_highlight_item();
	MENU_select_item();
	MENU_navigate();
}


void MENU_print_menu(){
	OLED_reset();
	OLED_printf("%s\n",current_menu->name);
	if (current_child!= NULL){
		MENU_highlight_item();
	}
	for (int i =0; i < current_menu->child_num; i++){
		OLED_goto_column(10);
		OLED_printf("%s\n", current_menu->child[i]->name);
	}
}



void MENU_select_item(){
	if ((JOY_button() || JOY_get_direction() == RIGHT) && current_child!= NULL){
		if (current_child->child[0] != NULL){
			current_menu = current_child;
			current_child = current_child->child[0];
			line = 1;
			MENU_print_menu();
		}else{
			if(current_child == &clear_highscores){
				//MENU_clear_highscores();
			}
			else if(current_child == &contrast_low)
				OLED_set_contrast( LOW_CONTRAST );
			else if(current_child == &contrast_medium)
				OLED_set_contrast( MEDIUM_CONTRAST );
			else if(current_child == &contrast_high)
				OLED_set_contrast( HIGH_CONTRAST );
			else if(current_child == &invert_screen){
				OLED_invert_screen();
			}else if(current_child == &slow_speed){
				STATE_OPTION_set_speed(1);
				STATE_OPTION_set(game_init);
			}else if(current_child == &medium_speed){
				STATE_OPTION_set_speed(2);
				STATE_OPTION_set(game_init);
			}else if(current_child == &fast_speed){
				STATE_OPTION_set_speed(3);
				STATE_OPTION_set(game_init);
			}
			else if(current_child == &highscores){
				current_menu = current_child;
				current_child = current_child->child[0];
				line = 1;
				//HIGHSCORE_print();
			}
		}
		while(JOY_button() || JOY_get_direction() == RIGHT){}
	}
}



void MENU_navigate(){

	switch (JOY_get_direction()){
		case LEFT:
			while(JOY_get_direction() == LEFT){}
			if (current_menu->parent != NULL){
				line = 1;
				current_menu = current_menu->parent;
				current_child = current_menu->child[0];
				MENU_print_menu();
			}
			break;
		case UP:
		while(JOY_get_direction() == UP){}
			if (line > 1){
				line = line - 1;
				current_child = current_menu->child[line - 1];
				MENU_highlight_item();
				}
			break;
		case DOWN:
		while(JOY_get_direction() == DOWN){}
			if (line < current_menu->child_num){
				line = line + 1;
				current_child = current_menu->child[line - 1];
				MENU_highlight_item();
				}
			break;
		
		default:
			break;
		
	}
}


void MENU_highlight_item( void )
{
	for (int i = 1; i < current_menu->child_num + 1; i++){
		OLED_pos(i, 0);
		OLED_printf("  ");
	}
	
	OLED_pos(line, 0);
	OLED_print_arrow();
}

void MENU_print_pause_screen(int remaining_lives)
{
	OLED_reset();
	OLED_pos(3, 20);
	OLED_printf("You have %d lives left\n", remaining_lives);

	OLED_pos(5, 20);
	OLED_printf("Press joystick");

}

void MENU_print_game_screen(void){
	OLED_reset();
	OLED_pos(3, 30);
	OLED_printf("Play game :D");
}

void MENU_print_game_over_screen(int score){
	OLED_reset();
	OLED_pos(3, 30);
	OLED_printf("Game over...\n");
	OLED_printf("You lasted %d seconds", score);
}