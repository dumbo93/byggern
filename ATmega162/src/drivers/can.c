/*
 * can.c
 *
 * Created: 11.10.2017 14:43:21
 *  Author: ingunnjv
 */ 
#include "can.h"
#include "MCP2515.h"


void CAN_init()
{
	//Set to loop-back mode
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}

void CAN_msg_send(can_msg *message)
{
	// Write ID to TXB0SIDH
	MCP_write(MCP_TXB0SIDH, message->id);
	// Write 0 to TXB0SIDL and extended identifier registers
	MCP_write(MCP_TXB0SIDL, 0);
	MCP_write(MCP_TXB0EID8, 0);
	MCP_write(MCP_TXB0EID0, 0);
	
	//Write data length
	MCP_write(MCP_TXB0DLC, message->length);
	
	for (uint8_t i = 0; i < message->length; i++){
		MCP_write(MCP_TXB0SIDH + 6 + i, message->data[i] );
	}
	MCP_request_to_send(MCP_RTS_TX0);
}

void CAN_msg_receive()
{
	
}