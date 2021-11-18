/**
 * \file game.c
 * \brief Game library
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "OLED_implementation.h"
#include "joystick_slider_driver.h"
#include "CAN_driver.h"

int current_lives = 3;
static int nb_of_lives = 3;
int goal = 0;

char game_status = 'T';
static int game_ended = 0;
int selected_option = 1;
struct Option current_option;
struct Menu menu;

/*
int selected_option = 1;
struct Option current_option = define_options();
struct Menu menu; //={define_options(),1};

**
 * \fn void game_init()
 * \brief Game initialization
 */

/**
 * \fn void game_init(int lives)
 * \brief game initialization
 * \param int lives
 */
void game_init(int lives)
{
	current_lives = lives;
	nb_of_lives = lives;
	current_option = define_options();
}

/**
 * \fn void game_start()
 * \brief Start game
 */
void game_start()
{

	int difficulty = 7;

	switch (game_status)
	{
	case 'T': //(T)itle
		game_init(3);

		OLED_print_title();
		_delay_ms(1500);

		game_status = 'H';
		OLED_reset();
		if (get_joystick_press())
		{
			OLED_reset();
			game_status = 'H';
		}
		break;

	case 'H': //(H)ome

		menu = make_menu(current_option, selected_option);
		current_option = menu.current_option;
		selected_option = menu.selected_option;
		if (current_option.title == "PLAY")
		{
			game_status = 'A';
		}
		else if (current_option.title == "CALIBRATION")
		{
			struct Message calibration_can_msg;
			calibration_can_msg.data[0] = 0x01;
			calibration_can_msg.id = 0x2b;
			calibration_can_msg.length = 1;
			CAN_send(calibration_can_msg);
			current_option = define_options();
			game_status = 'C';
		}
		break;

	case 'A': //(A)nimation
		OLED_start_animation();
		OLED_reset();
		game_status = 'P';
		break;

	case 'P': //(P)lay
		send_sensors_data_to_node2();
		if (!is_goal())
		{
			OLED_life_menu(nb_of_lives, current_lives, difficulty);
		}

		else
		{
			current_lives--;
			OLED_life_menu(nb_of_lives, current_lives, difficulty);
		}
		if (current_lives == 0)
		{
			OLED_reset();
			game_status = 'O';
		}
		break;

	case 'O': //(O)ver
		OLED_game_over();
		if (get_joystick_press())
		{
			OLED_reset();
			game_status = 'T';
		}
		break;

	case 'C': //(C)alibration
		OLED_reset();
		OLED_calibration();
		game_status = 'H';
		break;
	}
}

/**
 * \fn void new_goal()
 * \brief Update the goal variable
 */
void new_goal()
{
	goal = 1;
}

/**
 * \fn void is_goal()
 * \brief Check the goal variable
 */
int is_goal()
{
	int res = goal;
	goal = 0;
	return res;
}