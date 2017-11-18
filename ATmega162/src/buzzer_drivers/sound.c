/*
 * sound.c
 *
 * Created: 18.11.2017 13:46:19
 *  Author: ingunnjv
 */ 

#include <avr/io.h>

int cycle;
int cycles;

void SOUND_init()
{
	// Set PE2 as output
	DDRE |= (1 << PE2);
	
	//Normal port operation, CTC mode, OCR3A as TOP
	TCCR3A &= ~(1 << COM3A1) & ~(1 << COM3A0) & ~(1 << WGM31) & ~(1 << WGM30);
	TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
	
	//Set the compare match interrupt enable
	ETIMSK |= (1 << OCIE3A);
}

void SOUND_timer_start()
{
	//Set the prescaler (finn ut hva den skal være)
	TCCR3B |= (1 << CS32);
	TCCR3B &= ~(1 << CS31) & ~(1 << CS30);
	TCNT3 = 0;
	cycle = 0;
}

void SOUND_timer_stop()
{
	TCCR3B &= ~(1 << CS32) & ~(1 << CS31) & ~(1 << CS30);
	
}

int SOUND_play_note(float duration, float note_frequency)
{
	cycles = 2*duration*note_frequency/1000;
	OCR3A = duration/cycles;
	SOUND_timer_start();
}


ISR(TIMER3_COMPA_vect)
{
	if(cycle < cycles){
		if (cycle % 2 == 0)
		PORTE |= (1 << PE2);
		else
		PORTE &= ~(1 << PE2);
		cycle = cycle + 1;
	}
	else{
		PORTE &= ~(1 << PE2);
	}
}

