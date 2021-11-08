/**
 * \file UART_driver.c
 * \brief UART library
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */

#define FOSC 4915200 // Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include </home/louis/Documents/NTNU/TTK4155/Byggern/node1/UART_driver.h>

/**
 * \fn void USART_Init( unsigned int ubrr0 )
 * \brief UART initialization
 * \param unsigned int ubrr0
 */
void USART_Init(unsigned int ubrr0)
{
        /* Set baud rate */
        UBRR0H = (unsigned char)(ubrr0 >> 8);
        UBRR0L = (unsigned char)ubrr0;
        /* Enable receiver and transmitter */
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
        /* Set frame format: 8data, 2stop bit */
        UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);

        static FILE mystdout = FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);
        stdout = &mystdout;
}

/**
 * \fn void USART_Transmit(char data)
 * \brief UART transmit
 * \param char data
 */
void USART_Transmit(char data)
{
        /* Wait for empty transmit buffer */
        while (!(UCSR0A & (1 << UDRE0)))
                ;
        /* Put data into buffer, sends the data */
        UDR0 = data;
}

/**
 * \fn char USART_Receive(void)
 * \brief UART receive
 * \return char received_data
 */
char USART_Receive(void)
{
        /* Wait for data to be received */
        while ((!(UCSR0A)) & (1 << RXC0))
        {
                //;

                // LED on
                PORTC = 0b0000101; // PC0 = High = Vcc
                _delay_ms(500);    // wait 500 milliseconds

                //LED off
                PORTC = 0b00000000; // PC0 = Low = 0v
                _delay_ms(500);     // wait 500 milliseconds
        }

        /* Get and return received data from buffer */
        return UDR0;
}

/**
 * \fn void USART_Flush(void)
 * \brief UART flush
 */
void USART_Flush(void)
{
        char dummy;
        while (UCSR0A & (1 << RXC0))
                dummy = UDR0;
}
