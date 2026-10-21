#include "ti_msp_dl_config.h"
#include "timers.h"

volatile uint32_t msPassed = 0;
volatile bool gravityTick = false;

void TIMER_0_INST_IRQHandler(void){
    if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO){
        msPassed++;
        if (msPassed % 500 == 0) gravityTick = true;
    }
}