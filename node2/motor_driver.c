#include "motor_driver.h"
#include "sam.h"
#include "delay.h"
#include "encoder_driver.h"

void motor_init()
{
	//DACC->DACC_CR_SWRST=0x00000001;
	//mode register

	//power management
	//PMC ID:5 p38
	//DACC ID:38 =0b00100110= 0x26
	//PMC->PMC_PCR= 0x10001026;
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	/*
	DACC->DACC_WPMR = 0x44414300;
	DACC->DACC_MR = 0x01110110;
	DACC->DACC_ACR = 0x0000000f;
	*/

	PIOD->PIO_PER = PIO_PD10;
	PIOD->PIO_OER = PIO_PD10;
	PIOD->PIO_PUDR = PIO_PD10;
	//PIOD->PIO_OWER = PIO_PD10;

	PIOD->PIO_PER = PIO_PD9;
	PIOD->PIO_OER = PIO_PD9;
	PIOD->PIO_PUDR = PIO_PD9;
	//PIOD->PIO_OWER = PIO_PD9;
	//set speed

	//init DACC
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CHER |= DACC_CHER_CH1;
}
void motor_drive_right(int speed)
{
	//enable direction (motorbox datasheet)
	//MJ1 PIN 7: DIR => PIN 30 =>PD10
	PIOD->PIO_SODR = PIO_PD10;

	//enable motor (motorbox datasheet)
	//MJ1 PIN 6: EN => PIN 32 =>PD9
	PIOD->PIO_SODR = PIO_PD9;

	//set speed
	//DACC->DACC_MR = 0x01110110;
	//DACC->DACC_ACR = 0x0000000f;
	DACC->DACC_CDR = speed;
}

void motor_drive_left(int speed)
{
	//enable direction (motorbox datasheet)
	//MJ1 PIN 7: DIR => PIN 30 =>PD10
	PIOD->PIO_CODR = PIO_PD10;

	//enable motor (motorbox datasheet)
	//MJ1 PIN 6: EN => PIN 32 =>PD9
	PIOD->PIO_SODR = PIO_PD9;

	//set speed
	//DACC->DACC_MR = 0x01110110;
	//DACC->DACC_ACR = 0x0000000f;
	DACC->DACC_CDR = speed; //0x0000003ff;
}

void motor_stop()
{
	PIOD->PIO_CODR = PIO_PD9;
}

uint32_t motor_calibration()
{
	motor_drive_right(900);
	delayms(2000);
	//motor_stop();
	//delayms(1000);
	encoder_reset();
	printf("right: %x", encoder_read());

	motor_drive_left(900);
	delayms(2000);
	//motor_stop();
	//delayms(1000);
	uint32_t range = encoder_read();
	motor_stop();
	return range;
}

uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
motor_go_to(uint32_t x, uint32_t range, uint32_t treshold)
{

	//uint32_t target = map(x, 0, 255, 0, range);
	uint32_t target = x;
	uint32_t encoder_value = encoder_read();
	//while not in treshold
	while (encoder_value < target - treshold || encoder_value > target + treshold)
	{
		if (encoder_value < target)
		{
			printf("Right\n\r");
			motor_drive_left();
			delayms(10);
			motor_stop();
			encoder_value = encoder_read();
		}
		else
		{
			printf("Left\n\r");
			motor_drive_right();
			delayms(10);
			motor_stop();
			encoder_value = encoder_read();
		}
		printf("target: %x | encoder: %x\n\r", target, encoder_value);
		//delayms(500);
	}
}
*/

void motor_PID(int target, int range)
{
	int encoder = encoder_read();
	int position = map(encoder, 0, range, 0, 100);
	int error = target - position;
	int Kp = 25;
	int pid_result = error * Kp;
	printf("encoder: %d | position: %d | erreur: %d\n\r", encoder, position, error);
	if (error > 0.0)
	{
		printf("in if\n\r");
		motor_drive_left(pid_result);
	}
	else
	{
		printf("in else\n\r");
		motor_drive_right(-pid_result);
	}
}

int pid(int target, int current)
{
	int error = target - current;
}