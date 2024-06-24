#include "driver.h"

int main(){
    JOY_init();
    OLED_init();
    OLED_println("Hello World!");
}


//x horizontal y vertical
void display_raining(uint8_t xpos){
    for (uint8_t i = 0; i < 64; i++){
        display_raindrop(xpos, i);
        DLY_ms(16);
    }
}

void display_raindrop(uint8_t xpos, uint8_t ypos){
    for (uint8_t y = 0; y < 8; y++){
        JOY_OLED_data_start(y);
        for (uint8_t x = 0; x < 128 ; x++){
            if (x == xpos && y == ypos / 8){
                JOY_OLED_send(0x80 >> (x % 8));
            }
            else{
                JOY_OLED_send(0x00);
            }
        JOY_OLED_end();
        }

    }
}