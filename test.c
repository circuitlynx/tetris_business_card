#include "IS31FL3741.h"
#include "game.h"

void colorTest(void){
    for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(0,x,RED);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(1,x,GREEN);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(2,x,BLUE);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(3,x,CYAN);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(4,x,ORANGE);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(5,x,YELLOW);
        }
        for (int x = 0; x < SCREEN_WIDTH; x++){
            writePixel(6,x,PURPLE);
    }
}

void minoTest(void){
    drawMino(9,-2,i_block,EAST,0);
    drawMino(7,4,i_block,SOUTH,0);
    drawMino(4,0,i_block,WEST,0);

    drawMino(11,0,s_block,NORTH,0);
    drawMino(7,-2,s_block,EAST,0);
    drawMino(7,6,s_block,WEST,0);

    drawMino(10,3,z_block,NORTH,0);
    drawMino(5,1,z_block,WEST,0);

    drawMino(8,1,o_block,NORTH,0);
    drawMino(7,4,o_block,EAST,0);

    drawMino(11,2,t_block,NORTH,0);
    drawMino(9,5,t_block,SOUTH,0);
    drawMino(6,2,t_block,WEST,0);

    drawMino(11,5,l_block,NORTH,0);
    drawMino(9,0,l_block,SOUTH,0);

    drawMino(5,5,j_block,SOUTH,0);
}