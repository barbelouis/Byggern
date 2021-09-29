#define FOSC 4915200// Clock Speed
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>


#include <stdlib.h>
#include <stdint.h>
#include </home/louis/Documents/NTNU/TTK4155/Byggern/UART_driver.h>
#include <stdio.h>
//#include </home/louis/Documents/NTNU/TTK4155/Byggern/ADC_driver.h>
/* 
int main(void)
{

    //MCUCR =0b10000000;
    MCUCR |= (1 << SRE);
    //MCUCR &= ~(1 << SRE);
    SFIOR |= (1 << XMM2);
    //SFIOR =0b00100000; // Uses of jtag on port C (cf. page 32)
    USART_Init( MYUBRR );

    printf("We're in!\n");
/*
    ///////// Set up internal clk on PD4 /////////////////////
    DDRD |= (1 << DDD4);
    TCCR3B |= ( 1<< WGM32);
    TCCR3B |= ( 1<< CS30);
    OCR3A = 0x00;
    TCCR3A |= (1 << COM3A0);
    /////////////////////////////////////////////////////////


ADC_init();


    while(1){
     /*   
        printf("================\n");
        adc[0]=0x0f;
        _delay_ms(1);
        uint8_t retreived_value = adc[1];
        printf("Vertical axis:   %4d \n", retreived_value);
       
       
        _delay_ms(1);
       
        retreived_value = adc[1];
        printf("Horizontal axis: %4d \n", retreived_value);
        
        _delay_ms(1);
        retreived_value = adc[1];
        printf("Left slider:     %4d \n", retreived_value);

        _delay_ms(1);
        retreived_value = adc[1];
        printf("Right slider:    %4d \n", retreived_value);
        

       read_ADC_input();
       print_ADC_values();
    }

}   */