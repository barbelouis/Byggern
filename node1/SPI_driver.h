#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#define DDR_SPI DDRB
#define DD_MISO PINB6
#define DD_MOSI PINB5
#define DD_SCK PINB7
#define DD_SS PINB4

#include <stdint.h>

void SPI_init();
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
void SPI_write(uint8_t data);
uint8_t SPI_read();

#endif