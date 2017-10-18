/*
 * can.c
 *
 * Created: 11.10.2017 14:43:21
 *  Author: ingunnjv
 */ 
#include "can.h"
#include "MCP2515.h"
#include <avr/interrupt.h>

enum interrupt_flags interrupt_flag = no_flag; 

void CAN_init()
{
	// Interrupt pin (enable CANINTE.RXnIE)
	MCP_write(MCP_CANINTE, MCP_RX_INT);
	
	// Falling edge of INT0 generates interrupt request
	MCUCR |= (1 << ISC01) | (0 << ISC00);
	GICR |= (1 << INT0);
	
	//Set to loop-back mode
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}

void CAN_msg_send(can_msg *message)
{
	// Write ID to TXB0SIDH
	MCP_write(MCP_TXB0SIDH, (message->id) >> 3);
	// Write 0 to TXB0SIDL and extended identifier registers
	MCP_write(MCP_TXB0SIDL, (message->id) << 5);
	MCP_write(MCP_TXB0EID8, 0);
	MCP_write(MCP_TXB0EID0, 0);
	
	//Write data length
	MCP_write(MCP_TXB0DLC, message->length);
	
	for (int i = 0; i < message->length; i++){
		MCP_write(MCP_TXB0SIDH + 5 + i, message->data[i] );
	}
	MCP_request_to_send(MCP_RTS_TX0);
}

void CAN_msg_receive(can_msg *msg, uint8_t reg)
{

	msg->id = (MCP_read(reg + 1) << 3) | (MCP_read(reg + 2) >> 5); //RXBnSIDH and RXBnSIDL (id)
	msg->length = (MCP_read(reg + 5) & 0x0F ); // bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
		
	int i = 0;
	while( (i < msg->length) && (i < 8) ){
		msg->data[i] = MCP_read(reg + 6 + i);	//RXBnDM (receive buffer)
		i++;
	}	
	
}

void CAN_handle_interrupt(can_msg *msg)
{
	switch(interrupt_flag){
		case no_flag:
			break;
		case RX0:
			CAN_msg_receive(msg, MCP_RXB0CTRL);
			interrupt_flag = no_flag;
			break;
		case RX1:
			CAN_msg_receive(msg, MCP_RXB1CTRL);
			interrupt_flag = no_flag;
			break;
		default:
			break;
	}
}

ISR(INT0_vect){
	uint8_t interrupt = MCP_read(MCP_CANINTF);

	if (interrupt & MCP_RX0IF){
		interrupt_flag = RX0;
		// clear CANINTF.RX0IF
		MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);
	}
	else if (interrupt & MCP_RX1IF){
		interrupt_flag = RX1;
		// clear CANINTF.RX1IF
		MCP_bit_modify(MCP_CANINTF, 0x02, 0x00);
	}
	
}