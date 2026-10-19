#include "game.h"
#include "IS31FL3741.h"

// There will be a 2 unit buffer around every playable edge of the board.
static uint8_t gameBoard[BOARD_HEIGHT][SCREEN_WIDTH + 4];
static ActiveMino currentMino = NONE;
static Orientation currentOrientation;
static uint8_t currentMinoX = MINO_SPAWN_POSITION_X;
static uint8_t currentMinoY = MINO_SPAWN_POSITION_Y;

const Mino i_block = {
    .color = CYAN,
    .rotationNorth = {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    },
};

const Mino s_block = {
    .color = GREEN,
    .rotationNorth = {
        {0,0,1,1},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,0,1,1},
        {0,1,1,0},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    },
};

const Mino z_block = {
    .color = RED,
    .rotationNorth = {
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,0,1},
        {0,0,1,1},
        {0,0,1,0},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    },
};

const Mino o_block = {
    .color = YELLOW,
    .rotationNorth = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
};

const Mino t_block = {
    .color = PURPLE,
    .rotationNorth = {
        {0,0,1,0},
        {0,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,1,0},
        {0,0,1,1},
        {0,0,1,0},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,1,1,1},
        {0,0,1,0},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,0,1,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    },
};

const Mino l_block = {
    .color = ORANGE,
    .rotationNorth = {
        {0,0,0,1},
        {0,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,1,1,1},
        {0,1,0,0},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    },
};

const Mino j_block = {
    .color = BLUE,
    .rotationNorth = {
        {0,1,0,0},
        {0,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    .rotationEast = {
        {0,0,1,1},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    },
    .rotationSouth = {
        {0,0,0,0},
        {0,1,1,1},
        {0,0,0,1},
        {0,0,0,0}
    },
    .rotationWest = {
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
};

void gameTick(void){
    if (currentMino == NONE){
        if (!createMino()) restartGame();
        return;
    }
    
    if (!lowerMino()) {
        setMino();
        clearRows();
        return;
    }
}

void drawMino(uint8_t y, uint8_t x, Mino mino, Orientation orientation, bool clear){
    bool (*toDraw)[4];
    switch (orientation) {
        case NORTH:
            toDraw = mino.rotationNorth;
            break;
        case EAST:
            toDraw = mino.rotationEast;
            break;
        case SOUTH:
            toDraw = mino.rotationSouth;
            break;
        case WEST:
            toDraw = mino.rotationWest;
            break;
    }
    uint32_t color;
    if (clear) color = BLACK;
    else color = mino.color;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (toDraw[j][i] == 1) {
                writePixel(y + j, x + i, color);
            }
        }
    }
}