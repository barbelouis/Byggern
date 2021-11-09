#include "motor_driver.h"

void motor_init()
{
	//DACC->DACC_CR_SWRST=0x00000001;
	//mode register
	
	//power management
	//PMC ID:5 p38
	//DACC ID:38 =0b00100110= 0x26
	PMC->PMC_PCR= 0x10001026;
	DACC->DACC_WPMR = 0x44414300;
	DACC->DACC_MR = 0x01110110;
	DACC->DACC_ACR = 0x0000000f;

	//set speed

}
void motor_drive()
{
	//enable direction (motorbox datasheet)
	//MJ1 PIN 7: DIR => PIN 30


	//enable motor (motorbox datasheet)
	//MJ1 PIN 6: EN => PIN 32
}
