/*
 * sram.h
 *
 * Created: 06.09.2017 11:30:33
 *  Author: ingunnjv
 */ 


#ifndef SRAM_H_
#define SRAM_H_
#include <avr/io.h>


void SRAM_init(void);
void SRAM_test(void);
void SRAM_save(uint8_t saved_value, uint16_t address);
uint8_t SRAM_retrieve(uint16_t address);


#endif /* SRAM_H_ */