/*
 * touch_panel.h
 * touch buttons and sliders for USB multifunction card
 *
 * Created: 20.09.2017 08:44:48
 *  Author: ingunnjv
 */ 


#ifndef TOUCH_PANEL_H_
#define TOUCH_PANEL_H_

#define LEFT_BUTTON 0
#define RIGHT_BUTTON 1

#define RIGHT_SLIDER_CHANNEL 2
#define LEFT_SLIDER_CHANNEL 3

typedef struct TOUCH_slider_pos {
	int left_slider;
	int right_slider;
	} TOUCH_slider_pos_t;

void TOUCH_init( void );
int TOUCH_button( void );
TOUCH_slider_pos_t TOUCH_read_adc( void );
TOUCH_slider_pos_t TOUCH_get_slider_position( void );

#endif /* TOUCH_PANEL_H_ */