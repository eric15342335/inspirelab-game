#include "driver.h"
#include "snake.h"

void game_init(){
    JOY_init();
    for (uint8_t i = 0;i < 128 ; i++){
        gameboard[i] = '0';
    }
    gameboard[43] = 'a';
    gameboard[snakeTail] = 't';
    gameboard[snakeHead] = 'H';
    //reset the gameboard
}

int8_t direction(int8_t currentDirection){
    if (JOY_up_pressed() && gameboard[snakeHead] != 'f'){
        return -16;
    }
    if (JOY_down_pressed() && gameboard[snakeHead] != 'F'){
        return 16;
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
    else if (gameboard[snakeHead] == 'H' && currentDirection == 1 && snakeHead % 16 == 15){
        return true;
    }
    else if (gameboard[snakeHead] == 'h' && currentDirection == -1 && snakeHead % 16 == 0){
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

bool checkApple(int8_t currentDirection){
    return gameboard[snakeHead + currentDirection] == 'a';
}
    //check whether the next step is an apple

void moveSnake(int8_t currentDirection, bool apple){
    char newHead, oldHead;
    switch(currentDirection){
        case 1:
            newHead = 'H';
            break;
        case -1:
            newHead = 'h';
            break;
        case 16:
            newHead = 'F';
            break;
        case -16:
            newHead = 'f';
            break;
        default:
            newHead = '0'; //shut up compiler
            break;
    }
    gameboard[snakeHead+currentDirection] = newHead;
    if (gameboard[snakeHead] == 'H'){
        switch (currentDirection){
        case 16:
            oldHead = 'p';
            break;
        case -16:
            oldHead = 'b';
            break;
        case 1:
            oldHead = '-';
            break;
        default:
            break;
        }
    }
    else if (gameboard[snakeHead] == 'h'){
        switch (currentDirection){
        case 16:
            oldHead = 'q';
            break;
        case -16:
            oldHead = 'd';
            break;
        case -1:
            oldHead = '-';
            break;
        default:
            break;
        }
    }
    else if (gameboard[snakeHead] == 'F'){
        switch (currentDirection){
        case 1:
            oldHead = 'q';
            break;
        case -1:
            oldHead = 'b';
            break;
        case 16:
            oldHead = '|';
            break;
        default:
            break;
        }
    }
    else if (gameboard[snakeHead] == 'f'){
        switch (currentDirection){
        case 1:
            oldHead = 'p';
            break;
        case -1:
            oldHead = 'd';
            break;
        case -16:
            oldHead = '|';
            break;
        default:
            break;
        }
    }
    else{
        oldHead = '0'; //shut up compiler
    }
    gameboard[snakeHead] = oldHead;
    snakeHead += currentDirection;
    //head movement
    if (apple){
        return;
    }
    //if the snake eats the apple, the tail will not move
    char newTail;
    uint8_t newTailPos;
    if (gameboard[snakeTail] == 't'){
        newTailPos = snakeTail + 1;
        switch (gameboard[newTailPos]){
            case 'p':
                newTail = 'U';
                break;
            case 'b':
                newTail = 'u';
                break;
            case '-':
                newTail = 't';
                break;
            default:
                break;
        }
    }
    else if (gameboard[snakeTail] == 'u'){
        newTailPos = snakeTail - 16;
        switch (gameboard[newTailPos]){
            case 'q':
                newTail = 'T';
                break;
            case 'd':
                newTail = 't';
                break;
            case '|':
                newTail = 'U';
                break;
            default:
                break;
        }
    }
    else if (gameboard[snakeTail] == 'U'){
        newTailPos = snakeTail + 16;
        switch (gameboard[newTailPos]){
            case 'p':
                newTail = 'U';
                break;
            case 'b':
                newTail = 'u';
                break;
            case '-':
                newTail = 't';
                break;
            default:
                break;
        }
    }
    else if (gameboard[snakeTail] == 'T'){
        newTailPos = snakeTail - 1;
        switch (gameboard[newTailPos]){
            case 'q':
                newTail = 'T';
                break;
            case 'd':
                newTail = 't';
                break;
            case '|':
                newTail = 'U';
                break;
            default:
                break;
        }
    }
    else{
        newTail = '0';
        newTailPos = 0; //shut up compiler
    }
    gameboard[newTailPos] = newTail;
    snakeTail = newTailPos;
}

uint8_t gameboard_to_hex(uint8_t x,uint8_t y){
    uint8_t gameboard_index = y * 16 + x / 8;
    
    switch (gameboard[gameboard_index]) {
        case '0':
            return 0x00;
        case 'a':
            return apple[x % 8];
        case 'H':
            return rightSnakeHead[x % 8];
        case 'F':
            return downSnakeHead[x % 8];
        case 'f':
            return upSnakeHead[x % 8];
        case 'h':
            return leftSnakeHead[x % 8];
        case '|':
            return horizontalSnakeBody[x % 8];
        case '-':
            return verticalSnakeBody[x % 8];
        case 'U':
            return upSnakeTail[x % 8];
        case 'u':
            return downSnakeTail[x % 8];
        case 'T':
            return rightSnakeTail[x % 8];
        case 't':
            return leftSnakeTail[x % 8];
        case 'b':
            return topToLeft[x % 8];
        case 'd':
            return topToRight[x % 8];
        case 'p':
            return bottomToLeft[x % 8];
        case 'q':
            return bottomToRight[x % 8];
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
    while (!JOY_pad_pressed()){
        randseed = randseed;
        //wait for the button to be pressed
    } 
    JOY_sound(1000,100);
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

        bool apple = checkApple(currentDirection);
        //check if the snake has eaten the apple

        moveSnake(currentDirection,apple);
        //move the snake
        //generate a new apple
        display();
        //display the gameboard
        DLY_ms(100);
        //wait for a while
    }
}