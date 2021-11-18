#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

struct ADC_driver
{
   int input0;
   int input1;
   int input2;
   int input3;
} ADC_MAX;

void ADC_init();
void read_ADC_input();
void print_ADC_values();

#endif