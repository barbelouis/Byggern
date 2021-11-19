/**
 * \file solenoid_driver.c
 * \brief Solenoid driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */

#include "solenoid_driver.h"
#include "sam.h"
#include "delay.h"

/**
 * \fn void soleonid_init()
 * \brief Initialization of the solenoid
 */
void soleonid_init()
{							  //PA2 => A7 on the shield
	PIOA->PIO_PER |= PIO_PA2; //PIO Controller PIO Enable Register => Enables PIO to control PA2 Pin
	PIOA->PIO_OER |= PIO_PA2; //Output Enable => set PA2 as output
							  //PIOA->PIO_SODR |= PIO_PA2;		Set Output Data
	PIOA->PIO_SODR |= PIO_PA2;
}

/**
 * \fn void soleonid_hit()
 * \brief Hit with the solenoid
 */
void solenoid_hit()
{							   //Value from Joystick-Button
	PIOA->PIO_CODR |= PIO_PA2; //PIO Controller Set Output Data => Set the output to 1
	delayms(75);
	PIOA->PIO_SODR |= PIO_PA2; //Set the Output to 0 again so the solenoid goes back to starting position
}