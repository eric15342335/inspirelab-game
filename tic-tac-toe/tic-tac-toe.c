#include "driver.h"
#include "tic-tac-toe.h"

char gameboard[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // 3x3 gameboard
uint8_t selectpos; // position of the cursor

uint8_t select_to_hex(const uint8_t x, const uint8_t y){
    #define boxoffset 2
    #define topoffset 3
    #define middleoffset 0
    #define bottomoffset 5
    int boxStartX;
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
            JOY_OLED_send(gameboard_to_hex(x, y) | select_to_hex(x, y));
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

void selectposition(){
    selectpos = 4;
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
        display();
        //play();
        //display();
        //if (checkwin() == 1){
        //    break;
        DLY_ms(100);
        }
    return 0;

}