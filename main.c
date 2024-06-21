#include "driver.h"

void display_raindrop(uint8_t xdotpos, uint8_t ydotpos){
    uint8_t y, x;
    for (y = 0; y < 8; y++){
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++){
        if (x == xdotpos && ydotpos / 8 == y){
            JOY_OLED_send(0x01 << (ydotpos % 8));
        } 
        else{
            JOY_OLED_send(0x00);
        }
    }
    JOY_OLED_end();
  }
}

//x horizontal y vertical
void display_raining(uint8_t xpos){
    for (uint8_t i = 0; i < 64; i++){
        display_raindrop(xpos, i);
        DLY_ms(100);
    }
}

int main(){
    JOY_init();
    while (1){
        OLED_init();
        display_raining(64);
    };
}