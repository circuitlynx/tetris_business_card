#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "IS31FL3741.h"

typedef enum ActiveMino{
    NONE,
    I_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    O_BLOCK,
    T_BLOCK,
    L_BLOCK,
    J_BLOCK
} ActiveMino;

typedef enum Orientation{
    NORTH,
    EAST,
    SOUTH,
    WEST
} Orientation;

typedef struct Mino{
    uint32_t color;
    bool rotationNorth[4][4];
    bool rotationEast[4][4];
    bool rotationSouth[4][4];
    bool rotationWest[4][4];
} Mino;

// Performs all actions needed each game tick.
void gameTick(void);

// Creates a random mino. Returns FALSE if it can't.
bool createMino(void);

// Clears the board and restarts the game.
void restartGame(void);

// Attempts to lower the mino by one. Returns FALSE if it can't.
bool lowerMino(void);

// Writes the mino to the game board.
void setMino(void);

// Checks if any rows are full and need to be cleared.
void clearRows(void);

#endif