#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>


uint8_t MCP2515_init(){
       // DDRB = 0x01; // initialize port B

        //MCP2515_reset();
///////////////Extract from the lab documents//////////////////////////
        
        SPI_init () ; // Initialize SPI
        SPI_MasterInit(); // Initialize SPI Master
        MCP2515_reset () ; // Send reset - command
        // Self - test
        uint8_t value = MCP2515_read ( MCP_CANSTAT);
        if (( value & MODE_MASK ) != MODE_CONFIG ) {
        printf (" MCP2515 is NOT in configuration mode after reset !\n");
                return 1;
        }
return 0;
}



uint8_t MCP2515_read ( uint8_t address )
{
uint8_t result ;
PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
SPI_write ( MCP_READ ); // Send read instruction
SPI_write ( address ); // Send address
result = SPI_read () ; // Read result
PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
return result ;
}
////////////////////////////////////////////////////////////

void MCP2515_write(uint8_t address, int lenght, char* data ){
        PORTB &= ~(1 << CAN_CS);  // Select CAN - controller
        SPI_write ( MCP_WRITE ); // Send read instruction 
        SPI_write ( address); // Send address
        for (int i = 0; i < lenght; i++){
        SPI_write(data[i]); // send data
        }
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}
void MCP2515_request_send(){
        PORTB &= ~(1 << CAN_CS);  // Select CAN - controller
        printf("before SPI write\n");
        SPI_write(MCP_RTS_TX0);  // write instruction request send (0x81) to MCP2515 through SPI
        printf("after SPI write\n");
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
        
}
uint8_t MCP2515_read_status(){
        
        PORTB &= ~(1 << CAN_CS);  // Select CAN - controller
        SPI_write(MCP_READ_STATUS);  // write instruction read status (0xa0) to MCP2515 through SPI
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
        return MCP2515_read(0x2c);
}
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
        PORTB &= ~(1 << CAN_CS);  // Select CAN - controller
        SPI_write(MCP_BITMOD);
        SPI_write(address);
        SPI_write(mask);
        SPI_write(data);
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}
void MCP2515_reset(){
        PORTB &= ~(1 << CAN_CS);  // Select CAN - controller
        SPI_write(MCP_RESET);  // write instruction reset (0xc0) to MCP2515 through SPI
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}