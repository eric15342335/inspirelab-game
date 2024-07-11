#include "driver.h"
#include "tic-tac-toe.h"

char gameboard[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // 3x3 gameboard

int8_t selectpos; // position of the cursor

uint8_t cross_to_hex(const uint8_t x, const uint8_t y){
        #define boxoffset 2
    #define topoffset 3
    #define middleoffset 0
    #define bottomoffset 5
    uint8_t boxStartX;
    uint8_t displaycross;
    if (x <= leftborder + 1|| x >= rightborder - 3){
        return 0x00;
    }
    if (gameboard[0] == 'X' && !(x >= middleleftborder - 3|| y > middletopborder)){
        displaycross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[1] == 'X' && !(x <= middleleftborder + 1 ||x >= middlerightborder - 3|| y > middletopborder)){
        displaycross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[2] == 'X' && !(x <= middlerightborder + 1 || y > middletopborder)){
        displaycross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else if (gameboard[3] == 'X' && !(x >= middleleftborder - 3 || y <= middletopborder || y >= middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[4] == 'X' && !(x <= middleleftborder + 1 || x >= middlerightborder - 3 || y <= middletopborder || y >= middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[5] == 'X' && !(x <= middlerightborder + 1 || y <= middletopborder || y >= middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else if (gameboard[6] == 'X' && !(x >= middleleftborder - 3 || y < middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = leftborder + boxoffset;
    }
    else if (gameboard[7] == 'X' && !(x <= middleleftborder + 1 || x >= middlerightborder - 3 || y < middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = middleleftborder + boxoffset;
    }
    else if (gameboard[8] == 'X' && !(x <= middlerightborder + 1 || y < middlebottomborder)){
        displaycross  = 0xFF;
        boxStartX = middlerightborder + boxoffset;
    }
    else {
        return 0x00;
    }

    uint8_t crosspixel;
    switch (y) {
        case 0:
            crosspixel =  cross[x - boxStartX] << topoffset;
            break;
        case 1:
            crosspixel = ((cross[x - boxStartX] >> (8 - topoffset)) | (cross[x - boxStartX + 16] << topoffset));
            break;
        case 2:
            crosspixel = cross[x - boxStartX + 16] >> (8 - topoffset); //top boxes
            break;
        case 3:
            crosspixel = cross[x - boxStartX] << middleoffset;
            break;
        case 4:
            crosspixel = ((cross[x - boxStartX] >> (8 - middleoffset)) | (cross[x - boxStartX + 16] << middleoffset)); //middle boxes
            break;
        case 5:
            crosspixel = cross[x - boxStartX] << bottomoffset;
            break;
        case 6:
            crosspixel = ((cross[x - boxStartX] >> (8 - bottomoffset)) | (cross[x - boxStartX + 16] << bottomoffset));
            break;
        case 7:
            crosspixel = cross[x - boxStartX + 16] >> (8 - bottomoffset); //bottom boxes
        default:
            return 0x00;
        }
    return crosspixel & displaycross;

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
            if (x <= middleleftborder + 1 ||x >= middlerightborder - 3|| y > middletopborder){
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
    return 0x00; //shut up compiler
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
                          cross_to_hex(x, y));
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

void selectposition(){
    selectpos = 4;
    display();
    while (1){
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
            display();
            break;
        }
        DLY_ms(100);
    }
}

int main(){
    JOY_init();
    display();
    while (1){
        selectposition();
        //play();
        //display();
        //if (checkwin() == 1){
        //    break;
        DLY_ms(100);
        }
    return 0;

}