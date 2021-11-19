/**
 * \file OLED_implementation.c
 * \brief OLED implementation
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include "OLED_implementation.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "OLED_driver.h"

///GAME MENU
static struct Option home = {NULL, "HOME", "Play", "Settings", "", NULL, NULL, NULL};
static struct Option play = {NULL, "PLAY", "easy", "normal", "hard", NULL, NULL, NULL};
static struct Option settings = {NULL, "SETTINGS", "Calibrate", "Credits", "", NULL, NULL, NULL};
static struct Option calibration = {NULL, "CALIBRATION", "", "", "", NULL, NULL, NULL};
static struct Option credits = {NULL, "CREDITS", "Louis .B", "    &", "Michel .S", NULL, NULL, NULL};
static struct Option easy = {NULL, "EASY", "", "", "", NULL, NULL, NULL};
static struct Option normal = {NULL, "NORMAL", "", "", "", NULL, NULL, NULL};
static struct Option hard = {NULL, "HARD", "", "", "", NULL, NULL, NULL};

/**
 * \fn void make_options(char *title, int cursorPosition, char *o1, char *o2, char *o3)
 * \brief Print the options with existing options
 * \param *title Title of the Menu
 * \param *o1 Option 1
 * \param *o2 Option 2
 * \param *o3 Option 3
 */
void make_options(char *title, int cursorPosition, char *o1, char *o2, char *o3)
{

	OLED_goto_line(0);
	OLED_goto_column(1);

	OLED_print(title);

	clean_selected();
	OLED_goto_line(2);
	OLED_goto_column(1);
	if (cursorPosition == 1)
	{
		OLED_print("# ");
	}
	OLED_goto_line(2);
	OLED_goto_column(20);
	OLED_print(o1);

	OLED_goto_line(3);
	OLED_goto_column(1);
	if (cursorPosition == 2)
	{
		OLED_print("# ");
	}
	OLED_goto_line(3);
	OLED_goto_column(20);
	OLED_print(o2);

	OLED_goto_line(4);
	OLED_goto_column(1);
	if (cursorPosition == 3)
	{
		OLED_print("# ");
	}
	OLED_goto_line(4);
	OLED_goto_column(20);
	OLED_print(o3);

	OLED_goto_line(5);
	OLED_goto_column(1);
	if (cursorPosition == 4)
	{
		OLED_print("# ");
	}

	OLED_goto_line(5);
	OLED_goto_column(20);
	///OLED_print("<");
	OLED_test();
}

/**
 * \fn void clean_selected()
 * \brief Remove the "#" that correspond to the selected option
 */
void clean_selected()
{

	for (uint16_t i = 2; i < 6; i++)
	{
		OLED_goto_column(1);
		OLED_goto_line(i);
		OLED_print(" ");
	}
}

/**
 * \fn struct Option define_options()
 * \brief Map different options and sub-options between them.
 * \return struct Option
 */
struct Option define_options()
{

	//GAME OPTIONS MAPPING

	home.previous_option = &home;
	home.next_1 = &play;
	home.next_2 = &settings;
	home.next_3 = &home;

	play.previous_option = &home;
	play.next_1 = &easy;
	play.next_2 = &normal;
	play.next_3 = &hard;

	settings.previous_option = &home;
	settings.next_1 = &calibration;
	settings.next_2 = &credits;
	settings.next_3 = &settings;

	credits.previous_option = &settings;
	credits.next_1 = &credits;
	credits.next_2 = &credits;
	credits.next_3 = &credits;

	// struct Option current_option = home;

	return home;
}

/**
 * \fn struct Menu make_menu(struct Option current_option, int selected_option)
 * \brief Create the menu and change the selected option with the joystick
 * \param current_option Previous selected option
 * \param selected_option Number of the selected option
 * \return struct Menu
 */
struct Menu make_menu(struct Option current_option, int selected_option)
{

	//Define input for joystick push button

	//DDRB &= 0x00;
	//PORTB |= 0x02;

	// int selected_option=1;
	// struct Option current_option=option0;
	printf("in Make MENU");
	print_option(current_option, selected_option);
	char joystick_position = get_joystick_direction();
	//char joystick_position = 'C';
	if (joystick_position == 'T' && selected_option != 1)
	{
		selected_option = selected_option - 1;
	}
	else if (joystick_position == 'T' && selected_option == 1)
	{
		selected_option = 3;
	}
	else if (joystick_position == 'B' && selected_option != 4)
	{
		selected_option = selected_option + 1;
	}
	else if (joystick_position == 'B' && selected_option == 4)
	{
		selected_option = 1;
	}
	else if ((!(PINB & 0x02)) && selected_option == 1)
	{
		current_option = *current_option.next_1;
		OLED_reset();
	}
	else if ((!(PINB & 0x02)) && selected_option == 2)
	{
		current_option = *current_option.next_2;
		OLED_reset();
	}
	else if ((!(PINB & 0x02)) && selected_option == 3)
	{
		current_option = *current_option.next_3;
		OLED_reset();
	}
	else if ((!(PINB & 0x02)) && selected_option == 4)
	{
		current_option = *current_option.previous_option;
		OLED_reset();
	}

