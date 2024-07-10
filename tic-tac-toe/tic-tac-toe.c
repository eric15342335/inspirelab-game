#include "driver.h"
#include "tic-tac-toe.h"

char gameboard[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // 3x3 gameboard
uint8_t selectpos; // position of the cursor

uint8_t select_to_hex(const uint8_t x, const uint8_t y){
    if (x <= leftborder || x >= rightborder){
        return 0x00;
    }
    switch (selectpos){
        case 0:
            if (x >= middleleftborder || y >= middletopborder){
                return 0x00;
            }
            else{
                return selectframe[x - leftborder - 1 + y * 16];
            }
        case 1:
            if (x <= middleleftborder || x >= middlerightborder || y >= middletopborder){
                return 0x00;
            }
            else{
                return selectframe[x - middleleftborder - 1 + y * 16];
            }
        case 2:
            if (x <= middlerightborder || y >= middletopborder){
                return 0x00;
            }
            else{
                return selectframe[x - middlerightborder - 1 + y * 16];
            }
        case 3:
            if (x >= middleleftborder || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - leftborder - 1 + (y - middletopborder) * 16];
            }
        case 4:
            if (x <= middleleftborder || x >= middlerightborder || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - middleleftborder - 1 + (y - middletopborder) * 16];
            }
        case 5:
            if (x <= middlerightborder || y <= middletopborder || y >= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - middlerightborder - 1 + (y - middletopborder) * 16];
            }
        case 6:
            if (x >= middleleftborder || y <= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - leftborder - 1 + (y - middlebottomborder) * 16];
            }
        case 7:
            if (x <= middleleftborder || x >= middlerightborder || y <= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - middleleftborder - 1 + (y - middlebottomborder) * 16];
            }
        case 8:
            if (x <= middlerightborder || y <= middlebottomborder){
                return 0x00;
            }
            else{
                return selectframe[x - middlerightborder - 1 + (y - middlebottomborder) * 16];
            }
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
        else if (JOY_down_pressed() && selectpos < 7){
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