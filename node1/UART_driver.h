#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void USART_Init(unsigned int ubrr);

void USART_Transmit(char data);

char USART_Receive(void);

void USART_Flush(void);

#endif