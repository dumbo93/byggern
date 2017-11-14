/*
 * ir.c
 *
 * Created: 07.11.2017 13:40:42
 *  Author: ingunnjv
 */ 

#include "ir.h"
#include "adc_2560.h"

uint8_t IR_read()
{
	static uint8_t values[4];
	values[0] = ADC_read_2560();
	//printf("ADC value: %d\n", values[0]);
	int avg = 0;
	for (int i = 3; i >= 0; i--){
		avg = avg + values[i];
		if (i != 0){
			values[i] = values[i - 1];
		}
	}
	avg = avg / 4;
	return avg;
}

int IR_is_blocked()
{
	uint8_t threshold = 30;
	uint8_t ir_signal = IR_read();
	return (ir_signal > threshold);
}