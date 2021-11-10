#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

struct PID_settings
{
   int Kp;
   int Ki;
   int Kd;

}PID;
int pid(int target, int current);


#endif