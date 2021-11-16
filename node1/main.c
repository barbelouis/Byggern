/// \file
#define FOSC 4915200 // Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/UART_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/ADC_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/joystick_slider_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/OLED_implementation.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/SPI_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/sensors_over_CAN_driver.h"

//#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/fonts.h"
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

    int selected_option = 1;

    struct Option current_option = define_options();
    struct Menu menu; //={define_options(),1};

    CAN_init();

    CAN_MESSAGE message = {0b11110000110, 6, "abcdef"};

    CAN_MESSAGE received_message;

    for (int i = 0; i < message.length; i++)
    {
        printf("%x ", message.data[i]);
    }
    /*
    while (1)
    {

        CAN_send(message);
        uint8_t status;
        uint8_t error;
        uint8_t rec;
        uint8_t tec;

        status = MCP2515_read(MCP_CANINTF);
        error = MCP2515_read(MCP_EFLG);
        rec = MCP2515_read(MCP_REC);
        tec = MCP2515_read(MCP_TEC);
        printf("status: %x\n", status);
        printf("error flag: %x\n", error);
        printf("REC: %x\n", rec);
        printf("TEC: %x\n", tec);

        _delay_ms(500);
    }

    return 0;
    */
    
    while (1)
    {
        //OLED_print_title();
        OLED_draw_hearts();
        



        //continue;
        printf("==== LOOP ====\n\n");
        _delay_ms(200);
        //send_right_slider_position_to_node2();
       /*
        menu=make_menu(current_option,selected_option);
        current_option=menu.current_option;
        selected_option= menu.selected_option;
        */
        
        //char dir = get_joystick_direction();
        //printf("joystick: %c\n", dir);
        //CAN_send(message);
        //send_joystick_analog_horizontal_position_to_node2();
        //send_joystick_position_to_node2();
        send_sensors_data_to_node2();
        if (flag)
        {
            //  printf("Interrupt received\n");
            uint8_t status;
            uint8_t error;
            uint8_t rec;
            uint8_t tec;
            //status= MCP2515_read_status();

            status = MCP2515_read(MCP_CANINTF);
            error = MCP2515_read(MCP_EFLG);
            rec = MCP2515_read(MCP_REC);
            tec = MCP2515_read(MCP_TEC);
            printf("status: %x\n", status);
            printf("error flag: %x\n", error);
            printf("REC: %x\n", rec);
            printf("TEC: %x\n", tec);
            if ((0x3 & status))
            {
                //cli();
                CAN_receive(&received_message, status & 0x3);
                //CAN_receive(&received_message,0x2);
                //sei();
                printf("\n");
                printf("received ID: %x\n", received_message.id);
                printf("received length: %d\n", received_message.length);
                printf("received message: ");
                //     printf("%x ",received_message.data);

                for (int i = 0; i < received_message.length; i++)
                {
                    printf("%c", received_message.data[i]);
                }

                printf("\n\n");
            }
        }
    }
}
