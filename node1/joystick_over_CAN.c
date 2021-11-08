/**
 * \file joystick_over_CAN.c
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