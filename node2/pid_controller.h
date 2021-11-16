#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

struct PID_settings
{
   float Kp;
   float Ki;
   float Kd;
   int previous_error;
   int sum_errors;

}PID;

int pid(int target, int current);


#endif