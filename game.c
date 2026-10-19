#include "game.h"
#include "IS31FL3741.h"

static uint8_t gameBoard[SCREEN_HEIGHT][SCREEN_WIDTH];
static ActiveMino currentMino = NONE;
static Orientation currentOrientation;
static uint8_t currentMinoX;
static uint8_t currentMinoY;

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