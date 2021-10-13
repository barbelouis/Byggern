#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#define DDR_SPI DDRB
#define DD_MISO PB6
#define DD_MOSI PB5
#define DD_SCK PB7
#define DD_SS PB4

#include <stdint.h>

void SPI_init();
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_write(uint8_t data);
uint8_t SPI_read();

#endif 