	/*
       printf("\n next: ");
       printf(current_option.title);
       printf("\n selected: ");
       printf("%d",selected_option);*/
	struct Menu new_menu = {current_option, selected_option};
	return new_menu;
}

/**
 * \fn void print_option(struct Option option, int selected_option)
 * \brief Print the option with the cursor on the new selected option
 * \param option New selected option
 * \param selected_option Number of the selected option
 */
void print_option(struct Option option, int selected_option)
{

	make_options(option.title, selected_option, option.o_1, option.o_2, option.o_3);
}

/**
 * \fn void OLED_print_title()
 * \brief Print the title screen on the OLED
 */
void OLED_print_title()
{
	for (int i = 0; i < 256; i++)
	{
		OLED_set_brightness(i);
		OLED_goto_line(1);
		OLED_goto_column(33);
		OLED_print("GROUP 40");

		OLED_goto_line(3);
		OLED_goto_column(17);
		OLED_print("Byggern 2021");

		OLED_goto_line(6);
		OLED_goto_column(8);
		OLED_print("Louis & Michel");
		_delay_ms(5);
	}
	for (int i = 256; i >= 0; i--)
	{
		OLED_set_brightness(i);
		OLED_goto_line(1);
		OLED_goto_column(33);
		OLED_print("GROUP 40");

		OLED_goto_line(3);
		OLED_goto_column(17);
		OLED_print("Byggern 2021");

		OLED_goto_line(6);
		OLED_goto_column(8);
		OLED_print("Louis & Michel");
		_delay_ms(5);
	}
}

/**
 * \fn void OLED_game_over()
 * \brief Print the game over screen on the OLED
 */
void OLED_game_over()
{

	for (int i = 0; i < 256; i++)
	{
		OLED_set_brightness(i);

		OLED_goto_line(3);
		OLED_goto_column(28);
		OLED_print("GAME OVER");
		OLED_print_skull_bones(4, 56);
	}

	for (int i = 255; i >= 0; i--)
	{
		OLED_set_brightness(i);
		OLED_goto_line(3);
		OLED_goto_column(28);
		OLED_print("GAME OVER");
		OLED_print_skull_bones(4, 56);
	}
}

/**
 * \fn void OLED_calibration()
 * \brief Print the calibration screen on the OLED
 */
void OLED_calibration()
{

	for (int i = 0; i < 9; i++)
	{
		OLED_goto_line(4);
		OLED_goto_column(10);
		OLED_print("Calibration   ");
		_delay_ms(700);
		OLED_goto_line(4);
		OLED_goto_column(10);
		OLED_print("Calibration.");
		_delay_ms(700);
		OLED_goto_line(4);
		OLED_goto_column(10);
		OLED_print("Calibration..");
		_delay_ms(700);
		OLED_goto_line(4);
		OLED_goto_column(10);
		OLED_print("Calibration...");
		_delay_ms(700);
	}
	OLED_reset();
}

/**
 * \fn void OLED_start_animation()
 * \brief Print the animation screen on the OLED
 */
void OLED_start_animation()
{
	for (int i = 0; i < 128; i++)
	{
		OLED_goto_column(i);
		Oled_print_column1(i);
		_delay_ms(30);
	}
}

/**
 * \fn void OLED_print_column1()
 * \brief Print one column of the OLED 
 * \param int column
 */
void Oled_print_column1(int column)
{

	for (int i = 0; i < 8; i++)
	{
		OLED_goto_line(i);
		Oled_print_full();
	}
}

/**
 * \fn void OLED_print_full()
 * \brief Print a full area
 */
void Oled_print_full()
{

	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
	write_d(0xff);
}

/**
 * \fn void OLED_life_menu(int nb_lives, int current_lives, int difficulty)
 * \brief Print the lives screen on the OLED
 * \param nb_lives
 * \param current_lives
 * \param difficulty
 */
void OLED_life_menu(int nb_lives, int current_lives)
{

	OLED_goto_line(1);
	OLED_goto_column(39);
	OLED_print("lives:");

	OLED_number_of_lives(nb_lives, current_lives);
}

/**
 * \fn void OLED_number_of_lives(int number_of_lives, int current_lives)
 * \brief Print the hearths on the OLED
 * \param number_of_lives
 * \param current_lives
 */
