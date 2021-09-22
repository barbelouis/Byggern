#ifndef F_CPU
#define F_CPU 4915200UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include </home/louis/Documents/NTNU/TTK4155/Byggern/UART_driver.h>
#include <stdio.h>
 
int main(void)
{
    DDRD |= (1 << DDD4);
    TCCR3B |= ( 1<< WGM32);
    TCCR3B |= ( 1<< CS30);
    OCR3A = 0x00;
    TCCR3A |= (1 << COM3A0);
printf("================");

    volatile char *adc = (char *) 0x1400; // Start address for the ADC
    uint16_t adc_size = 0x400;

    while(1){
        printf("================");
        adc[0]=0b00000001;
        _delay_ms(50);
        uint8_t retreived_value = adc[00000001];
        printf("value: %4d \n", retreived_value);
 
    }

}   