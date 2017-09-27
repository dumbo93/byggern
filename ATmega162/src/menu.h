/*
 * menu.h
 *
 * Created: 27.09.2017 13:26:44
 *  Author: ingunnjv
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_item_info *menu_item_info_t;

typedef struct menu_item_info {
	char *name;
	menu_item_info_t parent;
	menu_item_info_t children;
	};
	


void MENU_init( void );

#endif /* MENU_H_ */