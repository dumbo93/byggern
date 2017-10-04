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


void MENU_init( void ){
	
	menu_item_info_t main_menu, play_game, highscores, settings;
	
	menu_item_info_t items[] = {main_menu, play_game, highscores, settings};
	

	main_menu->name = malloc(20);
	main_menu->name = "Main menu\n";
	main_menu->parent = NULL;
	main_menu->child[0] = play_game;
	main_menu->child[1] = highscores;
	main_menu->child[2] = settings;
	
	play_game->name = malloc(20);
	play_game->name = "Play game\n";
	play_game->parent = main_menu;	
	play_game->child[0] = NULL;
	
	highscores->name = malloc(20);
	highscores->name = "Highscores\n";
	highscores->parent = main_menu;	
	highscores->child[0] = NULL;
	
	settings->name = malloc(20);
	settings->name = "Settings\n";
	settings->parent = main_menu;
	settings->child[0] = NULL;	

	
	
	//printf("%s \n", main_menu->name);
	OLED_print(main_menu->name,0);
	//OLED_print(main_menu->child[0]->name,1);
	//OLED_print(main_menu->child->next->name,2);
	//OLED_print(main_menu->child->next->next->name,3);
	//printf("%s \n", main_menu->name);
	//printf("%s \n", main_menu->name);
	//printf("%s \n", main_menu->name);
	
	


}


//void MENU_print_menu(item){
	//OLED_print(item, 0);
	//int i =1;
	//menu_item_info_t head = item->child;
	//while(head != NULL){
		//OLED_print(head, i);
		//head = head->next;
		//i++;
	//}
//}


//void MENU_select_item( item ){
	//int pressed = JOY_button();
	//if (pressed == 1){
		//// item->child
	//}
//}
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
