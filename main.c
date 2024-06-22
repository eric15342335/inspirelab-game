#include "driver.h"
#include "snake.h"

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
    if (gameboard[gameboard_index] == '0'){
        return 0x00;
    }
    if (gameboard[gameboard_index] == 'a'){
        return apple[x % 8];
    }
    if (gameboard[gameboard_index] == 'h'){
        return rightSnakeHead[x % 8];
    }
    if (gameboard[gameboard_index] == 't'){
        return leftSnakeTail[x % 8];
    }
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
}