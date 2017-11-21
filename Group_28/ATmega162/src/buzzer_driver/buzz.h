/*
 * buzz.h
 *
 * Created: 20.11.2017 19:07:23
 *  Author: ingunnjv
 */ 


#ifndef BUZZ_H_
#define BUZZ_H_

#include <avr/io.h>

void BUZZ_init(void);
void BUZZ_start_song(int song);
void BUZZ_start_note(float freq, uint8_t dur);
void BUZZ_stop_song();


#endif /* BUZZ_H_ */