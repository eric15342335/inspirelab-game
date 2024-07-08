#include "driver.h"
#include "image.h"
#include "music.h"
#include "snake.h"

void game_init(void) {
    JOY_init();
    for (uint8_t i = 0; i < 128; i++) {
        gameboard[i] = '0';
    }
    gameboard[43] = 'a';
    gameboard[snakeTail] = 't';
    gameboard[init_snakeBody] = '-';
    gameboard[snakeHead] = 'H';
    // reset the gameboard
}

int8_t direction(const int8_t currentDirection) {
    if (JOY_up_pressed() && gameboard[snakeHead] != 'f') {
        return -16; // go up
    }
    if (JOY_down_pressed() && gameboard[snakeHead] != 'F') {
        return 16; // go down
    }
    if (JOY_left_pressed() && gameboard[snakeHead] != 'H') {
        return -1; // go left
    }
    if (JOY_right_pressed() && gameboard[snakeHead] != 'h') {
        return 1; // go right
    }
    // check if the snake is running to itself
    // if not then set the direction
    return currentDirection;
}

bool checkWallAndItself(const int8_t currentDirection) {
    if (snakeHead + currentDirection < 0 || snakeHead + currentDirection > 127) {
        return true;
    }
    // check whether the snake goes over the top and bottom border
    else if (gameboard[snakeHead] == 'H' && currentDirection == 1 &&
             snakeHead % 16 == 15) {
        return true;
    }
    // check whether the snake goes over the right border
    else if (gameboard[snakeHead] == 'h' && currentDirection == -1 &&
             snakeHead % 16 == 0) {
        return true;
    }
    // check whether the snake goes over the left wall

    return (gameboard[snakeHead + currentDirection] != '0' &&
            gameboard[snakeHead + currentDirection] != 'a');
    // check whether the snake hits itself
}

bool checkWin(void) {
    for (uint8_t i = 0; i < 128; i++) {
        if (gameboard[i] == '0' || gameboard[i] == 'a') {
            return false;
        }
    }
    return true;
    // if there is no empty space, the player wins
}

bool checkApple(const int8_t currentDirection) {
    return gameboard[snakeHead + currentDirection] == 'a';
}
// check whether the next step is an apple

void generate_apple(void) {
    uint8_t applePos;
    do {
        applePos = JOY_random() % 128;
    } while (gameboard[applePos] != '0');
    gameboard[applePos] = 'a';
    // random a location to put down an apple
    // random till that is a empty space
}

