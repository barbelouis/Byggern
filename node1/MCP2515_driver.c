/**
 * \file MCP2515_driver.c
 * \brief MCP2515 library
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

/**
 * \fn uint8_t MCP2515_init()
 * \brief MCP2515 initialization
 * \return 0 if in configuration mode, 1 if not.
 */
uint8_t MCP2515_init()
{
        // DDRB = 0x01; // initialize port B

        //MCP2515_reset();
        ///////////////Extract from the lab documents//////////////////////////

        SPI_init(); // Initialize SPI
        //SPI_MasterInit(); // Initialize SPI Master
        MCP2515_reset(); // Send reset - command
        // Self - test
        uint8_t value = MCP2515_read(MCP_CANSTAT);
        // printf("CANSTAT : %d \r\n",value);

        if ((value & MODE_MASK) != MODE_CONFIG)
        {
                printf(" MCP2515 is NOT in configuration mode after reset !\n");
                return 1;
        }
        return 0;
}

/**
 * \fn uint8_t MCP2515_read ( uint8_t address )
 * \brief MCP2515 read at specified address
 *
 * \param uint8_t address
 * \return value stored at specified the address.
 */
uint8_t MCP2515_read(uint8_t address)
{
        uint8_t result;
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        SPI_write(MCP_READ);     // Send read instruction
        SPI_write(address);      // Send address
        result = SPI_read();     // Read result
        PORTB |= (1 << CAN_CS);  // Deselect CAN - controller
        return result;
}
////////////////////////////////////////////////////////////

/**
 * \fn MCP2515_write_array(uint8_t address, int lenght, uint8_t* data )
 * \brief MCP2515 write an array of a specific lenght from a mentionend address
 *
 * \param uint8_t address
 * \param int lenght
 * \param uint8_t* data
 */
void MCP2515_write_array(uint8_t address, int lenght, uint8_t *data)
{
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        SPI_write(MCP_WRITE);    // Send read instruction
        SPI_write(address);      // Send address
        for (int i = 0; i < lenght; i++)
        {
                SPI_write(data[i]); // send data
        }
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}

/**
 * \fn MCP2515_write(uint8_t address, uint8_t data )
 * \brief MCP2515 write a byte to a specific address
 * \param uint8_t address 
 * \param uint8_t data
 */
void MCP2515_write(uint8_t address, uint8_t data)
{
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        SPI_write(MCP_WRITE);    // Send read instruction
        SPI_write(address);      // Send address
        SPI_write(data);         // send data
        PORTB |= (1 << CAN_CS);  // Deselect CAN - controller
}

/**
 * \fn MCP2515_request_send()
 * \brief MCP2515 request to send the data that were stored in the transmission buffers
 */
void MCP2515_request_send()
{
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        //printf("before SPI write\n");
        SPI_write(MCP_RTS_TX0); // write instruction request send (0x81) to MCP2515 through SPI
        //printf("after SPI write\n");
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}

/**
 * \fn uint8_t MCP2515_read_status()
 * \brief MCP2515 read status
 * \return status
 */
uint8_t MCP2515_read_status()
{

        PORTB &= ~(1 << CAN_CS);    // Select CAN - controller
        SPI_write(MCP_READ_STATUS); // write instruction read status (0xa0) to MCP2515 through SPI
        uint8_t result = SPI_read();
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
        return result;
}

/**
 * \fn MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
 * \brief MCP2515 modify specific bits at specific address
 * \param uint8_t address
 * \param uint8_t mask
 * \param uint8_t data
 */
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        SPI_write(MCP_BITMOD);
        SPI_write(address);
        SPI_write(mask);
        SPI_write(data);
        PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}

/**
 * \fn void MCP2515_reset()
 * \brief MCP2515 reset
 */
void MCP2515_reset()
{
        PORTB &= ~(1 << CAN_CS); // Select CAN - controller
        SPI_write(MCP_RESET);    // write instruction reset (0xc0) to MCP2515 through SPI
        PORTB |= (1 << CAN_CS);  // Deselect CAN - controller
}