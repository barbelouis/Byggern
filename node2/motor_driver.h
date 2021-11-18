#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include "sam.h"

void motor_init();
void motor_drive_right(int speed);
void motor_drive_left(int speed);
void motor_stop();
uint32_t motor_calibration();
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
motor_go_to(uint32_t x, uint32_t range, uint32_t treshold);
void motor_PID(int target,int range);
int get_range();
void motor_drive(int speed);


#endif