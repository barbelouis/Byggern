#include "pid_controller.h"
#include <time.h>

static PID={1,0,0,0,0};
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