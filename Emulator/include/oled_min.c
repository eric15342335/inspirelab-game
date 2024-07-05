#include "oled_min.h"

#include <stdio.h>
#include <stdlib.h>

coord_t cursor = {.x = 0, .y = 0};

uint8_t BUFFER[BUFFER_SIZE];

void OLED_init(void) {
    _OLED_refresh_display();
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

void OLED_clear(void) {
    // Actually OLED_fill(0x00) works the same
    for (int i = 0; i < BUFFER_SIZE; i++) {
        BUFFER[i] = 0;
    }
    cursor.x = 0;
    cursor.y = 0;
}

// OLED global variables
uint8_t column, scroll;

// OLED plot a single character
void OLED_plotChar(char c) {
    uint16_t ptr = c - 32; // character pointer
    ptr += ptr << 2;       // -> ptr = (ch - 32) * 5;
    OLED_data_start();
    for (uint8_t i = 5; i; i--) {
        // printf("Set buffer at (%d, %d) to %d\n", cursor.x, cursor.y, OLED_FONT[ptr]);
        I2C_write(OLED_FONT[ptr++]);
    }
    I2C_write(0x00); // write space between characters
    JOY_OLED_end();
}

// OLED write a character or handle control characters
void OLED_write(char c) {
    c = c & 0x7F; // ignore top bit
    // normal character
    if (c >= 32) {
        OLED_plotChar(c);
        if (++column > 20) {
            column = 0;
            if (cursor.y == 7)
                OLED_scrollDisplay();
            else
                cursor.y++;
            OLED_setline((cursor.y + scroll) & 0x07);
        }
    }
    // new cursor.y
    else if (c == '\n') {
        column = 0;
        if (cursor.y == 7)
            OLED_scrollDisplay();
        else
            cursor.y++;
        OLED_setline((cursor.y + scroll) & 0x07);
    }
    // carriage return
    else if (c == '\r') {
        column = 0;
        OLED_setline((cursor.y + scroll) & 0x07);
    }
}

// OLED print string
void OLED_print(char * str) {
    while (*str)
        OLED_write(*str++);
    _OLED_refresh_display();
}

// OLED print string with newline
void OLED_println(char * str) {
    OLED_print(str);
    OLED_write('\n');
}

void OLED_setline(uint8_t line) {
    OLED_data_start();
    cursor.y = line;
    cursor.x = 0;
    JOY_OLED_end();
}

void OLED_scrollDisplay(void) {
    for (int i = 0; i < SCREEN_X; i++) {
        for (int j = 0; j < SCREEN_Y / AXIS_Y_STORAGE - 1; j++) {
            BUFFER[j * SCREEN_X + i] = BUFFER[(j + 1) * SCREEN_X + i];
        }
        BUFFER[(SCREEN_Y / AXIS_Y_STORAGE - 1) * SCREEN_X + i] = 0;
    }
    scroll = (scroll + 1) & 0x07;
}

void _OLED_setBuffer(uint8_t data) {
    // Set the buffer at the cursor position
    int byteIndex = cursor.y * SCREEN_X + cursor.x;
    BUFFER[byteIndex] = data;
    cursor.x++;
    //printf("Set buffer at (%d, %d) to %d\n", cursor.x, cursor.y, data);
}

void _OLED_refresh_display() {
    // Clear the screen
    printf("\033[2J\033[H");
    // upper border
    for (int x = 0; x < SCREEN_X + 2; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < SCREEN_Y; y++) {
        printf("|");
        for (int x = 0; x < SCREEN_X; x++) {
            int byteIndex = (y / 8) * SCREEN_X + x;
            int bitIndex = y % 8;
            int b = BUFFER[byteIndex];
            printf((b >> bitIndex) & 1 ? "." : "X");
        }
        printf("|");

        printf("\n");
    }
    // lower border
    for (int x = 0; x < SCREEN_X + 2; x++) {
        printf("-");
    }
    printf("\n");
}
