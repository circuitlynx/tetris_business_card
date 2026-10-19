/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "IS31FL3741.h"

int main(void)
{
    SYSCFG_DL_init();
    IS31FL3741_init();
    
    // Test code
    // --- STEP A: Flood ALL Scaling Registers (Pages 2 and 3) ---
    // The IS31FL3741 has 351 channels. Page 2 handles 0-179, Page 3 handles 180-350.
    IS31FL3741_selectPage(0x02);
    for(uint16_t i = 0; i < 180; i++) {
        IS31FL3741_writeReg((uint8_t)i, 0x80);
    }
    IS31FL3741_selectPage(0x03);
    for(uint16_t i = 0; i < 180; i++) {
        IS31FL3741_writeReg((uint8_t)i, 0x80);
    }
    
    // --- STEP B: Flood ALL PWM Brightness Registers (Pages 0 and 1) ---
    // Page 0 handles 0-179, Page 1 handles 180-350.
    /*IS31FL3741_selectPage(0x00);

    for(uint16_t i = 0; i < 180; i = i + 3) {
        IS31FL3741_writeReg((uint8_t)i, 0x08);
        IS31FL3741_writeReg((uint8_t)(i+1), 0x08);
        IS31FL3741_writeReg((uint8_t)(i+2), 0x08);
        delay_cycles(4000000);

    }

    
    IS31FL3741_selectPage(0x01);
    for(uint16_t i = 0; i < 180; i = i + 3) {
        IS31FL3741_writeReg((uint8_t)i, 0x08);
        IS31FL3741_writeReg((uint8_t)(i+1), 0x08);
        IS31FL3741_writeReg((uint8_t)(i+2), 0x08);
        delay_cycles(4000000);

    }*/

    
    while (1) {
        for (int x = 0; x < SCREEN_WIDTH; x++){
            for (int y = 0; y < SCREEN_HEIGHT; y++){
                writePixel(y,x,0xFFFFFF);
                delay_cycles(4000000);
                writePixel(y, x, 0x0);
                delay_cycles(4000000);
            }
        }
    }
}
