/*
 * oled.c
 *
 * Created: 20.09.2017 12:50:42
 *  Author: ingunnjv
 */ 

#include "oled.h"
#include "adc.h"
#include "../memory_mapping.h"
#include <avr/io.h>
#include <stdio.h>
#include "font_normal.h"

volatile uint8_t *oled_cmd = (uint8_t *) OLED_COMMAND_ADDRESS;	// Start address for the OLED command
volatile uint8_t *oled_data = (uint8_t *) OLED_DATA_ADDRESS;	// Start address for the OLED data

void OLED_init( void )
{
	
	OLED_write_command(DISPLAY_OFF);
	OLED_write_command(SEGMENT_REMAP);

	OLED_write_command(SET_COM_PIN_HW_CONFIG);        //common  pads  hardware:  alternative
	OLED_write_command(0x12);						  // 0x12 = bx00010010, meaning A[5] = 0, A[4] = 1
	OLED_write_command(SET_COM_OUT_SCAN_DIR);		  //common output scan direction:com63~com0

	OLED_write_command(SET_MULTIPLEX_RATIO);
	OLED_write_command(0x3f);						  //multiplex  ratio  mode: 63

	OLED_write_command(SET_DISPLAY_CLK_DIV_RATIO_OSC_FREQ);        //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);

	OLED_write_command(SET_CONTRAST_CONTROL);
	OLED_write_command(0x50);

	OLED_write_command(SET_PRECHARGE_PERIOD);         //set  pre-charge  period
	OLED_write_command(0x21);						  //period

	OLED_write_command(SET_MEMORY_ADDRESSING_MODE);
	OLED_write_command(HORIZONTAL_ADDR_MODE);

	OLED_write_command(SET_VCOM_DESELECT_LVL);
	OLED_write_command(0x30);

	OLED_write_command(SELECT_IREF);				  // Master configuration cmd - select external or internal Iref
	OLED_write_command(0x00);						  // 0x00: external, 0x01: internal

	OLED_write_command(ENTIRE_DISPLAY_ON);			  //out  follows  RAM  content

	OLED_write_command(SET_NORMAL_DISPLAY);
	OLED_write_command(DISPLAY_ON);
	
	OLED_reset();
}

void OLED_write_command( uint8_t command )
{
	*oled_cmd = command;
}

void OLED_write_data( uint8_t data )
{
	*oled_data = data;
}

/* SET_COLUMN_ADDRESS: This  triple  byte  command  specifies  column  start  address  and  end  address  of  the  display  data  RAM.  This
command  also  sets  the  column  address  pointer  to  column
start  address.    This  pointer  is  used  to  define  the
current  read/write  column  address  in  graphic  display
data  RAM.
*/
void OLED_goto_column( uint8_t column )
{
	OLED_write_command(SET_COLUMN_ADDRESS);
	OLED_write_command(column);
	OLED_write_command(0x7F);
}

void OLED_goto_line( uint8_t line )
{
	OLED_write_command(SET_PAGE_ADDRESS);
	OLED_write_command(line);
	OLED_write_command(7);
}

void OLED_pos(uint8_t row, uint8_t column)
{
	OLED_goto_line(row);
	OLED_goto_column(column);
}

void OLED_home( void )
{
	// go "home", upper left corner
	OLED_pos(0, 0);
}


void OLED_clear_line( uint8_t line )
{
	// go to start position: first column in this line
	OLED_pos(line, 0);
	
	// go through all columns
	for (uint8_t col = 0; col < NUM_COLUMNS; col++){
		// write 8 bits to each column
		OLED_write_data(0x00);
	}
}

void OLED_reset( void )
{
	// clear all lines
	for (uint8_t line = 0; line < NUM_LINES; line++){
		OLED_clear_line(line);
	}
	
	// go home
	OLED_home();
}


void OLED_set_contrast( uint8_t level )
{
	OLED_write_command(SET_CONTRAST_CONTROL);
	OLED_write_command(level);
}

void OLED_print_char( char *character, uint8_t line)
{	
	printf("Character: %c \n", *character);
	if ((*character) == '\n'){
		//printf("newline\n");
		OLED_pos(line + 1, 0);
	}
	else{
		int i;
		for (i = 0; i < 5; i++){
			OLED_write_data(pgm_read_byte(&font5[*character - ' '][i]));
		}
	}
}

void OLED_print(char *c, uint8_t line)
{
	int i = 0;
	while(c[i] != '\0'){
		//printf("From OLED_print %c \n", c[i]);
		OLED_print_char(&c[i], line);
		i++;
	}
}


void OLED_smiley()
{
	OLED_pos(2,32);
	for (int col = 0; col < 10; col++){
		OLED_write_data(0xFF);
	}
	OLED_pos(2,85);
	for (int col = 0; col < 10; col++){
		OLED_write_data(0xFF);
	}
	
	OLED_pos(4, 32);
	for (int col = 0; col < 63; col++){
		OLED_write_data(0xF0);
	}
	
	OLED_pos(5, 42);
	for (int col = 0; col < 43; col++){
		OLED_write_data(0xFF);
	}
	


	OLED_pos(6, 57);
	for (int col = 0; col < 13; col++){
		OLED_write_data(0xFF);
	}
}
