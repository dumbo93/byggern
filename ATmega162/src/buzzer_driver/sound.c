/*
 * sound.c
 *
 * Created: 18.11.2017 13:46:19
 *  Author: ingunnjv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "../bit_manipulation.h"
#include "sound.h"
#include "sound_frequency.h"
#include "music.h"

int sound_on = 0;
int number = 0;
int timer0_on;
int current_song;

void SOUND_duration_init(void)
{
	// Set PE2 as output
	DDRE |= (1 << PE2);
	
	SOUND_frequency_init();
	//Timer3 - normal mode, prescale = 32
	TCCR3A &= ~(1 << COM3A1) & ~(1 << COM3A0) & ~(1 << WGM31) & ~(1 << WGM30);
	TCCR3B &= ~(1 << WGM33) | (1 << CS30);
	TCCR3B |= (1 << WGM32) | (1 << CS32) | (1 << CS31);
}



void SOUND_start_song(int song)
{
	SOUND_timer0_start();
	timer0_on = 1;
	SOUND_timer3_start();
	current_song = song;
	
	SOUND_start_note(pgm_read_float(&frequency[current_song][0]),pgm_read_byte(&duration[current_song][0]));
}

void SOUND_start_note(float freq, uint8_t dur)
{
	OCR3A = 1000*dur;
	printf("Start note! Freq: %d \t Dur: %d\n", (int)freq, dur);
	if (freq == 0){
		SOUND_stop_note();
		SOUND_timer0_stop();
		timer0_on = 0;
	}
	else {
		OCR0 = 1/freq;
		SOUND_play_note();
	}
}

void SOUND_play_note(void)
{
	// set note high
	set_bit(PORTE, PE2);
	//PORTE |= (1<<PE2);
	SOUND_set_sound_on(1);
}

void SOUND_stop_note(void)
{
	// set note low
	//PORTE &= ~(1<<PE2);
	clear_bit(PORTE, PE2);
	SOUND_set_sound_on(0);
	
}

void SOUND_timer3_start(void)
{
	//Set the compare match interrupt enable
	ETIMSK |= (1 << OCIE3A);
}



int SOUND_timer3_stop(void)
{
	ETIMSK &= ~(1<< OCIE3A);
}

//
ISR(TIMER3_COMPA_vect)
{
	if (!timer0_on){
		SOUND_timer0_start();
		timer0_on = 1;
	}
	number++;
	if (pgm_read_byte(&duration[current_song][number])!=NULL){
		SOUND_start_note(pgm_read_float(&frequency[current_song][number]), pgm_read_byte(&duration[current_song][number]));
	}else{
		number = 0;
		SOUND_start_note(pgm_read_float(&frequency[current_song][number]), pgm_read_byte(&duration[current_song][number]));
	}
}

