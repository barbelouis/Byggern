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
#endif 