#include "sam.h"
#include "game.h"
#define F_CPU                   84E6
#define CLK           F_CPU / 32
void timer_init() {
    //enable power management
    PMC->PMC_PCER0 |= 1 << (ID_TC0); //27

    // disable timer counter channel
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;

    // set clock to MCK/32
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK3 | TC_CMR_CPCTRG;

    // set match frequency to 50 Hz
    TC0->TC_CHANNEL[0].TC_RC = CLK/50;

    // enable RA compare match interrupt
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

    // enable interrupt
    NVIC_EnableIRQ(ID_TC0);
    NVIC_SetPriority(TC0_IRQn, 2);
}

void timer_enable(){
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}


void timer_disable(){
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
}

void TC0_Handler() {
   game();
    //printf("TICK\n\r");
    // clear interrupt flag
    TC0->TC_CHANNEL[0].TC_SR;
}


