/*
 * can.c
 *
 * Created: 11.10.2017 14:43:21
 *  Author: ingunnjv
 */ 
#include "can.h"
#include "MCP2515.h"
#include "uart.h"
#include <avr/interrupt.h>

enum interrupt_flags interrupt_flag = no_flag; 


int CAN_init()
{
	MCP_init();
	// Turn mask/filters off
	MCP_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	MCP_bit_modify(MCP_RXB1CTRL, MCP_FILTER_OFF, MCP_FILTER_OFF);
	
	// Rollover enable
	MCP_bit_modify(MCP_RXB0CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	MCP_bit_modify(MCP_RXB1CTRL, MCP_ROLLOVER, MCP_ROLLOVER);
	
	// Set to normal mode
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	uint8_t value = MCP_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_NORMAL){
		return 1;
	}
	
	// Interrupt pin (enable CANINTE.RXnIE)
	MCP_write(MCP_CANINTE, MCP_RX_INT);
	
	#if defined(__AVR_ATmega162__)
	// Low INT0 generates interrupt request
	MCUCR |= (0 << ISC01) | (0 << ISC00);
	GICR |= (1 << INT0);
	#endif

	#if defined(__AVR_ATmega2560__)
	// Low INT2 generates interrupt request
	EICRA |= (0 << ISC21) | (0 << ISC20);
	// Enable external interrupts of INT2
	EIMSK |= (1 << INT2);
	#endif
	return 0;
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
	// RXBnSIDH and RXBnSIDL (id)
	msg->id = (MCP_read(reg + 1) << 3) | (MCP_read(reg + 2) >> 5);
	// bit 0 to 3 are data length code bits. register + 5 is RXBnDLC (data length)
	msg->length = (MCP_read(reg + 5) & 0x0F ); 
		
	int i = 0;
	while( (i < msg->length) && (i < 8) ){
		//RXBnDM (receive buffer)
		msg->data[i] = MCP_read(reg + 6 + i);	
		i++;
	}	
}

void CAN_handle_interrupt(can_msg *msg)
{
	switch(interrupt_flag){
		case no_flag:
			msg->data[0] = CAN_NO_MESSAGE;
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


#if defined(__AVR_ATmega162__)
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
#endif

#if defined(__AVR_ATmega2560__)
ISR(INT2_vect){
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
#endif