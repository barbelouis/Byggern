#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/UART_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/ADC_driver.h"
//#include </home/louis/Documents/NTNU/TTK4155/Byggern/joystick_slider_driver.h>
#include <avr/io.h>



int main(void){
    //Set register for use of JTAG
    //MCUCR =0b1xxxxxxx;
    MCUCR |= (1 << SRE);
    //SFIOR =0bxx1xxxxx; // Uses of jtag on port C (cf. page 32)
    SFIOR |= (1 << XMM2);
    
    //init USART for communicqtion and printing
    USART_Init( MYUBRR );

    ADC_init();

    while(1){
    //read_ADC_input();
    //print_ADC_values();
    print_sensors();
    }
}


