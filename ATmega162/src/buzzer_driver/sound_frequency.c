/*
 * sound_duration.c
 *
 * Created: 19.11.2017 14:00:35
 *  Author: ingunnjv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sound_frequency.h"
#include "sound.h"


int sound_on;

void SOUND_frequency_init(void)
{
	//Timer0-normal mode and prescaler=64
	TCCR0 |= (1<<CS01) | (1<<CS00);
	TCCR0 &= ~(1<<WGM00) & ~(1<<WGM01) & ~(1<<CS02);
}


void SOUND_timer0_start(void)
{
	//Set the compare match interrupt enable
	TIMSK |= (1 << OCIE0);
}


void SOUND_set_sound_on(int on)
{
	sound_on = on;
}


int SOUND_timer0_stop()
{
	TIMSK &= ~(1 << OCIE0);
}


ISR(TIMER0_COMP_vect)
{
	//printf("Timer0 got interrupt\n");
	if (sound_on){
		//printf("Sound on %d\n", sound_on);
		SOUND_stop_note();
	}else{
		//printf("Sound off %d\n", sound_on);
		SOUND_play_note();
	}
}

