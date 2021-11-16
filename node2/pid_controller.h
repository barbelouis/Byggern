#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

typedef struct
{
   float Kp;
   float Ki;
   float Kd;
   int previous_error;
   int sum_errors;

}PID_settings;

int PID_controller(int target, int current);


#endif