/**
 * \file encoder_driver.c
 * \brief Encoder driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */

#include "encoder_driver.h"
#include "delay.h"

/**
 * \fn void encoder_init()
 * \brief Initialization of the encoder
 */
void encoder_init()
{

	PMC->PMC_PCER0 |= (1 << ID_PIOC);

	//MJ1
	//initialize !OE as output (MJ1)
	PIOD->PIO_PER = PIO_PD0;
	PIOD->PIO_OER = PIO_PD0;
	PIOD->PIO_PUDR = PIO_PD0;

	//initialize !RST as output (MJ1)
	PIOD->PIO_PER = PIO_PD1;
	PIOD->PIO_OER = PIO_PD1;
	PIOD->PIO_PUDR = PIO_PD1;

	//set counter to 0
	PIOD->PIO_CODR = PIO_PD1;
	delayus(100);
	PIOD->PIO_SODR = PIO_PD1;

	//initialize SEL as output (MJ1)
	PIOD->PIO_PER = PIO_PD2;
	PIOD->PIO_OER = PIO_PD2;
	PIOD->PIO_PUDR = PIO_PD2;

	//MJ2
	//initialize D0-7 as intputs (MJ2)

	PIOC->PIO_PER = 0x1fe;
	PIOC->PIO_IFER = 0x1fe;
	PIOC->PIO_PUDR = 0x1fe;
}

/**
 * \fn uint16_t encoder_read()
 * \brief Read the encoder value
 */
uint16_t encoder_read()
{
	//Set !OE low to enable output of encoder
	PIOD->PIO_CODR = PIO_PD0;

	//Set SEL low to get high byte
	PIOD->PIO_CODR = PIO_PD2;

	//wait about 20 microseconds
	delayus(100);
	//Read MSB
	uint8_t msb = ((PIOC->PIO_PDSR) & 0x1ff) >> 1;

	//Set SEL high to get low byte
	PIOD->PIO_SODR = PIO_PD2;

	//wait about 20 microseconds
	delayus(100);
	//Read LSB
	uint8_t lsb = ((PIOC->PIO_PDSR) & 0x1ff) >> 1;

	//Set !OE high to enable output of encoder
	PIOD->PIO_SODR = PIO_PD0;

	uint16_t result = (msb << 8) | lsb;
	return result;
}

/**
 * \fn void encoder_reset()
 * \brief Reset the encoder
 */
void encoder_reset()
{
	//set counter to 0
	PIOD->PIO_CODR = PIO_PD1;
	delayus(100);
	PIOD->PIO_SODR = PIO_PD1;
}