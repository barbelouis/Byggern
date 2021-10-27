#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/UART_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/ADC_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/joystick_slider_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_implementation.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"

//#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/fonts.h"
#include <avr/io.h>
#include <util/delay.h> 
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>



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
    


   //ADC_init();
    
       printf("reset\n");
    CAN_init();
    //SPI_init();

    
    printf("after can init\n");
    
    //uint8_t arr [3] = {1,1,1};
    struct Message message={0b00000000111,3,{'a','b','c'}};
    //struct Message message={0b00000000111,3,"abc"};
    struct Message received_message;


    for(int i=0; i< message.length; i++){
                    printf("%x ",message.data[i]);
                    
                } 
     CAN_send(message);
     printf("after can send\n");
    

    while(1){
        //continue;
        _delay_ms(150);
        /*
        menu=make_menu(current_option,selected_option);
        current_option=menu.current_option;
        selected_option= menu.selected_option;
        */
        CAN_send(message);
       // printf(message.data);
       // printf("\nmessage sent\n");
       
        if(flag|1){
          //  printf("Interrupt received\n");
            uint8_t status;
            //status= MCP2515_read_status();
            

            status= MCP2515_read(MCP_CANINTF);
            printf("status: %x\n",status);
            if((0x3 & status)){
                cli();
                CAN_receive(&received_message,status & 0x3);
                //CAN_receive(&received_message,0x2);
                sei();
                printf("message length: %d\n",received_message.length);
                printf("received: ");
                printf("%x ",received_message.data);
                
                for(int i=0; i< received_message.length; i++){
                    printf("%x ",received_message.data[i]);
                    
                } 
            
                
                //printf(received_message.data);
                printf("\n");
                //printf("%x",received_message.data);
            }
            
        }
        
    
    
    }


    
/*
   while(1){
       _delay_ms(5);
       SPI_write('a');
   }*/

}




