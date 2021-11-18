/**
 * \file can_controller.c
 * \brief Controller of the CAN
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */
#include "can_controller.h"
#include "motor_driver.h"
#include "game.h"

/**
 * \fn void message_handler(CAN_MESSAGE message)
 * \brief CAN message handler
 */
void message_handler(CAN_MESSAGE message)
{
	switch (message.id)
	{
	case 42:
	{
		printf("in switch\n\r");
		uint8_t joystick_x = message.data[0];
		uint8_t joystick_y = message.data[1];
		uint8_t left_slider = message.data[2];
		uint8_t right_slider = message.data[3];
		uint8_t button = message.data[4];
		set_new_user_input(joystick_x, joystick_y, left_slider, right_slider, button);
		/*
		servo_map(message.data[0]);
		if(message.data[2]==0x1){
		solenoid_hit();
		}
		motor_PID(slider,0x21e7);
		break;
		*/
		break;
	}
	case 43:
	{
		motor_calibration();
	}
	}
}