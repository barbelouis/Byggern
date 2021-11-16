/**
 * \file OLED_driver.c
 * \brief OLED driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/fonts.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

/**
 * \fn OLED_init()
 * \brief OLED initialization
 */
void OLED_init()
{
        write_c(0xae); // display off
        write_c(0xa1); //segment remap
        write_c(0xda); //common pads hardware: alternative
        write_c(0x12);
        write_c(0xc8); //common output scan direction:com63~com0
        write_c(0xa8); //multiplex ration mode:63
        write_c(0x3f);
        write_c(0xd5); //display divide ratio/osc. freq. mode
        write_c(0x80);
        write_c(0x81); //contrast control
        write_c(0x50);
        write_c(0xd9); //set pre-charge period
        write_c(0x21);
        write_c(0x20); //Set Memory Addressing Mode
        write_c(0x02);
        write_c(0xdb); //VCOM deselect level mode
        write_c(0x30);
        write_c(0xad); //master configuration
        write_c(0x00);
        write_c(0xa4); //out follows RAM content
        write_c(0xa6); //set normal display
        write_c(0xaf); // display on

        //// start of OLED
        // write_c(0x00);
        write_c(0x10);

        //printf OLED
        //  static FILE mystdout = FDEV_SETUP_STREAM(OLED_print, NULL,_FDEV_SETUP_WRITE);
        // stdout = &mystdout;
}

/**
 * \fn void write_c(uint16_t command)
 * \brief
 * \param command
 */
void write_c(uint16_t command)
{
        volatile char *ext_ram = (char *)0x1000; // Start address for the OLED
        //DDRB = 0x01;                             // initialize port B
        //PORTB = 0b00000000;                      // PB0 = High = Vcc
        ext_ram[0] = command;
        //PORTB = 0b00000001; // PB0 = Low
}

/**
 * \fn void write_d(uint16_t command)
 * \brief
 * \param command
 */
void write_d(uint16_t command)
{
        volatile char *ext_ram = (char *)0x1200; // Start address for the OLED
        //DDRB = 0x01;                             // initialize port B
        //PORTB = 0b00000001;                      // PB0 = High = Vcc
        ext_ram[0] = command;
        //PORTB = 0b00000000; // PB0 = Low
}

/**
 * \fn void OLED_goto_line(line)
 * \brief OLED set the cursor to line
 * \param line
 */
void OLED_goto_line(line)
{
        write_c(0xB0 | line);
        //write_c(0x00);
        //write_c(0x10); //commented 15/11
}

/**
 * \fn void OLED_clear_line(line)
 * \brief OLED clear line
 * \param line
 */
void OLED_clear_line(line)
{
        OLED_goto_line(line);
        for (uint16_t i = 0; i < 128; i++)
        {
                write_d(0x00);
                // printf("line:   %4d \n", i);
                _delay_ms(5);
        }
}

/**
 * \fn void OLED_print_line(line)
 * \brief OLED print line
 * \param line
 */
void OLED_print_line(line)
{
        OLED_goto_line(line);
        for (uint16_t i = 0; i < 128; i++)
        {
                write_d(0xff);
                //printf("line:   %4d \n", i);
                _delay_ms(5);
        }
}

/**
 * \fn void OLED_reset()
 * \brief OLED reset
 */
void OLED_reset()
{
        for (uint16_t j = 0; j < 8; j++)
        {
                OLED_goto_line(j);
                for (uint16_t i = 0; i < 128; i++)
                {
                        write_d(0x00);
                        // printf("line:   %4d \n", i);
                        //_delay_ms(5);
                }
        }
}

/**
 * \fn void OLED_print_column()
 * \brief OLED print column
 */
void OLED_print_column()
{
        for (uint16_t j = 0; j < 8; j++)
        {
                OLED_goto_line(j);
                for (uint16_t i = 0; i < 128; i++)
                {

                        if (i == 0)
                        {
                                write_d(0xff);
                        }
                        else
                        {
                                write_d(0x00);
                        }
                        printf("line:   %4d \n", i);
                        //_delay_ms(5);
                }
        }
}

