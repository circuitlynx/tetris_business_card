#ifndef IS31FL3741_H
#define IS31FL3741_H

#include <stdbool.h>
#include <stdint.h>

#define IS31FL3741_ADDR 0x30

// Defines brightness of the screen
#define GLOBAL_CURRENT 0x02

#define COMMAND_REGISTER 0xFD
#define COMMAND_REGISTER_LOCK 0xFE

// Pages
#define PAGE_PWM_1 0x00
#define PAGE_PWM_2 0x01
#define PAGE_SCALING_1 0x02
#define PAGE_SCALING_2 0x03
#define PAGE_FUNCTION_REGISTER 0x04

// Page 4 Registers
#define CONFIGURATION_REGISTER 0x00
#define GLOBAL_CURRENT_REGISTER 0x01
#define RESET_REGISTER 0x3F

// Constants
#define UNLOCK 0xC5
#define RESET 0xAE
#define NORMAL 0x01

#define SCREEN_WIDTH 9
#define SCREEN_HEIGHT 13

#define RED    0xFF0404
#define GREEN  0x04FF04
#define BLUE   0x0404FF
#define CYAN   0x04FFFF
#define ORANGE 0xFF2804
#define YELLOW 0xFFFF04
#define PURPLE 0xFF04FF

// Write a single byte to a register
bool IS31FL3741_writeReg(uint8_t reg, uint8_t data);

// Unlock the command register and select a page
bool IS31FL3741_selectPage(uint8_t page);

// Initialize the display
void IS31FL3741_init(void);

// Writes with a color in 0xRRGGBB format.
bool writePixel(uint8_t y, uint8_t x, uint32_t color);

#endif