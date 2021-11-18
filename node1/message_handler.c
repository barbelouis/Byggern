/*
 * CFile1.c
 *
 * Created: 15.11.2021 16:06:05
 *  Author: micheljs
 */


 
#include "can_driver.h"
#include "game.h"
void message_handler(CAN_MESSAGE message){
	switch(message.id){
	case 41:
		printf("GOAL!!!!\n\r");
		new_goal();
		break;
	}

}

