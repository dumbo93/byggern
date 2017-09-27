/*
 * menu.c
 *
 * Created: 27.09.2017 13:26:36
 *  Author: ingunnjv
 */ 

#include "menu.h"
#include "drivers/oled.h"

#include <stdlib.h>


void MENU_init( void ){
	
	menu_item_info_t main_menu;
	main_menu->name = malloc(20);
	main_menu->name = "Main menu";
	main_menu->parent = NULL;
	
	printf("%s \n", main_menu->name);

}




