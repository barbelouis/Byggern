#include "/home/louis/Documents/NTNU/TTK4155/Byggern/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/SPI_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>

void MCP2515_init(){
        DDRB = 0x01; // initialize port B
        MCP2515_reset();
}

void MCP2515_read(){
        
        PORTB &= ~(1 << PINB4);  // SS Low


        SPI_MasterTransmit(0x03);  // read instruction send to MCP2515 through SPI
       

       SPI_MasterTransmit(0xff); // send address (CAN ID?)

        PORTB |= (1 << PINB4); // SS High
}

void MCP2515_write(){
        PORTB &= ~(1 << PINB4);  // SS Low


        SPI_MasterTransmit(0x02);  // write instruction send to MCP2515 through SPI

        SPI_MasterTransmit(0xff); // send address (CAN ID?)

        SPI_MasterTransmit(0xff); // send one extra byte
       
        PORTB |= (1 << PINB4); // SS High
}
void MCP2515_request_send(){
        PORTB &= ~(1 << PINB4);  // SS Low
        SPI_MasterTransmit(0x81);  // write instruction send to MCP2515 through SPI
        PORTB |= (1 << PINB4); // SS High
        
}
void MCP2515_read_status(){
        
        PORTB &= ~(1 << PINB4);  // SS Low
        SPI_MasterTransmit(0xa0);  // write instruction send to MCP2515 through SPI
        PORTB |= (1 << PINB4); // SS High
}
void MCP2515_bit_modify(){
        PORTB &= ~(1 << PINB4);  // SS Low
        SPI_MasterTransmit(0x05);  // write instruction send to MCP2515 through SPI
        //to complete?
        PORTB |= (1 << PINB4); // SS High
}
void MCP2515_reset(){
        PORTB &= ~(1 << PINB4);  // SS Low
        SPI_MasterTransmit(0xc0);  // write instruction send to MCP2515 through SPI
        PORTB |= (1 << PINB4); // SS High
}