/**
 * \file OLED_implementation.c
 * \brief OLED implementation
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_implementation.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

///List of options
static struct Option option3 = {NULL, "C:", "CA", "CB", "CC", NULL, NULL, NULL};
static struct Option option2 = {NULL, "B:", "BA", "BB", "BC", NULL, NULL, NULL};
static struct Option option1 = {NULL, "A:", "AA", "AB", "AC", NULL, NULL, NULL};
static struct Option option0 = {NULL, "Options:", "A", "B", "C", NULL, NULL, NULL};


/*
GAME MENU
static struct Option home={NULL, "HOME", "Play", "Settings", "", NULL, NULL, NULL};
static struct Option play={NULL, "PLAY", "3 lifes", "5 lifes", "10 lifes", NULL, NULL, NULL};
static struct Option settings={NULL, "SETTINGS", "Calibrate", "Credits", "", NULL, NULL, NULL};
static struct Option calibration={NULL, "CALIBRATION", "", "", "", NULL, NULL, NULL};
static struct Option credits={NULL, "CREDITS", "Louis BARBE", "Michel SCHneider", "", NULL, NULL, NULL};
static struct Option lifes3={NULL, "3 Lifes", "", "", "", NULL, NULL, NULL};
static struct Option lifes5={NULL, "5 Lifes", "", "", "", NULL, NULL, NULL};
static struct Option lifes10={NULL, "10 Lifes", "", "", "", NULL, NULL, NULL};

*/
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
     //OLED_print("<");
     OLED_test();
}

/**
 * \fn void clean_selected()
 * \brief Remove the "#" that correspond to the selected option
 */
void clean_selected()
{
     OLED_goto_column(1);
     for (uint16_t i = 2; i < 6; i++)
     {
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

     option3.previous_option = &option0;
     option3.next_1 = &option3;
     option3.next_2 = &option3;
     option3.next_3 = &option3;

     option2.previous_option = &option0;
     option2.next_1 = &option2;
     option2.next_2 = &option2;
     option2.next_3 = &option2;

     option1.previous_option = &option0;
     option1.next_1 = &option1;
     option1.next_2 = &option1;
     option1.next_3 = &option1;

     option0.previous_option = &option0;
     option0.next_1 = &option1;
     option0.next_2 = &option2;
     option0.next_3 = &option3;

     struct Option current_option = option0;
     //int selected_option;
     return option0;

/*
GAME OPTIONS MAPPING
     option3.previous_option = &option0;
     option3.next_1 = &option3;
     option3.next_2 = &option3;
     option3.next_3 = &option3;

     home.previous_option = &home;
     home.next_1 = &play;
     home.next_2 = &settings;
     home.next_3 = &home;

     play.previous_option = &home;
     play.next_1 = &lifes3;
     play.next_2 = &lifes5;
     play.next_3 = &lifes10;

     settings.previous_option = &home;
     settings.next_1 = &calibrate;
     settings.next_2 = &credits;
     setting.next_3 = &settings;

     credits.previous_option = &settings;
     credits.next_1 = &credits;
     credits.next_2 = &credits;
     credits.next_3 = &credits;

     struct Option current_option = home;
     */

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
     DDRB &= 0x00;
     PORTB |= 0x02;

     // int selected_option=1;
     // struct Option current_option=option0;

     print_option(current_option, selected_option);
     char joystick_position = get_joystick_direction();
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