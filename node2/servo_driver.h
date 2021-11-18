/*
 * Servo_driver.h
 *
 * Created: 01.11.2021 15:23:30
 *  Author: micheljs
 */

#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

void servo_init(void);
void servo_set_pos(double duty);
void servo_angle(int angle);
void servo_set(double pulsewitdh);
void servo_map(int horizontalposition);
void servo_move(char position);
double change_duty(double current_duty, double increament);
double increase_duty(double current_duty, double increament);
double decrease_duty(double current_duty, double increament);

#endif