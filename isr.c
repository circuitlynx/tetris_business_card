#include "ti_msp_dl_config.h"
#include "isr.h"

#define DEBOUNCE_MS 10

volatile uint32_t msPassed = 0;
volatile bool gravityTick = false;

volatile bool moveLeft = false;
volatile bool moveRight = false;
volatile bool rotate = false;

static volatile bool     leftLocked;
static volatile uint32_t leftLockedMs;
static volatile bool     rightLocked;
static volatile uint32_t rightLockedMs;
static volatile bool     upLocked;
static volatile uint32_t upLockedMs;

// Helper function for the timer. If a pin has been HIGH for longer than DEBOUNCE_MS it will arm itself.
static void rearmPin(uint32_t pin, volatile bool *locked, volatile uint32_t *lockMs);

// Triggers on 1ms ticks
void TIMER_0_INST_IRQHandler(void){
    if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO){
        msPassed++;
        if (msPassed % 500 == 0) gravityTick = true;
    }
    rearmPin(GPIO_GRP_0_PIN_LEFT_PIN, &leftLocked, &leftLockedMs);
    rearmPin(GPIO_GRP_0_PIN_RIGHT_PIN, &rightLocked, &rightLockedMs);
    rearmPin(GPIO_GRP_0_PIN_UP_PIN, &upLocked, &upLockedMs);
}

// Triggers on button inputs
void GPIOA_IRQHandler(void){
    switch (DL_GPIO_getPendingInterrupt(GPIOA)){
        case GPIO_GRP_0_PIN_LEFT_IIDX:
            moveLeft = true;
            DL_GPIO_disableInterrupt(GPIOA, GPIO_GRP_0_PIN_LEFT_PIN);
            leftLockedMs = msPassed;
            leftLocked = true;
            break;
        case GPIO_GRP_0_PIN_RIGHT_IIDX:
            moveRight = true;
            DL_GPIO_disableInterrupt(GPIOA, GPIO_GRP_0_PIN_RIGHT_PIN);
            rightLockedMs = msPassed;
            rightLocked = true;
            break;
        case GPIO_GRP_0_PIN_UP_IIDX:
            rotate = true;
            DL_GPIO_disableInterrupt(GPIOA, GPIO_GRP_0_PIN_UP_PIN);
            upLockedMs = msPassed;
            upLocked = true;
            break;
        default:
            break;
    }
}

// Helper function for the timer. If a pin has been HIGH for longer than DEBOUNCE_MS it will arm itself.
static void rearmPin(uint32_t pin, volatile bool *locked, volatile uint32_t *lockMs){
    if (!*locked) return;
    if (DL_GPIO_readPins(GPIOA, pin) == 0) {
        *lockMs = msPassed;
    } else if ((msPassed - *lockMs) >= DEBOUNCE_MS) {
        DL_GPIO_clearInterruptStatus(GPIOA, pin);
        DL_GPIO_enableInterrupt(GPIOA, pin);
        *locked = false;
    }
}