/**
 * \file SPI_driver.c
 * \brief SPI library
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

/**
 * \fn void SPI_init()
 * Extract from the Atmega162 documentation
 * \brief SPI initialization
 */
void SPI_init()
{
    //SPI mode to 0

    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);

    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
    DDR_SPI &= ~(1 << DD_MISO);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

/**
 * \fn void SPI_MasterTransmit(char cData)
 * Extract from the Atmega162 documentation
 * \brief SPI Master transmission
 * \param cData Data to transmit
 */
void SPI_MasterTransmit(char cData)
{

    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    //printf("before while \n");
    while (!(SPSR & (1 << SPIF)))
        ;
    //printf("After while \n");
}

/**
 * \fn SPI_write(uint8_t data)
 * \brief SPI write (encapsulation of SPI_MasterTransmit)
 * \param data Data to transmit
 */
void SPI_write(uint8_t data)
{
    SPI_MasterTransmit(data);
}

/**
 * \fn uint8_t SPI_read()
 * \brief SPI Master transmission
 * \return byte read
 * Extract from the Atmega162 documentation
 */
uint8_t SPI_read()
{
    SPI_MasterTransmit('a');
    return SPDR;
}