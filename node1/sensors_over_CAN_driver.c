/**
 * \file sensors_over_CAN_driver.c
 * \brief Send sensors value over the CAN
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */

#include "CAN_driver.h"
#include <stdio.h>
#include "joystick_slider_driver.h"

/**
 * \fn void send_sensors_data_to_node2()
 * \brief Send the sensors data over the CAN
 */
void send_sensors_data_to_node2()
{
    struct Message joystick_can_msg;
    joystick_can_msg.data[0] = get_joystick_horizontal_analog_position();
    //  printf("joystick: %x\n", joystick_can_msg.data[0]);
    joystick_can_msg.data[1] = get_joystick_vertical_analog_position();
    joystick_can_msg.data[2] = get_left_slider_analog_position();
    joystick_can_msg.data[3] = get_right_slider_analog_position();
    joystick_can_msg.data[4] = get_joystick_press();
    //printf("Data: %x\n", data);
    joystick_can_msg.id = 0x2a;
    joystick_can_msg.length = 5;
    //joystick_can_msg = {0x2a, 3, data}; //id=42;
    CAN_send(joystick_can_msg);
}