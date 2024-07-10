#include "driver.h"
#include "tic-tac-toe.h"

uint8_t gameboard_to_hex(const uint8_t x, const uint8_t y){
    if (x == leftborder || x == rightborder || x == middleleftborder || x == middlerightborder) return 0xFF; //left and right border
    if (x > leftborder && x < rightborder){
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
    else return 0x00;
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

int main(){
    JOY_init();
    display();
    return 0;

}