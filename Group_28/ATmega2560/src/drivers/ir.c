/*
 * ir.c
 *
 * Created: 07.11.2017 13:40:42
 *  Author: ingunnjv
 */ 

#include "ir.h"
#include "adc_2560.h"

uint8_t IR_read( void )
{
	static uint8_t values[4];
	int avg = 0;
	
	values[0] = ADC_read_2560();
	for (int i = 3; i >= 0; i--){
		avg = avg + values[i];
		if (i != 0){
			values[i] = values[i - 1];
		}
	}
	avg = avg / 4;
	return avg;
}
