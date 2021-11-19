/**
 * \file message_handler.c
 * \brief Message handler
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include "game.h"

/**
 * \fn void message_handler(CAN_MESSAGE message)
 * \brief Message handler
 * \param CAN_MESSAGE message
 */
void message_handler(CAN_MESSAGE message)
{
	new_goal();
	switch (message.id)
	{
	case 41:
		printf("GOAL!!!!\n\r");
		new_goal();
		break;
	}
}
