#include "pid_controller.h"


static PID_settings PID ={10,1,1,0,0};
int PID_controller(int target, int range)
{

	int encoder = encoder_read();
	int position = map(encoder, 0, range, 0, 100);
	int error = target - position;
	
	int T=1;
	PID.sum_errors += error;
	PID.Kd=error;
	int pid_result = error * PID.Kp + PID.sum_errors * T* PID.Ki +( PID.Kd / T) * (error - PID.previous_error);
return pid_result;	
	
}


void timer_init(){
	//Programmable Clock 0 Output Enable
	PMC->PMC_PCER1 |= PMC_SCER_PCK0;
	
	PMC_PCK0
}