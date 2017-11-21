/*
 * buzz.c
 *
 * Created: 20.11.2017 18:55:55
 *  Author: ingunnjv
 */ 

#include "frequency_generator.h"
#include "buzz.h"
#include "music.h"
#include "../bit_manipulation.h"

#include <avr/interrupt.h>
#include <stdlib.h>

int sound_on = 0;
int number = 0;
int current_song;

void BUZZ_init(void)
{	
	//Timer3 - ctc mode
	TCCR3A &= ~(1 << COM3A1) & ~(1 << COM3A0) & ~(1 << WGM31) & ~(1 << WGM30);
	TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
	
	//Set the compare match interrupt enable
	ETIMSK |= (1 << OCIE3A);
	
	FREQUENCY_GENERATOR_init();
}

void BUZZ_start_song(int song)
{
	number = 0;
	FREQUENCY_GENERATOR_start(1);
	
	// Set prescaler to 64
	TCCR3B &= ~(1 << CS32);
	TCCR3B |= (1 << CS31) | (1 << CS30);
	current_song = song;
	
	BUZZ_start_note(pgm_read_float(&frequency[current_song][0]),pgm_read_byte(&duration[current_song][0]));
}

void BUZZ_stop_song()
{
	TCCR3B &= ~(1 << CS32) & ~(1 << CS31) & ~(1 << CS30);
	FREQUENCY_GENERATOR_start(0);
	current_song = 2;	
}

void BUZZ_start_note(float freq, uint8_t dur)
{
	uint8_t match;
	OCR3A = dur*49152000/(64000);

	if (freq == 0){
		match = 0;
	}
	else {
		match = 4915200/(64*2*freq);
	}
	FREQUENCY_GENERATOR_play(match);
}


ISR(TIMER3_COMPA_vect)
{
	if (current_song != 2){
		number++;
		switch(current_song){
			case 0: // mario
				if (number == 79){
					number = 0;
				}
				break;
		
			case 1: // star wars
				if (number == 75){
					number = 0;
				}
				break;
		
			default:
				break;
		}
		BUZZ_start_note(pgm_read_float(&frequency[current_song][number]), pgm_read_byte(&duration[current_song][number]));
	}
	else{
		BUZZ_start_note(0, 50);
	}
}