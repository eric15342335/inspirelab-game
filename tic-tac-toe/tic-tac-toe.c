#include "driver.h"
#include "tic-tac-toe.h"

char gameboard[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // 3x3 gameboard

int8_t selectpos; // position of the cursor


uint8_t circlecross_to_hex(const uint8_t x, const uint8_t y, char player) {
    #define boxoffset 2
    #define topoffset 3
    #define middleoffset 0
    #define bottomoffset 5
    uint8_t boxStartX;
    uint8_t displaycirclecross;
    const uint8_t * pic;
    if (x <= leftborder + 1|| x >= rightborder - 3){
        return 0x00;
    }
    if (player == 'O'){
        pic = (const uint8_t * )circle;
    }
    else if (player == 'X'){
        pic = (const uint8_t * )cross;
    }
    else {
        return 0x00;
    }
    if (gameboard[0] == player && !(x >= middleleftborder - 3|| y > middletopborder)){
        displaycirclecross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[1] == player && !(x <= middleleftborder + 1 ||x >= middlerightborder - 3|| y > middletopborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[2] == player && !(x <= middlerightborder + 1 || y > middletopborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else if (gameboard[3] == player && !(x >= middleleftborder - 3 || y <= middletopborder || y >= middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[4] == player && !(x <= middleleftborder + 1 || x >= middlerightborder - 3 || y <= middletopborder || y >= middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[5] == player && !(x <= middlerightborder + 1 || y <= middletopborder || y >= middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else if (gameboard[6] == player && !(x >= middleleftborder - 3 || y < middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[7] == player && !(x <= middleleftborder + 1 || x >= middlerightborder - 3 || y < middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[8] == player && !(x <= middlerightborder + 1 || y < middlebottomborder)){
        displaycirclecross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else {
        return 0x00;
    }
    // the above code is to determine if the circle should be displayed

    uint8_t circlecrosspixel;
    switch (y) {
        case 0:
            circlecrosspixel =  pic[x - boxStartX] << topoffset;
            break;
        case 1:
            circlecrosspixel = ((pic[x - boxStartX] >> (8 - topoffset)) | (pic[x - boxStartX + 16] << topoffset));
            break;
        case 2:
            circlecrosspixel = pic[x - boxStartX + 16] >> (8 - topoffset); //top boxes
            break;
        case 3:
            circlecrosspixel = pic[x - boxStartX] << middleoffset;
            break;
        case 4:
            circlecrosspixel = ((pic[x - boxStartX] >> (8 - middleoffset)) | (pic[x - boxStartX + 16] << middleoffset)); //middle boxes
            break;
        case 5:
            circlecrosspixel = pic[x - boxStartX] << bottomoffset;
            break;
        case 6:
            circlecrosspixel = ((pic[x - boxStartX] >> (8 - bottomoffset)) | (pic[x - boxStartX + 16] << bottomoffset));
            break;
        case 7:
            circlecrosspixel = pic[x - boxStartX + 16] >> (8 - bottomoffset); //bottom boxes
            break;
        default:
            return 0x00;
        }
    return circlecrosspixel & displaycirclecross;
    //bitwise and to only display the circle where it should be

}

uint8_t select_to_hex(const uint8_t x, const uint8_t y){
    #define boxoffset 2
    #define topoffset 3
    #define middleoffset 0
    #define bottomoffset 5
    int boxStartX;
    if (selectpos == -1){
        return 0x00;
    }
    if (x <= leftborder + 1|| x >= rightborder - 3){
        return 0x00;
    }
    switch (selectpos){
        case 0:
            if (x >= middleleftborder - 3|| y > middletopborder){
                return 0x00;
            }
            boxStartX = leftborder + boxoffset;
            break;
        case 1:
            if (x <= middleleftborder + 1 || x >= middlerightborder - 3|| y > middletopborder){
                return 0x00;
            }
            boxStartX = middleleftborder + boxoffset;
            break;
        case 2:
            if (x <= middlerightborder + 1 || y > middletopborder){
                return 0x00;
            }
            boxStartX = middlerightborder + boxoffset;
            break;
        case 3:
            if (x >= middleleftborder - 3 || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            boxStartX = leftborder + boxoffset;
            break;
        case 4:
            if (x <= middleleftborder + 1 || x >= middlerightborder - 3 || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            boxStartX = middleleftborder + boxoffset;
            break;
        case 5:
            if (x <= middlerightborder + 1 || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            boxStartX = middlerightborder + boxoffset;
            break;
        case 6:
            if (x >= middleleftborder - 3 || y < middlebottomborder){
                return 0x00;
            }
            boxStartX = leftborder + boxoffset;
            break;
        case 7:
            if (x <= middleleftborder + 1 || x >= middlerightborder - 3 || y < middlebottomborder){
                return 0x00;
            }
            boxStartX = middleleftborder + boxoffset;
            break;
        case 8:
            if (x <= middlerightborder + 1 || y < middlebottomborder){
                return 0x00;
            }
            boxStartX = middlerightborder + boxoffset;
            break;
        default:
            boxStartX = 0;
            break;
        }
    switch (y) {
        case 0:
            return selectframe[x - boxStartX] << topoffset;
        case 1:
            return ((selectframe[x - boxStartX] >> (8 - topoffset)) | (selectframe[x - boxStartX + 16] << topoffset));
        case 2:
            return selectframe[x - boxStartX + 16] >> (8 - topoffset); //top boxes
        case 3:
            return selectframe[x - boxStartX] << middleoffset;
        case 4:
            return ((selectframe[x - boxStartX] >> (8 - middleoffset)) | (selectframe[x - boxStartX + 16] << middleoffset)); //middle boxes
        case 5:
            return selectframe[x - boxStartX] << bottomoffset;
        case 6:
            return ((selectframe[x - boxStartX] >> (8 - bottomoffset)) | (selectframe[x - boxStartX + 16] << bottomoffset));
        case 7:
            return selectframe[x - boxStartX + 16] >> (8 - bottomoffset); //bottom boxes
        default:
            return 0x00;
        }
}
    

uint8_t gameboard_to_hex(const uint8_t x, const uint8_t y){
    if (x == leftborder || x == rightborder || x == middleleftborder || x == middlerightborder){
        return 0xFF; //left and right border
    }
    if (x > leftborder && x < rightborder) {
        switch (y){
            case topborder:
                return 0x01;
            case middletopborder:
                return 0x20;
            case middlebottomborder:
                return 0x04;
            case bottomborder:
                return 0x80;
            default:
                return 0x00;
        }
    }
    else {
        return 0x00;
    }
}

void display(void) {
    // x horizontal y vertical
    uint8_t y, x;
    for (y = 0; y < 8; y++) {
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++) {
            JOY_OLED_send(gameboard_to_hex(x, y) | select_to_hex(x, y) |
                          circlecross_to_hex(x, y,'X') | circlecross_to_hex(x,y,'O'));
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

void selectposition(){
    selectpos = 4;
    uint16_t randseed;
    uint8_t i;
    display();
    while (1){
        randseed = 0; //shut up compiler warning on windows 10
        for (i = 0; i < 10; i++){
            randseed++;
            if (randseed == 65530){
                randseed = 0;
            }
            DLY_ms(10); //much higher rate of switching randseed
        }
        if (JOY_up_pressed() && selectpos > 2){
            selectpos -= 3;
            display();
        }
        else if (JOY_down_pressed() && selectpos < 6){
            selectpos += 3;
            display();
        }
        else if (JOY_left_pressed() && selectpos % 3 != 0){
            selectpos -= 1;
            display();
        }
        else if (JOY_right_pressed() && selectpos % 3 != 2){
            selectpos += 1;
            display();
        }
        else if (JOY_act_pressed() && gameboard[selectpos] == ' '){
            JOY_sound(1000, 100);
            gameboard[selectpos] = 'X';
            selectpos = -1;
            JOY_setseed(randseed);
            display();
            break;
        }
        DLY_ms(10);
    }
}

void play(){
    while (1){
        uint8_t randpos = JOY_random() % 9;
        if (gameboard[randpos] == ' '){
            gameboard[randpos] = 'O';
            JOY_sound(500, 200);
            DLY_ms(300);
            break;
        }
    }
    display();

} 

char checkwinside(){
    for (uint8_t i = 0; i < 9; i += 3){
        if (gameboard[i] == gameboard[i + 1] && gameboard[i + 1] == gameboard[i + 2] && gameboard[i] != ' '){
            return gameboard[i];
        }
    }
    // horizontal
    for (uint8_t i = 0; i < 3; i++){
        if (gameboard[i] == gameboard[i + 3] && gameboard[i + 3] == gameboard[i + 6] && gameboard[i] != ' '){
            return gameboard[i];
        }
    }
    // vertical
    if (gameboard[0] == gameboard[4] && gameboard[4] == gameboard[8] && gameboard[0] != ' '){
        return gameboard[0];
    }
    if (gameboard[2] == gameboard[4] && gameboard[4] == gameboard[6] && gameboard[2] != ' '){
        return gameboard[2];
    }
    // 2 diagonals
    for (uint8_t i = 0; i < 9; i++){
        if (gameboard[i] == ' ') return 0;
    }
    return 'd'; // check draw or not
}

int main(){
    char winner;
    JOY_init();
    display();
    while (1) {
        selectposition();
        winner = checkwinside();
        if (winner != 0) break;
        play();
        winner = checkwinside();
        if (winner != 0) break;
        DLY_ms(100);
    }
    switch (winner){
        case 'X':
            OLED_println("You \nwin!");
            JOY_sound(1000, 1000);
            break;
        case 'O':
            OLED_println("You \nlose!");
            JOY_sound(500, 1000);
            break;
        case 'd':
            OLED_println("Draw!");
            JOY_sound(1000, 1000);
            break;
    }
    _OLED_refresh_display();
}