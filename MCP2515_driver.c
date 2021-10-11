#include "/home/louis/Documents/NTNU/TTK4155/Byggern/ADC_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>

void MCP2515_init(){
}

void MCP2515_read(){
        
        DDRB = 0x01;                       // initialize port B
        PORTB &= ~(1 << PINB4);  // SS Low



        ///to complete

        PORTB |= (1 << PINB4); // SS High
}
