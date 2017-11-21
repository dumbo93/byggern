/*
 * adc.h
 *
 * Created: 07.11.2017 13:11:56
 *  Author: ingunnjv
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_init_2560( void );
uint8_t ADC_read_2560( void );

#endif /* ADC_H_ */