void moveSnake(const int8_t currentDirection, const bool apple) {
    char newHead = '0', oldHead = '0';
    switch (currentDirection) {
        case 1:
            newHead = 'H';
            break;
        case -1:
            newHead = 'h';
            break;
        case 16:
            newHead = 'f';
            break;
        case -16:
            newHead = 'F';
            break;
        default:
            break;
    }
    // generate a new head for the snake in the next step
    // different head for different direction
    gameboard[snakeHead + currentDirection] = newHead;
    // put down the new head
    if (gameboard[snakeHead] == 'H') {
        switch (currentDirection) {
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
    else if (gameboard[snakeHead] == 'h') {
        switch (currentDirection) {
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
    else if (gameboard[snakeHead] == 'f') {
        switch (currentDirection) {
            case 1:
                oldHead = 'd';
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
    else if (gameboard[snakeHead] == 'F') {
        switch (currentDirection) {
            case 1:
                oldHead = 'q';
                break;
            case -1:
                oldHead = 'p';
                break;
            case -16:
                oldHead = '|';
                break;
            default:
                break;
        }
    }
    // update the old head location to body of snake with different direction
    gameboard[snakeHead] = oldHead;
    // put down the new snake body into old head location
    snakeHead += currentDirection;
    // update the snake head location

    if (apple) {
        return;
    }
    // if the snake eats the apple, the tail will not move
    // code below should be skipped

    char newTail = '0';
    uint8_t newTailPos = 0;
    if (gameboard[snakeTail] == 't') {
        newTailPos = snakeTail + 1;
        switch (gameboard[newTailPos]) {
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
    else if (gameboard[snakeTail] == 'u') {
        newTailPos = snakeTail - 16;
        switch (gameboard[newTailPos]) {
            case 'p':
                newTail = 'T';
                break;
            case 'q':
                newTail = 't';
                break;
            case '|':
                newTail = 'u';
                break;
            default:
                break;
        }
    }
    else if (gameboard[snakeTail] == 'U') {
        newTailPos = snakeTail + 16;
        switch (gameboard[newTailPos]) {
            case 'd':
                newTail = 't';
                break;
            case 'b':
                newTail = 'T';
                break;
            case '|':
                newTail = 'U';
                break;
            default:
                break;
        }
    }
    else if (gameboard[snakeTail] == 'T') {
        newTailPos = snakeTail - 1;
        switch (gameboard[newTailPos]) {
            case 'q':
                newTail = 'U';
                break;
            case 'd':
                newTail = 'u';
                break;
            case '-':
                newTail = 'T';
                break;
            default:
                break;
        }
    }
    // set the new tail location with different direction
    // set the tail direction according to the snake posture

    gameboard[snakeTail] = '0';
    // old snake tail should go one block foward, so the original snake tail should be
    // set to empty

    gameboard[newTailPos] = newTail;
    snakeTail = newTailPos;
    // update new tail location
}

uint8_t gameboard_to_hex(const uint8_t x, const uint8_t y) {
    uint8_t gameboard_index = y * 16 + x / 8;
    // convert gameboard coordinate to display input array coordinate
    switch (gameboard[gameboard_index]) {
        case '0':
            return 0x00;
        case 'a':
            return apple[x % 8];
        case 'H':
            return rightSnakeHead[x % 8];
        case 'f':
            return downSnakeHead[x % 8];
        case 'F':
            return upSnakeHead[x % 8];
        case 'h':
            return leftSnakeHead[x % 8];
        case '-':
            return horizontalSnakeBody[x % 8];
        case '|':
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
}

void display(void) {
    // x horizontal y vertical
    uint8_t y, x;
    for (y = 0; y < 8; y++) {
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++) {
            JOY_OLED_send(gameboard_to_hex(x, y));
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

void displayData(uint8_t _image_data[]) {
    uint8_t y, x;
    for (y = 0; y < 8; y++) {
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++) {
            JOY_OLED_send(_image_data[y * 128 + x]);
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

int main(void) {
    game_init();
    OLED_clear();
    {
        uint8_t image_data_2[1024];
        for (int i = 0; i < 1024; i++) {
            image_data_2[i] = image_data[i];
        }
        for (uint8_t i = 0; i < 9; i += 4) {
            for (uint8_t j = i; j < i + 6; j++) {
                displayData(image_data_2);
                shiftImage((offset_t){j, j % 6 - 3}, image_data, image_data_2,
                    (ScreenCoord){128, 64});
            }
            negateImage(image_data_2, 1024);
            playMusic((noterange_t){i % 13, i % 13 + 4});
        }
        playMusic((noterange_t){12, 13});
    }
    
    OLED_println("Press any key to start");
    _OLED_refresh_display();
    display();
    uint16_t seed = 0;
    while (!JOY_pad_pressed()) {
        seed++;
        if (seed > 65530) {
            seed = 0;
        } // boundary check of uint16_t rnval
        // generate a seed according to the time between boot and button pressed
        DLY_ms(1);
        // wait for the button to be pressed
    }
    JOY_setseed(seed);
    int8_t currentDirection = 1;
    // initialize the direction
    currentDirection = direction(currentDirection);
    JOY_sound(1000, 100);
    // start the game
    while (1) {
        for (uint8_t i = 0; i < 7; i++) {
            currentDirection = direction(currentDirection);
            DLY_ms(50);
            // update direction every 50ms
        }
        // get the direction
        if (checkWallAndItself(currentDirection)) {
            OLED_println("Game Over!");
            break;
        }
        // check if the snake is dead

        bool apple = checkApple(currentDirection);
        // check if the snake has eaten the apple

        moveSnake(currentDirection, apple);
        // move the snake
        // generate a new apple
        if (apple) {
            JOY_sound(1000, 100);
            generate_apple();
        }
        display();
        // display the gameboard
        DLY_ms(50);
        // wait for a while
        if (checkWin()) {
            OLED_println("You Win!");
            break;
        }
    }
    DLY_ms(2000);
}