void OLED_number_of_lives(int number_of_lives, int current_lives)
{

	int dead_haerts = number_of_lives - current_lives;

	if (number_of_lives == 5)
	{
		switch (dead_haerts)
		{
		case 0:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(1);

			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(1);

			OLED_goto_column(73);
			OLED_print_heart(1);

			OLED_goto_column(91);
			OLED_print_heart(1);
			break;

		case 1:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(1);

			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(1);

			OLED_goto_column(73);
			OLED_print_heart(1);

			OLED_goto_column(91);
			OLED_print_heart(0);
			break;

		case 2:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(1);

			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(1);

			OLED_goto_column(73);
			OLED_print_heart(0);

			OLED_goto_column(91);
			OLED_print_heart(0);
			break;

		case 3:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(1);

			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(0);

			OLED_goto_column(73);
			OLED_print_heart(0);

			OLED_goto_column(91);
			OLED_print_heart(0);
			break;

		case 4:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(1);

			OLED_goto_column(37);
			OLED_print_heart(0);

			OLED_goto_column(55);
			OLED_print_heart(0);

			OLED_goto_column(73);
			OLED_print_heart(0);

			OLED_goto_column(91);
			OLED_print_heart(0);
			break;

		case 5:
			OLED_goto_line(3);
			OLED_goto_column(19);
			OLED_print_heart(0);

			OLED_goto_column(37);
			OLED_print_heart(0);

			OLED_goto_column(55);
			OLED_print_heart(0);

			OLED_goto_column(73);
			OLED_print_heart(0);

			OLED_goto_column(91);
			OLED_print_heart(0);
		default:
			OLED_game_over();
		}
	}

	else if (number_of_lives == 4)
	{
		switch (dead_haerts)
		{
		case 0:
			OLED_goto_line(3);
			OLED_goto_column(35);
			OLED_print_heart(1);

			OLED_goto_column(53);
			OLED_print_heart(1);

			OLED_goto_column(72);
			OLED_print_heart(1);

			OLED_goto_column(90);
			OLED_print_heart(1);
			break;

		case 1:
			OLED_goto_line(3);
			OLED_goto_column(35);
			OLED_print_heart(1);

			OLED_goto_column(53);
			OLED_print_heart(1);

			OLED_goto_column(72);
			OLED_print_heart(1);

			OLED_goto_column(90);
			OLED_print_heart(0);
			break;

		case 2:
			OLED_goto_line(3);
			OLED_goto_column(35);
			OLED_print_heart(1);

			OLED_goto_column(53);
			OLED_print_heart(1);

			OLED_goto_column(72);
			OLED_print_heart(0);

			OLED_goto_column(90);
			OLED_print_heart(0);
			break;

		case 3:
			OLED_goto_line(3);
			OLED_goto_column(35);
			OLED_print_heart(1);

			OLED_goto_column(53);
			OLED_print_heart(0);

			OLED_goto_column(72);
			OLED_print_heart(0);

			OLED_goto_column(90);
			OLED_print_heart(0);
			break;

		case 4:
			OLED_goto_line(3);
			OLED_goto_column(35);
			OLED_print_heart(0);

			OLED_goto_column(53);
			OLED_print_heart(0);

			OLED_goto_column(72);
			OLED_print_heart(0);

			OLED_goto_column(90);
			OLED_print_heart(0);
			break;
		default:
			OLED_game_over();
			;
		}
	}

	else if (number_of_lives == 3)
	{
		switch (dead_haerts)
		{
		case 0:
			OLED_goto_line(3);
			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(1);

			OLED_goto_column(73);
			OLED_print_heart(1);
			break;

		case 1:
			OLED_goto_line(3);
			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(1);

			OLED_goto_column(73);
			OLED_print_heart(0);
			break;

		case 2:
			OLED_goto_line(3);
			OLED_goto_column(37);
			OLED_print_heart(1);

			OLED_goto_column(55);
			OLED_print_heart(0);

			OLED_goto_column(73);
			OLED_print_heart(0);
			break;

		case 3:
			OLED_goto_line(3);
			OLED_goto_column(37);
			OLED_print_heart(0);

			OLED_goto_column(55);
			OLED_print_heart(0);

			OLED_goto_column(73);
			OLED_print_heart(0);
		default:
			OLED_game_over();
		}
	}
}

/**
 * \fn void print_pixel()
 * \brief Print one pixel
 * \param n
 * \param size
 */
void print_pixel(int n, int size)
{
	for (int i = 0; i < n; i++)
	{
		write_d(size);
	}
}

/**
 * \fn void OLED_goto_pixel(int line, int column)
 * \brief go to a pixel
 * \param line
 * \param column
 */
