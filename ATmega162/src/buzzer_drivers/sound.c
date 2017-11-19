/*
 * sound.c
 *
 * Created: 18.11.2017 13:46:19
 *  Author: ingunnjv
 */ 

#include <avr/io.h>
#include "../bit_manipulation.h"

//int cycle;
//int cycles;
int sound_on = 0;
uint16_t delay_val;
uint16_t cycle;

void SOUND_init()
{
	// Set PE2 as output
	DDRE |= (1 << PE2);
	
	//Normal port operation, CTC mode, OCR3A as TOP
	TCCR3A &= ~(1 << COM3A1) & ~(1 << COM3A0) & ~(1 << WGM31) & ~(1 << WGM30);
	TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
	
	//Timer0-normal mode and prescaler=64
	TCCR0 |= (1<<WGM01) | (1<<CS01) | (1<<CS00);
	TCCR0 &= ~(1<<WGM00) & ~(1<<CS02);
	
}

void SOUND_start_note(int frequency, int duration)
{
	
	//cycle time in sec
	cycle= frequency*duration;
	SOUND_timer1_start();
	SOUND_timer3_start();
	
	OCR1A = ; 
	OCR3A = cycle;
	
	SOUND_play_note();
}

void SOUND_play_note(void)
{
	// set note high
	set_bit(PORTE, PE2);
	//PORTE |= (1<<PE2);
	sound_on = 1;
}

void SOUND_stop_note(void)
{
	// set note low
	//PORTE &= ~(1<<PE2);
	clear_bit(PORTE, PE2);
	sound_on = 0;
	
}

void SOUND_timer1_start(void)
{
	//Set the compare match interrupt enable
	TIMSK |= (1 << OCIE1A);
}

void SOUND_timer3_start(void)
{
	//Set the compare match interrupt enable
	ETIMSK |= (1 << OCIE3A);
}

int SOUND_timer_stop()
{
	TIMSK &= ~(1 << OCIE1A);
	ETIMSK &= ~(1<< OCIE3A);
}


ISR(TIMER1_COMPA_vect)
{
	if (sound_on)
		SOUND_stop_note();
	else
		SOUND_play_note();
}

ISR(TIMER3_COMPA_vect)
{
	
}


//void SOUND_timer_start()
//{
	////Set the prescaler (finn ut hva den skal være)
	//TCCR3B |= (1 << CS32);
	//TCCR3B &= ~(1 << CS31) & ~(1 << CS30);
	//TCNT3 = 0;
	//cycle = 0;
//}
//
//void SOUND_timer_stop()
//{
	//TCCR3B &= ~(1 << CS32) & ~(1 << CS31) & ~(1 << CS30);
	//
//}
//
//int SOUND_play_note(float duration, float note_frequency)
//{
	//cycles = 2*duration*note_frequency/1000;
	//OCR3A = duration/cycles;
	//SOUND_timer_start();
//}
//
//
//ISR(TIMER3_COMPA_vect)
//{
	//if(cycle < cycles){
		//if (cycle % 2 == 0)
		//PORTE |= (1 << PE2);
		//else
		//PORTE &= ~(1 << PE2);
		//cycle = cycle + 1;
	//}
	//else{
		//PORTE &= ~(1 << PE2);
	//}
//}

