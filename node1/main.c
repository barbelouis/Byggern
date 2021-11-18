/*
 * Node1.c
 *
 * Created: 16.11.2021 20:04:28
 * Author : Miche
 */

#include <avr/io.h>
/// \file
#define FOSC 4915200 // Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#include "UART_driver.h"
#include "ADC_driver.h"
#include "joystick_slider_driver.h"
#include "OLED_driver.h"
#include "OLED_implementation.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN_driver.h"
#include "sensors_over_CAN_driver.h"
#include "message_handler.h"

#include "joystick_slider_driver.h"

//#include "fonts.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

///Entry point of the program
int main(void)
{

    //Set register for use of JTAG
    //MCUCR =0b1xxxxxxx;
    MCUCR |= (1 << SRE);
    //SFIOR =0bxx1xxxxx; // Uses of jtag on port C (cf. page 32)
    SFIOR |= (1 << XMM2);

    //init USART for communicqtion and printing
    USART_Init(MYUBRR);

    printf("===== RESET =====\n");

    ADC_init();

    OLED_init();

    OLED_reset();

    CAN_init();

    while (1)
    {
        printf("==== LOOP ====\n\n");
        game_start();

        _delay_ms(200);

        check_can_message();
        }
}
