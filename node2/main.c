#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"


/* LED Definitions */
#define LED_NUM     3                        /* Number of user LEDs          */

extern void LED_Init(void);
extern void LED_On  (unsigned int num);
extern void LED_Off (unsigned int num);
extern void LED_Out (unsigned int value);



/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: low level LED functions
 * Note(s):
 *----------------------------------------------------------------------------
 * Modified by Antronics Ltd for use with the Arduino Due.
 * For details, see: http://www.element14.com/community/roadTestReviews/1453
 *                                                                 15 May 2013
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 20009-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "sam.h"                        /* SAM3X definitions                */
//#include "LED.h"

// This is a half-baked attempt at making a generic LED selector;
// The array elements give the pin masks, but the corresponding Ports are
// hard-coded!
// Also, the port setup was hard-coded!
// (and the Keil original didn't include the array dimension)
//                                        'TX' LED  'L' LED   'RX' LED
//                                        Port A    Port B    Port C
const unsigned long led_mask[LED_NUM] = { PIO_PA19, PIO_PA20, PIO_PC30 };

/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_Init (void) {
 // PMC->PMC_WPMR = 0x504D4300;             /* Disable write protect            */

 // PMC->PMC_PCER0 = ((1UL << ID_PIOA) |    /* enable PIOA clock                */
  //                  (1UL << ID_PIOB) |    /* enable PIOB clock                */  
    //                (1UL << ID_PIOC)  );  /* enable PIOC clock                */  

  PIOA->PIO_PER  =
  PIOA->PIO_OER  =
  PIOA->PIO_PUDR =
  PIOA->PIO_OWER = (led_mask[0]);         /* Setup PIO_PA12     for LED       */

 //PMC->PMC_WPMR = 0x504D4301;             /* Enable write protect             */

  LED_Out (0);                            /* switch LEDs off                  */
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On (unsigned int num) {

  
		 PIOA->PIO_CODR = led_mask[num];
  
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off (unsigned int num) {


		PIOA->PIO_SODR = led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}


void delay(int n)
{
    int i;

    for (;n >0; n--)
    {
        for (i=0;i<100;i++)
            __asm("nop");
    }
}


int main()
{
    
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();
    printf("Hello World\n\r");
    
    LED_Init();
     

    while (1)
    {
        // code 
       /*
        LED_On(0);
        //LED_On(1);
        delay(2000);
        LED_Off(0);
        //LED_Off(1);
        */
        delay(1000);
        printf("Hello World\n\r");
    }
    
}