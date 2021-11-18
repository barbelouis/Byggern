/**
 * \file ADC_driver.c
 * \brief ADC driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */
#include "ADC_driver.h"
#include "sam.h"
#include <stdio.h>
#include "can_controller.h"

static int score = 0;
static int blocked = 0;
int val = 0;
long counter = 0;

/**
 * \fn void ADC_init()
 * \brief ADC initialization
 */
void ADC_init()
{
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;

	//ADC->ADC_WPMR = 0x414443;						//Write Protect Mode Register, disables the write protection the Protect Key is: 0x414443

	ADC->ADC_MR |= ADC_MR_FREERUN_ON; //ADC Mode Register => ON = never wait for any trigger
	ADC->ADC_CHER |= ADC_CHER_CH7;	  //ADC Channel Enable Register => enable Channel 7 = PA16(SAM3X8E) => A0 on the shield (Channel and Pins ar switched)
	ADC->ADC_CR |= ADC_CR_START;	  //ADC Control Register => Begins analog-to-digital convesion
}

/**
 * \fn void ADC_boolean_read()
 * \brief ADC read value
 * \return int value on the ADC
 */
int ADC_boolean_read()
{
	//printf("value: %d\n\r", (int)ADC->ADC_CDR[0]);		//Channel Data Register
	//printf("test: %d\n\r", (int)ADC->ADC_LCDR);		//Last converted data register => not necassairy for the moment
	//printf("value:  %d\n\r", RTT->RTT_VR);
	if (RTT->RTT_VR >= 2)
	{ //internal clock to count the seconds
		counter = 0;
		//printf("value:  %d\n\r", counter);
	}
	val = ADC->ADC_LCDR;
	/*x = RTT->RTT_VR;*/
	//printf("value:  %d\n\r", val);
	//printf("counter:  %d\n\r", counter);
	if (val > 1800 && counter == 0)
	{
		// 		printf("GOAL!!!\n\r");
		// 		score++;
		// 		printf("Score: %d\n\r",score);
		counter = 1;
		RTT->RTT_MR |= RTT_MR_RTTRST;
		return 1;
		//ADC_send_boolean(1);
		//printf("Remove Ball");
		//delay(500000);					//Not so clean
	}
	return 0;
}
