
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include <util/delay.h> 
#include <avr/io.h>
#include <stdio.h>

void SPI_init(){
//SPI mode to 0
SPCR &= ~(1 << CPOL);
SPCR &= ~(1 << CPHA);


}

///extract from the Atmega162 documentation/

void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK) | (1<<DD_SS);
DDR_SPI &= ~(1<<DD_MISO);
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
/// 
//DDRB= 0x01;

}
void SPI_MasterTransmit(char cData)
{

/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
//printf("before while \n");
while(!(SPSR & (1<<SPIF)));
//printf("After while \n");
}


void SPI_SlaveInit(void)
{
/* Set MISO output, all others input */
DDR_SPI = (1<<DD_MISO);
/* Enable SPI */
SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
/* Wait for reception complete */
while(!(SPSR & (1<<SPIF)))
;
/* Return data register */
return SPDR;
}


void SPI_write(uint8_t data ){
    SPI_MasterTransmit(data);
}

uint8_t SPI_read(){
    SPI_MasterTransmit('a');
    return SPDR;
}