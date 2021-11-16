#include "pid_controller.h"
#include "motor_driver.h"
#include "sam.h"


static PID_settings PID ={10,0.5,0,0,0,1000};
int PID_controller(int target, int current)
{
	int error = target - current;
	PID.sum_errors += error;
	
	int pid_result = error * PID.Kp + PID.sum_errors* PID.Ki +PID.Kd * (error - PID.previous_error);
	PID.previous_error=error;
	if(pid_result>PID.max){
		pid_result=PID.max;
	}
	else if(pid_result<-PID.max){
		pid_result=-PID.max;
	}
return pid_result;	
	
}


