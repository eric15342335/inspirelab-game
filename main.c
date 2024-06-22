#include "driver.h"
#include "snake.h"
#include <stdlib.h>

;void game_init(){
    JOY_init();
    for (uint8_t i = 0;i < 128 ; i++){
        gameboard[i] = '0';
    }
    gameboard[33] = 'h';
    gameboard[43] = 'a';
    gameboard[32] = 't';

}

uint8_t gameboard_to_hex(uint8_t x,uint8_t y){
    uint8_t gameboard_index = y * 16 + x / 8;
    
    switch (gameboard[gameboard_index]) {
        case '0':
            return 0x00;
        case 'a':
            return apple[x % 8];
        case 'h':
            return rightSnakeHead[x % 8];
        case 't':
            return leftSnakeTail[x % 8];
        default:
            return 0x00;
    }
    //use switch to rewrite the above if statements


    return 0x00;
}

void display(){ //x horizontal y vertical
    uint8_t y, x;
    for (y = 0; y < 8; y++){
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++){
            JOY_OLED_send(gameboard_to_hex(x,y));
    }
    JOY_OLED_end();
  }
}

int main(){
    game_init();
    display();
    int randseed = 0;
    while (!JOY_act_pressed()){
        randseed++;
        DLY_ms1(100);
        //wait for the button to be pressed
    }
    srand(randseed);
    //start the game
    while (1){

    }
}