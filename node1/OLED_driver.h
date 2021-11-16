#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include <stdio.h>
void write_c(uint16_t command);


void OLED_init();
void OLED_reset();
void OLED_home(); 
void OLED_goto_line(line);
void OLED_goto_column(column);
void OLED_clear_line(line);
void OLED_print_line(line);
void OLED_pos(row,column);
//void OLED_print(char*);
void OLED_print_test();
void OLED_print_column();
void OLED_test();
void OLED_test2();
void OLED_print_ASCII(int code);
void OLED_print(char* c);
void OLED_print_title();
void OLED_print_u();

void OLED_draw_hearts();
void print_pixel(int n,int size);
void OLED_goto_pixel(int line, int column);
void OLED_print_line_pixels(int nb_pixels,int size);
void print_pixel_at(int line, int column, int size);
void OLED_print_heart(int filled);
#endif 