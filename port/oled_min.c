#include "oled_min.h"

#include <stdio.h>
#include <stdlib.h>

coord_t cursor = {.x = 0, .y = 0};

uint8_t BUFFER[BUFFER_SIZE];

void OLED_init(void) {
    // Clear the screen
    system("clear");
    // upper border
    for (int x = 0; x < SCREEN_X+2; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < SCREEN_Y; y++) {
        printf("|");
        for (int x = 0; x < SCREEN_X; x++) {
            int byteIndex = (y / 8) * SCREEN_X + x;
            int bitIndex = y % 8;
            int b = BUFFER[byteIndex];
            printf((b >> bitIndex) & 1 ? "X" : ".");
        }
        printf("|");
        
        printf("\n");
    }
    // lower border
    for (int x = 0; x < SCREEN_X+2; x++) {
        printf("-");
    }
    printf("\n");
    return;
}

void OLED_data_start(void) { _OLED_doNothing(); }

void _OLED_doNothing(void) {
    // Do nothing
}

void OLED_setpos(uint8_t x, uint8_t y) {
    cursor.x = x;
    cursor.y = y;
}

void OLED_fill(uint8_t p) {
    for (uint8_t y = 0; y < SCREEN_Y / AXIS_Y_STORAGE; y++) {
        OLED_data_start();
        for (uint8_t x = 0; x < SCREEN_X; x++) {
            BUFFER[y * SCREEN_X + x] = p;
        }
    }
}

void _OLED_setBuffer(uint8_t data) {
    // Set the buffer at the cursor position
    int byteIndex = cursor.y * SCREEN_X + cursor.x;
    BUFFER[byteIndex] = data;
    cursor.x++;
    //printf("Set buffer at (%d, %d) to %d\n", cursor.x, cursor.y, data);
}
