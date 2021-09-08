#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include </home/louis/Documents/NTNU/TTK4155/Byggern/UART_driver.h>
#include </home/louis/Documents/NTNU/TTK4155/Byggern/sram_test.h>



int main(void)
{

USART_Init( MYUBRR );

SRAM_test();

}


