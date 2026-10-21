#include "ti_msp_dl_config.h"
#include "isr.h"

volatile uint32_t msPassed = 0;
volatile bool gravityTick = false;

volatile bool moveLeft = false;
volatile bool moveRight = false;
volatile bool rotate = false;

// Triggers on 1ms ticks
void TIMER_0_INST_IRQHandler(void){
    if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO){
        msPassed++;
        if (msPassed % 500 == 0) gravityTick = true;
    }
}

// Triggers on button inputs
void GPIOA_IRQHandler(void){
    switch (DL_GPIO_getPendingInterrupt(GPIOA)){
        case GPIO_GRP_0_PIN_LEFT_IIDX:
            moveLeft = true;
            break;
        case GPIO_GRP_0_PIN_RIGHT_IIDX:
            moveRight = true;
            break;
        case GPIO_GRP_0_PIN_UP_IIDX:
            rotate = true;
            break;
        default:
            break;
    }
}