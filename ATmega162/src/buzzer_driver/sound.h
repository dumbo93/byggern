/*
 * sound.h
 *
 * Created: 19.11.2017 14:00:59
 *  Author: ingunnjv
 */ 


#ifndef SOUND_H_
#define SOUND_H_

void SOUND_duration_init(void);
void SOUND_start_song(int song);
void SOUND_start_note(float freq, uint8_t dur);
void SOUND_play_note(void);
void SOUND_stop_note(void);
void SOUND_timer3_start(void);
int SOUND_timer3_stop(void);



#endif /* SOUND_H_ */