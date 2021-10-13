#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/UART_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/ADC_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/joystick_slider_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/OLED_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/OLED_implementation.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/SPI_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/CAN_driver.h"

//#include "/home/louis/Documents/NTNU/TTK4155/Byggern/fonts.h"
#include <avr/io.h>
#include <util/delay.h> 
#include <stdio.h>
#include <stdlib.h>



int main(void){
    //Set register for use of JTAG
    //MCUCR =0b1xxxxxxx;
    MCUCR |= (1 << SRE);
    //SFIOR =0bxx1xxxxx; // Uses of jtag on port C (cf. page 32)
    SFIOR |= (1 << XMM2);
    
    //init USART for communicqtion and printing
    USART_Init( MYUBRR );

    ADC_init();

    OLED_init();
    
    
    OLED_reset();


     
    int selected_option=1;
    
    
    struct Option current_option=define_options();
    struct Menu menu;//={define_options(),1};
    




       
    CAN_init();
    struct Message message={0b00000000111,2,"ab"};
    struct Message received_message;
    

    

    while(1){
        _delay_ms(150);
        menu=make_menu(current_option,selected_option);
        current_option=menu.current_option;
        selected_option= menu.selected_option;
        CAN_send(message);
        printf("\nmessage sent\n");
        if(flag|1){
            printf("Interrupt received\n");
            uint8_t status;
            status= MCP2515_read_status();
            if((1 & status)|1){
                CAN_receive(&received_message);
                printf("message received: ");

                printf(received_message.data[0]);
            }
            
        }
    
    
    }

}