void OLED_goto_pixel(int line, int column)
{
	OLED_goto_column(column * 8);
	OLED_goto_line(line);
}

/**
 * \fn void OLED_print_line_pixels(int nb_pixels, int size)
 * \brief print a line of pixel
 * \param nb_pixels
 * \param size
 */
void OLED_print_line_pixels(int nb_pixels, int size)
{
	for (int i = 0; i < nb_pixels; i++)
	{
		print_pixel(4, size);
	}
}

/**
 * \fn void print_pixel_at(int line, int column, int size)
 * \brief print a pixel at
 * \param nb_pixels
 * \param size
 */
void print_pixel_at(int line, int column, int size)
{
	OLED_goto_column(column);
	OLED_goto_line(line);
	for (int i = 0; i < size; i++)
	{
		write_d(0xf);
	}
}

/**
 * \fn void OLED_print_heart(int filled)
 * \brief print one heart
 * \param filed
 */
void OLED_print_heart(int filled)
{
	if (filled)
	{
		write_d(0b00001110);
		write_d(0b00011111);
		write_d(0b00111111);
		write_d(0b01111111);
		write_d(0b11111110);
		write_d(0b01111111);
		write_d(0b00111111);
		write_d(0b00011111);
		write_d(0b00001110);
	}
	else
	{
		write_d(0b00001110);
		write_d(0b00010001);
		write_d(0b00100001);
		write_d(0b01000001);
		write_d(0b10000010);
		write_d(0b01000001);
		write_d(0b00100001);
		write_d(0b00010001);
		write_d(0b00001110);
	}
}

/**
 * \fn void OLED_print_skull(int line, int column)
 * \brief print a skull at line and column
 * \param line
 * \param column
 */
void OLED_print_skull(int line, int column)
{
	OLED_goto_line(line);
	OLED_goto_column(column);

	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00111100);
	write_d(0b01000010);
	write_d(0b10011001);
	write_d(0b00011001);

	OLED_goto_line(line);
	OLED_goto_column(column + 8);

	write_d(0b01000001);
	write_d(0b00011001);
	write_d(0b10011001);
	write_d(0b01000010);
	write_d(0b00111100);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);

	OLED_goto_line(line + 1);
	OLED_goto_column(column);

	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000001);
	write_d(0b00000010);
	write_d(0b00000101);

	OLED_goto_line(line + 1);
	OLED_goto_column(column + 8);

	write_d(0b00000101);
	write_d(0b00000101);
	write_d(0b00000010);
	write_d(0b00000001);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
}

/**
 * \fn void OLED_print_skull_bones(int line, int column)
 * \brief print a skull with bones at line and column
 * \param line
 * \param column
 */
void OLED_print_skull_bones(int line, int column)
{

	OLED_goto_line(line);
	OLED_goto_column(column);

	write_d(0b00000000);
	write_d(0b11100000);
	write_d(0b11100000);
	write_d(0b11100000);
	write_d(0b10000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);

	OLED_goto_line(line);
	OLED_goto_column(column + 8);

	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b10000000);
	write_d(0b11100000);
	write_d(0b11100000);
	write_d(0b11100000);

	OLED_goto_line(line + 1);
	OLED_goto_column(column);

	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000001);
	write_d(0b00111111);
	write_d(0b01000011);
	write_d(0b10011001);
	write_d(0b00011001);

	OLED_goto_line(line + 1);
	OLED_goto_column(column + 8);

	write_d(0b01000001);
	write_d(0b00011001);
	write_d(0b10011001);
	write_d(0b01000011);
	write_d(0b00111111);
	write_d(0b00000001);
	write_d(0b00000000);
	write_d(0b00000000);

	OLED_goto_line(line + 2);
	OLED_goto_column(column);

	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00111000);
	write_d(0b00111000);
	write_d(0b00111100);
	write_d(0b00001111);
	write_d(0b00000110);
	write_d(0b00000101);

	OLED_goto_line(line + 2);
	OLED_goto_column(column + 8);

	write_d(0b00000101);
	write_d(0b00000101);
	write_d(0b00000110);
	write_d(0b00001111);
	write_d(0b00111100);
	write_d(0b00111000);
	write_d(0b00111000);
	write_d(0b00000000);
}

/*


{0b 0 0 0 0 0 0 0 0
,0b 1 1 0 0 0 0 0 0
,0b 1 1 0 1 0 0 0 0
,0b 1 1 0 1 1 0 0 0
,0b 1 1 1 1 1 1 0 0
,0b 1 1 1 1 1 1 0 0
,0b 0 0 0 1 1 0 0 0
,0b 0 0 0 1 0 0 0 0}


{0b00000000,0b11000000,0b11010000,0b11011000,0b11111100,0b11111100,0b00011000,0b00010000}


*/