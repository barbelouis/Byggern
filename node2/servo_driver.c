/**
 * \file servo_driver.c
 * \brief Servo driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */

#include "sam.h"
#include "uart_and_printf/printf-stdarg.h"
#include "servo_driver.h"
#include "can_controller.h"

#define signal_period 0.02	//Period time 20ms
#define mck 84000000		//master clock frequency
#define devider 84			//Value used to calculate a usable PWM signal
#define clk 1000000			//clk frequency used for the PWM signal ( mck/devider = 1MHZ => easier to work with )
#define start_periode 0.075 //Middle Position of Servo => 1.5mS/20mS

/**
 * \fn void servo_init(void)
 * \brief Initialization of the servo
 */
void servo_init(void)
{

	PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6; //AB-Select Register
	PIOC->PIO_PDR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;	 //PIO Disable Register

	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos); //Peripherals control register
	PMC->PMC_PCER1 |= 0x10;																  //Peripheral(1) clock register

	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(devider);

	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA;

	int CPRD = signal_period * mck / devider; //Channel period register

	PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(CPRD);

	PWM->PWM_CH_NUM[5].PWM_CDTY = (signal_period * clk * (1 - start_periode)); //Channel duty cycle register

	PWM->PWM_ENA = PWM_ENA_CHID5; //Enable of PWM channel
}

/**
 * \fn void servo_set_pos(double duty)
 * \brief Set the position of the servo
 */
void servo_set_pos(double duty)
{
	PWM->PWM_CH_NUM[5].PWM_CDTY = (signal_period * clk * (1 - duty));
}

/**
 * \fn void servo_set(double pulsewidth)
 * \brief Set the position of the servo with the good range
 */
void servo_set(double pulsewidth)
{ //calculation of dutycycle

	double dutycycle;

	if (pulsewidth < 0.0009)
	{
		pulsewidth = 0.0009;
	}
	else if (pulsewidth > 0.0021)
	{
		dutycycle = 0.0021;
	}
	else
	{
		dutycycle = pulsewidth / signal_period;
	}
	servo_set_pos(dutycycle);
}

/**
 * \fn void servo_map(int horizontalposition)
 * \brief Mapping of the servo
 */
void servo_map(int horizontalposition)
{

	double pulsewidth;

	pulsewidth = (horizontalposition * (0.002 - 0.001) / 246) + 0.001;

	if (pulsewidth == 0)
	{
		pulsewidth = 0.001;
	}

	servo_set(pulsewidth);
}

/**
 * \fn void servo_move(char position)
 * \brief Move the servo to Left, Center and Right
 */
void servo_move(char position)
{
	if (position == 'L')
	{
		servo_map(0);
	}
	else if (position == 'C')
	{
		servo_map(128);
	}
	else if (position == 'R')
	{
		servo_map(255);
	}
}
