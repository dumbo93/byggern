/*
 * adc.h
 *
 * Created: 13.09.2017 12:08:18
 *  Author: ingunnjv
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

int ADC_init(void);
uint8_t ADC_read(uint8_t channel);

#endif /* ADC_H_ */