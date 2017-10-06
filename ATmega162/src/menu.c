/*
 * menu.c
 *
 * Created: 27.09.2017 13:26:36
 *  Author: ingunnjv
 */ 

#include "menu.h"
#include "drivers/oled.h"
#include "drivers/joystick.h"

#include <stdlib.h>

menu_item_info_t main_menu, play_game, highscores, settings;

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
	.child[0] = NULL,
	.child_num = 0,
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
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t *current_menu;
menu_item_info_t *current_child;



void MENU_init( void ){
	current_menu = &main_menu;
	current_child = main_menu.child[0];
	MENU_print_menu();
	while(1){
		MENU_select_item();
	}

}


void MENU_print_menu(){
	printf("her\n");
	OLED_reset();
	OLED_print(current_menu->name, 0);
	printf("her nå \n");
	for (int i =0; i < current_menu->child_num; i++){
		printf("%d \n", current_menu->child_num);
		printf("in for at child %d \n",i);
		OLED_print(current_menu->child[i]->name,i+1);
	}
}


void MENU_select_item(){
	//int pressed = JOY_button();
	if (JOY_button()){
		current_menu = current_child;
		current_child = current_child->child[0];
		
		MENU_print_menu();
	}
}
//
//
//
//void MENU_navigate( item, current_child ,line){
	//JOY_direction_t dir = JOY_get_direction();
	//if (dir == UP & column > 1){
		//// current_child->prev;
		//MENU_highlighte_item(current_child,  line -1)
		//}else if (dir == DOWN){
		//// current_child->next;
		//MENU_highlighte_item(current_child,  line + 1)
		//}else if (dir == LEFT){
		//MENU_highlighte_item(menu_item_info_t parent,  1)
		//// item->parent;
	//}
	//
//}
//
//
//
