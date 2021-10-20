#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/ADC_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>

void ADC_init(){
    ///////// Set up internal clk on PD4 /////////////////////
    DDRD |= (1 << DDD4);
    TCCR3B |= ( 1<< WGM32);
    TCCR3B |= ( 1<< CS30);
    OCR3A = 0x00;
    TCCR3A |= (1 << COM3A0);
    /////////////////////////////////////////////////////////
}

void read_ADC_input(){
     volatile char *adc = (char *) 0x1400; // Start address for the ADC
     //printf("------ ADC values ------\n");
        adc[0]=0x0f;
        _delay_ms(1);
        //Vertical axis
        uint8_t input0 = adc[1];
        ADC_MAX.input0= input0;  
        //printf("Vertical axis:   %4d \n", input0);     
       
        _delay_ms(1);
       //Horizontal axis
        uint8_t input1 = adc[1];
        ADC_MAX.input1= input1;
        //printf("Horizontal axis: %4d \n", input1);
        
        _delay_ms(1);
        //Left slider
        uint8_t input2 = adc[1];
        ADC_MAX.input2= input2;
        //printf("Left slider:     %4d \n", input2);

        _delay_ms(1);
        //Right slider
        uint8_t input3 = adc[1];
        ADC_MAX.input3= input3;
        //printf("Right slider:    %4d \n", input3);
}

void print_ADC_values(){
        printf("=========ADC STRUCT values ==========\n");
        printf("Vertical axis:   %4d \n", ADC_MAX.input0);
        printf("Horizontal axis: %4d \n", ADC_MAX.input1);
        printf("Left slider:     %4d \n", ADC_MAX.input2);
        printf("Right slider:    %4d \n", ADC_MAX.input3);
}
