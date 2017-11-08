/*
 * motor.c
 *
 * Created: 08.11.2017 13:53:07
 *  Author: ingunnjv
 */ 
#include <avr/io.h>

#include "twi_handler.h"
#include "TWI_Master.h"
#include <util/delay.h>

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
	
	DDRH |= (1 << PH3) | (1 << PH5)| (1 << PH6);
	
	PORTH &= ~(1 << PH6);
	_delay_us(20);
	PORTH |= (1 << PH6);
	
}

void MOTOR_set_dir(int dir)
{
	if (dir == 1){
		PORTH |= (1 << PH1);
	}
	else if (dir == 0){
		PORTH &= ~(1 << PH1);
	}
	//else{
		//perror("Invalid motor direction: ");
	//}
}

void MOTOR_set_velocity(uint8_t vel)
{
	uint8_t velocity[1];
	velocity[0] = vel;
	TWI_send_address_and_data(velocity, 1);
	
	if(!TWI_Transceiver_Busy() && !TWI_statusReg.lastTransOK){
		printf("TWI error\n");
		TWI_act_on_failure_in_last_transmission( TWI_Get_State_Info() );
	}
}

void MOTOR_read_encoder(void)
{	
	// Set !OE low
	PORTH &= ~(1<<PH5);
	
	// Set SEL low to get high byte(0)
	PORTH &= ~(1<<PH3);
	
	_delay_us(20);
	//OBS!!
	// Dette fungerer sikkert ikke!! :(
	uint8_t encoder_value[8];
	for (i=0;i<8;i++){
		encoder_value[i] = PINK
	}
	// Set SEL high to get low byte(1)
	PORTH |= (1<<PH3);
	_delay_us(20);
	
}