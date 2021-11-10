#ifndef ENCODER_DRIVER_H_
#define ENCODER_DRIVER_H_

#include "sam.h"

void encoder_init();
uint16_t  encoder_read();
void delay2(int n);
void encoder_reset();




#endif