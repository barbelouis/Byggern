#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

volatile char *adc = (char *) 0x1400; // Start address for the ADC

struct ADC_driver
{
   int input0;
   int input1;
   int input2;
   int input3;
}ADC_MAX;


int ADC_init();
void read_ADC_input();
void print_ADC_values();

#endif 