#include "solenoid_driver.h"
#include "sam.h"
#include "delay.h"
// #include <stdio.h>
// #include <stdlib.h>



void soleonid_init(){					//PA2 => A7 on the shield
	PIOA-> PIO_PER |= PIO_PA2;			//PIO Controller PIO Enable Register => Enables PIO to control PA2 Pin
	PIOA->PIO_OER |= PIO_PA2;			//Output Enable => set PA2 as output
	//PIOA->PIO_SODR |= PIO_PA2;		Set Output Data
	
}

void solenoid_hit(){		//Value from Joystick-Button
	PIOA->PIO_CODR |= PIO_PA2;		//PIO Controller Set Output Data => Set the output to 1
	delayms(200);
	PIOA->PIO_SODR |= PIO_PA2;		//Set the Output to 0 again so the solenoid goes back to starting position
}