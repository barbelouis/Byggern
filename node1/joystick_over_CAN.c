#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include <stdio.h>
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/joystick_slider_driver.h"

void send_joystick_position_to_node2(){

    struct Message joystick_can_msg={0b00000000011,1,get_joystick_direction()};
    CAN_send(joystick_can_msg);

}