/*
 * motor.c
 *
 * Created: 08.11.2017 13:53:07
 *  Author: ingunnjv
 */ 
#include <avr/io.h>
#include "motor.h"
#include "twi_handler.h"
#include "TWI_Master.h"
#include "../setup.h"
#include <util/delay.h>

uint8_t max_velocity = 0x50;


void MOTOR_init()
{
	TWI_Master_Initialise();
	// Set MJ1 pins as output
	// PH4 = EN, PH1 = DIR
	DDRH |= (1 << PH4) | (1 << PH1);
	
	// Enable motor and select direction in MJ1
	PORTH |= (1 << PH4) | (1 << PH1);
	
	//Setup encoder
	// Set MJ2 pins as input
	DDRK = 0x00;
	
	// Set some MJ1 pins to output, PH3 = SEL, PH5 = !OE, PH6 = RST
	DDRH |= (1 << PH3) | (1 << PH5)| (1 << PH6);
	
}

void MOTOR_find_limits( void ) 
{
	// *** Calibrate ***
	MOTOR_set_dir(1);
	MOTOR_set_velocity(max_velocity);
	_delay_ms(2000);
	MOTOR_set_velocity((uint8_t)1);
	
	// Reset encoder
	PORTH &= ~(1 << PH6);
	_delay_us(20);
	PORTH |= (1 << PH6);
	
	// Find max encoder value
	MOTOR_set_dir(0);
	MOTOR_set_velocity(max_velocity);
	_delay_ms(2000);
	MOTOR_set_velocity(0);
	MOTOR_max_encoder_value = MOTOR_read_encoder();
	printf("Max encoder value: %d\n", MOTOR_max_encoder_value);
}


void MOTOR_set_dir(int dir)
{
	if (dir == 1){
		// retning høyre
		PORTH |= (1 << PH1);
	}
	else if (dir == 0){
		// retning venstre 
		PORTH &= ~(1 << PH1);
	}
	//else{
		//perror("Invalid motor direction: ");
	//}
}

void MOTOR_set_velocity(uint8_t vel)
{
	uint8_t velocity[1];
	if (vel < max_velocity){ velocity[0] = vel; }
	else{ velocity[0] = max_velocity; }
	TWI_send_address_and_data(velocity, 1);
	
	if(!TWI_Transceiver_Busy() && !TWI_statusReg.lastTransOK){
		printf("TWI error\n");
		TWI_act_on_failure_in_last_transmission( TWI_Get_State_Info() );
	}
}

int16_t MOTOR_read_encoder(void)
{	
	// Set !OE low
	PORTH &= ~(1<<PH5);
	
	// Set SEL low to get high byte(0)
	PORTH &= ~(1<<PH3);
	
	_delay_us(20);
	// Read MSB
	uint8_t encoder_value_MSB;
	encoder_value_MSB = PINK;
	
	
	// Set SEL high to get low byte(1)
	PORTH |= (1<<PH3);
	_delay_us(20);
	
	// Read LSB
	uint8_t encoder_value_LSB;
	encoder_value_LSB = PINK;

	// Set !OE high
	PORTH |= (1<<PH5);
	
	// Process received data
	int16_t total_encoder_value = encoder_value_MSB << 8 | encoder_value_LSB;
	printf("\tEncoder value: %x\n", total_encoder_value);
	
	return total_encoder_value;
	
}

float MOTOR_read_scaled_encoder()
{
	float encoder_value = (float)MOTOR_read_encoder()/MOTOR_max_encoder_value * 255; //Scaled between 0 and 255
	//encoder_value = abs(encoder_value - 255.0); // 255 is rightmost position, 0 is leftmost position
	printf("\tScaled encoder value: %d\n", (int)encoder_value);
	return encoder_value;
}