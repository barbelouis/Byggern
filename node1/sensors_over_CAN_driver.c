/**
 * \file sensors_over_CAN.c
 * \brief Send sensors value over the CAN
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include <stdio.h>
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/joystick_slider_driver.h"

/**
 * \fn void send_joystick_position_to_node2()
 * \brief Send the joystick position over the CAN
 */
void send_joystick_position_to_node2()
{

    struct Message joystick_can_msg = {0b00000000011, 1, get_joystick_direction()};
    CAN_send(joystick_can_msg);
}

void send_joystick_analog_horizontal_position_to_node2()
{

    struct Message joystick_can_msg = {0b00000000111, 3, get_joystick_horizontal_analog_position()};
    CAN_send(joystick_can_msg);
}

void send_right_slider_position_to_node2()
{

    struct Message joystick_can_msg = {0b0000000001, 1, get_right_slider_percentage()};
    CAN_send(joystick_can_msg);
}

void send_sensors_data_to_node2()
{
    struct Message joystick_can_msg;
    joystick_can_msg.data[0] = get_joystick_horizontal_analog_position();
    printf("joystick: %x\n", joystick_can_msg.data[0]);
    joystick_can_msg.data[1] = get_joystick_vertical_analog_position();
    joystick_can_msg.data[2] = get_left_slider_analog_position();
    joystick_can_msg.data[3] = get_right_slider_analog_position();
    joystick_can_msg.data[4] = get_joystick_press();
    //printf("Data: %x\n", data);
    joystick_can_msg.id=0x2a;
    joystick_can_msg.length=5;
    //joystick_can_msg = {0x2a, 3, data}; //id=42;
    CAN_send(joystick_can_msg);
}