/**
 * \file motor_driver.c
 * \brief Driver of the motor
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */
#include "motor_driver.h"
#include "sam.h"
#include "delay.h"
#include "encoder_driver.h"
#include "pid_controller.h"

static int previous_encoder = 0;
static int range = 0x21e7;

/**
 * \fn void motor_init()
 * \brief Initialization of the motor
 */
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

/**
 * \fn void motor_drive_right(int speed)
 * \brief Drive the motor to the right
 * \param speed
 */
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

/**
 * \fn void motor_drive_left(int speed)
 * \brief Drive the motor to the lefts
 * \param speed
 */
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

/**
 * \fn void motor_stop()
 * \brief stop the motor
 */
void motor_stop()
{
	PIOD->PIO_CODR = PIO_PD9;
}

/**
 * \fn uint32_t motor_calibration()
 * \brief Calibration of the motor
 */
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
	range = encoder_read();
	motor_stop();
	return range;
}

/**
 * \fn int get_range()
 * \brief Calibration of the motor
 */
int get_range()
{
	return range;
}

/**
 * \fn uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
 * \brief mapping of x from [in_min;in_max] to [out_min;out_max]
 * \param x
 * \param in_min
 * \param in_max
 * \param out_min
 * \param out_max
 * \return mapping
 */
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * \fn void motor_PID(int target, int range)
 * \brief Control of the motor with the PID controller
 * \param target
 * \param range
 */
void motor_PID(int target, int range)
{
	int encoder = encoder_read();

	int position = map(encoder, 0, range, 0, 255);
	int pid_result = PID_controller(target, position);

	//int speed= encoder- previous_encoder;
	//previous_encoder=encoder;
	//int speed_target=map(target,0,200,-1000,1000);

	//int pid_speed_result = PID_controller(speed_target,speed);

	motor_drive(pid_result);
}

/**
 * \fn void motor_drive(int speed)
 * \brief Drive the motor to the good direction according to the speed
 * \param speed
 */
void motor_drive(int speed)
{
	if (speed > 0.0)
	{
		//printf("in if\n\r");
		motor_drive_left(speed);
	}
	else
	{
		//printf("in else\n\r");
		motor_drive_right(-speed);
	}
}