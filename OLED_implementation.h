#ifndef OLED_IMPLEMENTATION_H
#define OLED_IMPLEMENTATION_H

#include <stdio.h>


struct Option
{
   struct Option* previous_option;
   char* title;
   char* o_1;
   char* o_2;
   char* o_3;
   struct Option* next_1;
   struct Option* next_2;
   struct Option* next_3;
};

struct Menu
{
   struct Option current_option;
   int selected_option;
};

void make_options(char* title, int cursorPosition, char* option1, char* option2, char* option3);
void clean_selected();
struct Menu make_menu(struct Option current_option, int selected_option);
struct Option define_options();
void print_option(struct Option option, int selected_option);



#endif 