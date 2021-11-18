/**
 * \file pid_controller.c
 * \brief PID controller
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */
#include "pid_controller.h"
#include "motor_driver.h"
#include "sam.h"

///Parameters of the PID
static PID_settings PID = {20, 0.8, 0.2, 0, 0, 1000}; // perfect PID: 20,0.8,0.2,0,0,1000

/**
 * \fn int PID_controller(int target, int current)
 * \brief PID controller
 * \param target
 * \param current
 * \return pid_result
 */
int PID_controller(int target, int current)
{
	int error = target - current;
	PID.sum_errors += error;

	int pid_result = error * PID.Kp + PID.sum_errors * PID.Ki + PID.Kd * (error - PID.previous_error);
	PID.previous_error = error;
	if (pid_result > PID.max)
	{
		pid_result = PID.max;
	}
	else if (pid_result < -PID.max)
	{
		pid_result = -PID.max;
	}
	return pid_result;
}
