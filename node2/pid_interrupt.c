#include "timer.h"
#include "sam/sam3x/include/sam.h"
#include "sam/interrupt.h"
#include "sam/interrupt/interrupt_sam_nvic.h"


#define IRQ_SysTick_priority    0
#define F_CPU                   84000000


volatile uint32_t count = 0;


static void SysTick_init_us(int period) {
    // load value
    SysTick->LOAD = ((int)(period*84) & SysTick_LOAD_RELOAD_Msk)-1;

    // reset count
    SysTick->VAL = 0;

    // priority
    NVIC_SetPriority(SysTick_IRQn, IRQ_SysTick_priority);

    // set SysTick timer to MCK, enable interrupt and timer
    SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
    SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
    if(count!=0) {
        count--;
    }
    else {
        SysTick->CTRL = 0;
    }
}