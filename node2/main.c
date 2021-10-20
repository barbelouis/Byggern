#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"

#include "sam.h"

#define LED_PIN 0x8000000u

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

    //REG_PORT_DIR0 |= (1<<26);
    PIOB ->PIO_PER |= LED_PIN;

    while (1)
    {
        /* code */
        /*
        PA20 &= ~(1<<26);
        delay(200);
        PA20 |= (1<<26);
        delay(100);
        PA20 &= ~(1<<26);
        delay(200);
        PA |= (1<<26);
        delay(1000); */
    }
    
}



