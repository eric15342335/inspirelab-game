#include "driver.h"
#include "snake.h"

void game_init(){
    JOY_init();
    for (uint8_t i = 0;i < 128 ; i++){
        gameboard[i] = '0';
    }
    gameboard[snakeHead] = 'H';
    gameboard[43] = 'a';
    gameboard[snakeHead - 1] = 't';
    //reset the gameboard
}

int8_t direction(int8_t currentDirection){
    if (JOY_up_pressed() && gameboard[snakeHead] != 'f'){
        return -12;
    }
    if (JOY_down_pressed() && gameboard[snakeHead] != 'F'){
        return 12;
    }
    if (JOY_left_pressed() && gameboard[snakeHead] != 'h'){
        return -1;
    }
    if (JOY_right_pressed() && gameboard[snakeHead] != 'H'){
        return 1;
    }
    //check if the snake is running to itself
    return currentDirection;
}

bool checkWallAndItself(int8_t currentDirection){
    if (snakeHead + currentDirection < 0 || snakeHead + currentDirection > 127){
        return true;
    }
    else if (gameboard[snakeHead] = 'H' && currentDirection == 1 && snakeHead % 16 == 15){
        return true;
    }
    else if (gameboard[snakeHead] = 'h' && currentDirection == -1 && snakeHead % 16 == 0){
        return true;
    }
    //check whether the snake hits the wall

    if (gameboard[snakeHead + currentDirection] != '0' || gameboard[snakeHead + currentDirection] != 'a'){
        return false;
    }
    else{
        return true;
    }
    //check whether the snake hits itself
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
        DLY_ms(100);
        //wait for the button to be pressed
    }
    int8_t currentDirection = 0;
    //start the game
    while (1){
        for (uint8_t i = 0; i < 3; i++){
            currentDirection = direction(currentDirection);
            DLY_ms(125);
        }
        //get the direction
        if (!checkWallAndItself(currentDirection)){
            break;
        }
        //check if the snake is dead

        
        //check if the snake has eaten the apple
        //move the snake
        //generate a new apple
        //display the gameboard
        //wait for a while
    }
}