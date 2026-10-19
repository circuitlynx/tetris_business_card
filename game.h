#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "IS31FL3741.h"

#define MINO_SPAWN_POSITION_X 2
#define MINO_SPAWN_POSITION_Y 0

#define BOARD_HEIGHT 20

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

extern const Mino i_block;
extern const Mino s_block;
extern const Mino z_block;
extern const Mino o_block;
extern const Mino t_block;
extern const Mino l_block;
extern const Mino j_block;

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

// Checks if any rows are full and need to be cleared. If so, clear them.
void clearRows(void);

// If clear is set, erase the mino instead.
void drawMino(uint8_t y, uint8_t x, Mino mino, Orientation orientation, bool clear);

#endif