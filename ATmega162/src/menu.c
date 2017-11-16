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
	//.name = malloc(20),
	.name = "Main menu\n",
	.parent = NULL,
	.child[0] = &play_game,
	.child[1] = &highscores,
	.child[2] = &settings,
	.child_num = 3,
};

menu_item_info_t play_game = {
	.name = "Play game\n",
	.parent = &main_menu,
	.child[0] = &slow_speed,
	.child[1] = &medium_speed,
	.child[2] = &fast_speed,
	.child_num = 3,
};

menu_item_info_t highscores ={
	.name = "Highscores\n",
	.parent = &main_menu,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t settings ={
	.name = "Settings\n",
	.parent = &main_menu,
	.child[0] = &clear_highscores,
	.child[1] = &contrast_level,
	.child[2] = &invert_screen,
	.child_num = 3,
};

menu_item_info_t slow_speed = {
	.name = "Slow\n",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t medium_speed = {
	.name = "Medium\n",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t fast_speed = {
	.name = "Fast\n",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t clear_highscores ={
	.name = "Clear Highscores\n",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t contrast_level ={
	.name = "Contrast level\n",
	.parent = &settings,
	.child[0] = &contrast_low,
	.child[1] = &contrast_medium,
	.child[2] = &contrast_high,
	.child_num = 3,
};

menu_item_info_t invert_screen ={
	.name = "Invert screen\n",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t contrast_low ={
	.name = "Low\n",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};
menu_item_info_t contrast_medium ={
	.name = "Medium\n",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};
menu_item_info_t contrast_high ={
	.name = "High\n",
	.parent = &contrast_level,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t *current_menu;
menu_item_info_t *current_child;
int line;



void MENU_init( void ){
	current_menu = &main_menu;
	current_child = main_menu.child[0];
	line = 1;
	MENU_print_menu();
	MENU_highlight_item();
	MENU_select_item();
	MENU_navigate();
}


void MENU_print_menu(){
	//printf("her\n");
	OLED_reset();
	OLED_print(current_menu->name, 0);
	//printf("her nå \n");
	if (current_child!= NULL){
		MENU_highlight_item();
	}
	for (int i =0; i < current_menu->child_num; i++){
		//printf("%d \n", current_menu->child_num);
		//printf("in for at child %d \n",i);
		OLED_goto_column(10);
		OLED_print(current_menu->child[i]->name,i+1);
	}
}
int cmpfunc (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}
void MENU_print_highscores(){
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

void MENU_delete_highscores()
{
	
}


void MENU_select_item(){
	//int pressed = JOY_button();
	static int inverted;
	if ((JOY_button() || JOY_get_direction() == RIGHT) && current_child!= NULL){
		if (current_child->child[0] != NULL){
			current_menu = current_child;
			current_child = current_child->child[0];
			line = 1;
			MENU_print_menu();
		}else{
			if(current_child == &clear_highscores){
				MENU_delete_highscores();
			}
			else if(current_child == &contrast_low)
				OLED_set_contrast( LOW_CONTRAST );
			else if(current_child == &contrast_medium)
				OLED_set_contrast( MEDIUM_CONTRAST );
			else if(current_child == &contrast_high)
				OLED_set_contrast( HIGH_CONTRAST );
			else if(current_child == &invert_screen){
				if (!inverted){
					OLED_write_command(SET_INVERSE_DISPLAY);
					inverted = 1;
				}else{
					OLED_write_command(SET_NORMAL_DISPLAY);
					inverted = 0;
				}
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
				MENU_print_highscores();
			}
		}
		while(JOY_button() || JOY_get_direction() == RIGHT){}
	}
}



void MENU_navigate(){
	//JOY_direction_t dir = JOY_get_direction();
	//printf("Direction: %d \n", dir);
	switch (JOY_get_direction()){
		case LEFT:
			while(JOY_get_direction() == LEFT){}
			//printf("LEFT - Current menu: %s \n", current_menu->name);
			if (current_menu->parent != NULL){
				line = 1;
				current_menu = current_menu->parent;
				current_child = current_menu->child[0];
				//printf("LEFT - Current line %d \n", line);
				MENU_print_menu();
			}
			break;
		case UP:
		while(JOY_get_direction() == UP){}
			//printf("UP - Current menu %s \n", current_menu->name);
			if (line > 1){
				line = line - 1;
				current_child = current_menu->child[line - 1];
				//printf("UP - Current line %d \n", line);
				MENU_highlight_item();
				}
			break;
		case DOWN:
		while(JOY_get_direction() == DOWN){}
			//printf("DOWN - Current menu %s \n", current_menu->name);
			if (line < current_menu->child_num){
				line = line + 1;
				current_child = current_menu->child[line - 1];
				//printf("DOWN - Current line %d \n", line);
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
		OLED_print("  ",i);
	}
	
	OLED_pos(line, 0);
	OLED_print_arrow();
}

void MENU_print_pause_screen(int remaining_lives)
{
	OLED_reset();
	OLED_pos(3, 20);
	char* pause_message = "You have ";
	OLED_print(pause_message, 3);
	itoa(remaining_lives, pause_message, 10);
	OLED_print(pause_message, 3);
	pause_message = " lives left\n";
	OLED_print(pause_message, 3);
	OLED_pos(5, 20);
	pause_message = "Press joystick to continue";// the game.";
	OLED_print(pause_message, 5);
}

void MENU_print_game_screen(void){
	OLED_reset();
	OLED_pos(3, 30);
	char* game_message = "Play game :D";
	OLED_print(game_message, 3);
}