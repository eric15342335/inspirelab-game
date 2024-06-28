#ifndef OLED_MIN_H
#define OLED_MIN_H

#include "driver.h"

#include <stdint.h>

typedef struct coord {
    uint8_t x; // < SCREEN_X
    uint8_t y; // < SCREEN_Y
} coord_t;

#define SCREEN_X 128
#define SCREEN_Y 64
#define AXIS_Y_STORAGE 8
#define BUFFER_SIZE SCREEN_X * SCREEN_Y / AXIS_Y_STORAGE

void OLED_init(void);
void OLED_data_start(void);
void OLED_setpos(uint8_t x, uint8_t y);
void OLED_fill(uint8_t p);

/**
 * @note
 * Functions start with _ does not exist in the original
 * oled_min.h file. They are created for simulation purposes.
 */

#include <stdbool.h>
void _OLED_setBuffer(uint8_t data);
void _OLED_doNothing(void);

#define _OLED_refresh() OLED_init()

#endif // OLED_MIN_H
