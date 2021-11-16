/*
 * Servo_driver.c
 *
 * Created: 01.11.2021 15:27:55
 *  Author: micheljs
 */ 

#include "sam.h"
#include "uart_and_printf/printf-stdarg.h"
#include "servo_driver.h"
#include "can_controller.h"


#define signal_period 0.02			//Period time 20ms 
#define mck 84000000				//master clock frequency
#define devider 84					//Value used to calculate a usable PWM signal 
#define clk	1000000					//clk frequency used for the PWM signal ( mck/devider = 1MHZ => easier to work with )
#define start_periode 0.075			//Middle Position of Servo => 1.5mS/20mS


void servo_init(void){
	
	PIOC -> PIO_ABSR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;										//AB-Select Register 
	PIOC -> PIO_PDR |= PIO_PC19B_PWMH5 |PIO_PC18B_PWMH6;										//PIO Disable Register 
	
	PMC -> PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos);		//Peripherals control register 
	PMC -> PMC_PCER1 |= 0x10;																	//Peripheral(1) clock register 
	
	PWM ->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(devider);
	
	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	int CPRD = signal_period * mck	/ devider;													//Channel period register
	
	PWM -> PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(CPRD);
	
	PWM ->PWM_CH_NUM[5].PWM_CDTY = (signal_period*clk*(1-start_periode));						//Channel duty cycle register
	
	PWM -> PWM_ENA = PWM_ENA_CHID5;																//Enable of PWM channel 	
}

	
void servo_set_pos(double duty){
	PWM -> PWM_CH_NUM[5].PWM_CDTY = (signal_period*clk*(1-duty));
	}
	
void servo_set(double pulsewidth){																//calculation of dutycycle
	
	double dutycycle;
	
	if (pulsewidth < 0.0009)
	{
		pulsewidth = 0.0009;
	}
	else if (pulsewidth > 0.0021){
		dutycycle = 0.0021;
	}
	else{
		dutycycle = pulsewidth/signal_period;
	}
	servo_set_pos(dutycycle);
	}
	
void servo_map(int horizontalposition){
	
	double pulsewidth;
	
	pulsewidth = (horizontalposition*(0.002-0.001)/255) + 0.001;
	
	if (pulsewidth == 0)
	{
		pulsewidth = 0.001; 
	}
	
	servo_set(pulsewidth);
}

void servo_move(char position){
	if (position == 'L'){
		servo_map(0);
	}
	else if (position == 'C'){
		servo_map(128);
	}
	else if (position == 'R'){
		servo_map(255);
	}
}


//Extracted from arduino map
/*
double map(double x, double in_min, double in_max, double out_min, double out_max) {			
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	
}


long mapf2(long x, long in_min, long in_max, long out_min, long out_max)
{
	if ((in_max - in_min) > (out_max - out_min)) {
		return (x - in_min) * (out_max - out_min+1) / (in_max - in_min+1) + out_min;
	}
	else
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}

double change_duty(double current_duty, double increment){
	double res = current_duty + increment;
	if(res>0.1){
		res=0.1;
	}
	else if (res<0.05){
		res=0.05;
	}
	servo_drive(res);
	return res;
}


double increase_duty(double current_duty, double increment){
	double res = current_duty + increment;
	if(res>0.1){
		res=0.1;
	}
	//servo_drive(res);
	return res;
}
double decrease_duty(double current_duty, double increment){
	double res = current_duty - increment;
	if (res<0.05){
		res=0.05;
	}
	//servo_drive(res);
	return res;
}
*/