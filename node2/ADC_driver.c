#include "ADC_driver.h"

void ADC_init()
{
    //To complete
}
int ADC_get_value()
{
    //To complete
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