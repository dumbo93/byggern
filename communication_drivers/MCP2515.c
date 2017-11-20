/*
 * MCP2515.c
 *
 * Created: 11.10.2017 12:54:11
 *  Author: ingunnjv
 */ 

#include "MCP2515.h"
#include "spi.h"
#include "uart.h"
#if defined(__AVR_ATmega162__)
#include "../ATmega162/src/setup.h"
#endif
#if defined(__AVR_ATmega2560__)
#include "../ATmega2560/src/setup.h"
#endif
#include <util/delay.h>


uint8_t MCP_init( void )
{
	SPI_init();
	MCP_reset();
	
	uint8_t value = MCP_read(MCP_CANSTAT);
	
	if ((value & MODE_MASK) != MODE_CONFIG){
		//printf("MCP2515 is NOT in configuration mode after reset\n");
		return 1;
	}
	return 0;
}

void MCP_reset( void )
{
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send reset instruction
	SPI_transmit_receive(MCP_RESET);
	_delay_us(200);
	SPI_set_ss(1);
}

uint8_t MCP_read( uint8_t address )
{
	uint8_t received;
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send read instruction
	SPI_transmit_receive(MCP_READ);
	// Send 8-bit address
	SPI_transmit_receive(address);
	// Send dummy data and receive data from MCP2515
	received = SPI_transmit_receive(0);
	SPI_set_ss(1);
	return received;
}

void MCP_write( uint8_t address, uint8_t data )
{
	SPI_set_ss(0);
	SPI_transmit_receive(MCP_WRITE);
	SPI_transmit_receive(address);
	SPI_transmit_receive(data);
	SPI_set_ss(1);
}

//RTS command is either MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2 or MCP_RTS_ALL
void MCP_request_to_send( uint8_t RTS_command )
{
	SPI_set_ss(0);
	SPI_transmit_receive(RTS_command);
	SPI_set_ss(1);
}

uint8_t MCP_read_status()
{
	SPI_set_ss(0);
	SPI_transmit_receive(MCP_READ_STATUS);
	uint8_t status = SPI_transmit_receive(0);
	SPI_set_ss(1);
	
	return status;
}

void MCP_bit_modify( uint8_t address, uint8_t mask, uint8_t data )
{
	SPI_set_ss(0);
	SPI_transmit_receive(MCP_BITMOD);
	
	SPI_transmit_receive(address);
	SPI_transmit_receive(mask);
	SPI_transmit_receive(data);
	
	SPI_set_ss(1);
}