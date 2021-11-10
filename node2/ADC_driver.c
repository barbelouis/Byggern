#include "ADC_driver.h"
#include "sam.h"
#include <stdio.h>


void ADC_init()
{
    //To complete
    //AD0=>PA16
   

}
int ADC_get_value()
{
    //To complete
     uint16_t value = (PIOA->PIO_PDSR);
     printf("Value %x\n\r", value);
}
int ADC_get_boolean()
{
    if (ADC_get_value > 200)
    { //value to defined
        return 1;
    }
    else
        return 0;
}