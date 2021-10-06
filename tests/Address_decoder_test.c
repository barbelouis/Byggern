#ifndef F_CPU
#define F_CPU 4915200UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
 /*
int main(void)
{
    DDRC = 0x01;                       // initialize port C
    while(1)
    {
       
        PORTC = 0b00000000;            
        _delay_ms(1000); 


        PORTC = 0b00000100;            
        _delay_ms(1000);                
       
        PORTC = 0b00001000;            
        _delay_ms(1000); 

        PORTC = 0b0001100;            
        _delay_ms(1000);
                        
    }
}*/