/**
 * \fn void OLED_goto_column(column)
 * \brief OLED go to column
 * \param column
 */
void OLED_goto_column(column)
{
        /*for (uint16_t i = 0; i < column*8; i++){
                write_d(0x00);
        }*/
        write_c(0x0f & column);
        write_c(0x10 | (column & 0xf0));
}

/**
 * \fn void OLED_test()
 * \brief print specifi character
 */
void OLED_test()
{
        write_d(0b00000000);
        write_d(0b11000000);
        write_d(0b11010000);
        write_d(0b11011000);
        write_d(0b11111100);
        write_d(0b11111100);
        write_d(0b00011000);
        write_d(0b00010000);
}
/*
void OLED_print_char(__uint8_t character[8]){
        for (int i = 0; i < 8; i++)
        {
                __uint8_t x = character[i];
                write_d(x);
        }

}*/

/**
 * \fn void OLED_print_ASCII(int code)
 * \brief print ASCII character
 * \param code
 */
void OLED_print_ASCII(int code)
{

        for (int i = 0; i < 8; i++)
        {
                uint8_t byte = pgm_read_byte(&(font8[code - 32][i]));
                write_d(byte);
        }
}

/**
 * \fn void OLED_print(char *c)
 * \brief print character
 * \param c 
 */
void OLED_print(char *c)
{

        //printf("ASCII value of %c = %d", c, c);
        int len = strlen(c);
        for (int i = 0; i < len; i++)
        {
                OLED_print_ASCII(c[i]);
        }
}
/*
void OLED_print(char* string){
        
        OLED_print(string);
}*/

void OLED_print_title()
{

        ///////////////////////////LINE2
        OLED_goto_column(2);
        for (int i = 5; i < 14; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 28; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 37; i < 44; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 49; i < 52; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 61; i < 64; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 65; i < 76; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 97; i < 100; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 107; i < 112; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }
        for (int i = 117; i < 124; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        //////////////////////////////LINE3

        OLED_goto_column(3);

        for (int i = 1; i < 4; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 13; i < 16; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 20; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 27; i < 32; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 33; i < 36; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 45; i < 48; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 49; i < 52; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 61; i < 64; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 77; i < 80; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 97; i < 100; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 107; i < 112; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 113; i < 116; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 125; i < 128; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        //////////////////////////////////LINE4

        OLED_goto_column(4);
        for (int i = 1; i < 4; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 28; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 33; i < 36; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 45; i < 48; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 49; i < 52; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 61; i < 64; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 65; i < 76; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 97; i < 108; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 113; i < 116; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 125; i < 128; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        ///////////////////////LINE5

        OLED_goto_column(5);

        for (int i = 1; i < 4; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 24; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 33; i < 36; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 45; i < 48; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 49; i < 52; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 61; i < 64; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 65; i < 68; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 109; i < 112; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 113; i < 116; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 125; i < 128; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        ////////////////////////////////LINE6

        OLED_goto_column(6);

        for (int i = 1; i < 4; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 9; i < 16; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 20; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 25; i < 28; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 133; i < 36; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 45; i < 48; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 49; i < 52; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 61; i < 64; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 65; i < 68; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 109; i < 112; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 113; i < 116; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 125; i < 128; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        ////////////////////////////////LINE7

        OLED_goto_column(7);

        for (int i = 5; i < 12; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 17; i < 20; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 29; i < 32; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 37; i < 44; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 53; i < 60; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 65; i < 68; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 109; i < 112; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }

        for (int i = 117; i < 124; i++)
        {
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }
}

void OLED_print_u()
{

        //OLED_reset();

        for (int i = 2; i < 6; i++)
        {
                OLED_goto_column(0);
                OLED_goto_line(i);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        }
        OLED_goto_column(8);
        OLED_goto_line(1);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
        OLED_goto_column(64);
        OLED_goto_line(6);
        write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);
                write_d(0xff);

}
void print_pixel()
{
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
        write_d(0xff);
}
