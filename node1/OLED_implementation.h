#ifndef OLED_IMPLEMENTATION_H
#define OLED_IMPLEMENTATION_H

#include <stdio.h>

void OLED_print_title();
void OLED_print_u();
void OLED_life_menu(int nb_lives, int current_lives, int difficulty);
void OLED_number_of_lives(int number_of_lives, int current_lives);
void OLED_draw_hearts();
void print_pixel(int n, int size);
void OLED_goto_pixel(int line, int column);
void OLED_print_line_pixels(int nb_pixels, int size);
void print_pixel_at(int line, int column, int size);
void OLED_print_heart(int filled);
void OLED_game_over();

void OLED_start_animation();
void Oled_print_full();
void Oled_print_column1();
void OLED_calibration();

struct Option
{
   struct Option *previous_option;
   char *title;
   char *o_1;
   char *o_2;
   char *o_3;
   struct Option *next_1;
   struct Option *next_2;
   struct Option *next_3;
};

struct Menu
{
   struct Option current_option;
   int selected_option;
};

void make_options(char *title, int cursorPosition, char *option1, char *option2, char *option3);
void clean_selected();
struct Menu make_menu(struct Option current_option, int selected_option);
struct Option define_options();
void print_option(struct Option option, int selected_option);

#endif