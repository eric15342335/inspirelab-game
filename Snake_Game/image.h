#pragma once

#include "driver.h"
const uint8_t image_data[1024] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xE0, 0xD8, 0xD8,
    0xF8, 0xF8, 0xF8, 0xF8, 0xFF, 0xDF, 0xFF, 0xDF, 0xFF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF,
    0x5F, 0xDF, 0x5F, 0xDF, 0x1F, 0xDF, 0x16, 0xDF, 0x07, 0xDF, 0xC7, 0xDF, 0xD7, 0xDF,
    0xD7, 0xD7, 0xDF, 0xD7, 0xDF, 0xC7, 0xDF, 0x07, 0xDF, 0x1F, 0xDF, 0x1F, 0xDF, 0x58,
    0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xC0, 0xC0, 0xC0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x40, 0x58, 0xDA, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB,
    0xDB, 0xDB, 0x5B, 0x5B, 0x5B, 0x5B, 0xDB, 0x5A, 0x5A, 0x42, 0x5A, 0x5A, 0x5A, 0xDA,
    0x9A, 0x1A, 0x5A, 0x72, 0x42, 0x52, 0x12, 0x9E, 0x18, 0x9E, 0x18, 0x9E, 0x00, 0xB2,
    0x00, 0x32, 0x32, 0x02, 0x32, 0x00, 0xB2, 0x00, 0x9A, 0x18, 0x9E, 0x5A, 0x5A, 0x12,
    0x52, 0x62, 0x32, 0x9A, 0xDA, 0x5A, 0x42, 0xDA, 0x02, 0xDB, 0x03, 0xDA, 0x5A, 0xD8,
    0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x5A, 0x5B, 0x42, 0x5B, 0x5A, 0x5B, 0x5A, 0x5B,
    0x5A, 0x5A, 0x5A, 0x5A, 0x5B, 0x5A, 0x5B, 0x5A, 0x5A, 0x5B, 0x5B, 0x08, 0x5B, 0x52,
    0x72, 0xC6, 0xD6, 0x08, 0x5A, 0x5A, 0x42, 0x00, 0x00, 0x10, 0x00, 0x02, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x12, 0x10, 0x40, 0x40,
    0x74, 0x0A, 0xDA, 0xC3, 0x12, 0x76, 0x76, 0x5A, 0x5A, 0x5B, 0x42, 0x5B, 0x40, 0x5B,
    0x48, 0x5B, 0x00, 0x5B, 0x5A, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x5A, 0x5B, 0x1B, 0x7B, 0x02, 0x7B,
    0x02, 0x7B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5A, 0x7B, 0x00, 0x7B, 0x00,
    0x7B, 0x0A, 0x5B, 0x5B, 0x5B, 0x5E, 0x5A, 0x5A, 0x4A, 0x72, 0x02, 0x78, 0x00, 0x60,
    0x00, 0x60, 0x00, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x60, 0xF8, 0x68,
    0xFB, 0x7B, 0xFB, 0x7A, 0xFB, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0x7B, 0x7B, 0x7B,
    0x5B, 0x5B, 0x5B, 0x5B, 0x4B, 0x5B, 0x9B, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x02, 0x5E,
    0x42, 0x5B, 0x0B, 0xDB, 0xD8, 0x9B, 0x6B, 0x6B, 0x6B, 0x68, 0x6B, 0x60, 0x7B, 0x00,
    0x7B, 0x02, 0x7B, 0x0B, 0x7B, 0x4B, 0x7B, 0x4B, 0x4B, 0x5B, 0x4B, 0x7B, 0x5B, 0x5B,
    0x5B, 0x5B, 0x5B, 0x7B, 0x7B, 0x7B, 0x7B, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0x7B,
    0x7F, 0x7B, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x5F, 0x5F, 0x5B, 0x5B, 0x7B,
    0x0B, 0x7B, 0x1B, 0xDB, 0x5B, 0x5B, 0x0B, 0x1B, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x12, 0x12, 0x08, 0x0A, 0x0E, 0x08, 0x4B, 0x63,
    0x7B, 0x5B, 0x1B, 0x4B, 0x4B, 0x48, 0x0B, 0x08, 0x4B, 0x4B, 0x4B, 0xCB, 0x49, 0x6B,
    0x60, 0x6B, 0x61, 0x6B, 0x63, 0x6B, 0x63, 0x6B, 0x6B, 0x6B, 0x6B, 0x6B, 0x6B, 0x6B,
    0x6B, 0x43, 0xCB, 0x03, 0xCB, 0x03, 0xCB, 0x08, 0x4B, 0x4B, 0x4B, 0x93, 0x93, 0x0B,
    0x0B, 0x0B, 0x0B, 0x06, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00,
    0x02, 0x00, 0x03, 0x03, 0x01, 0x01, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

typedef struct offset {
    int x;
    int y;
} offset_t;

typedef offset_t ScreenCoord;
void negateImage(uint8_t pixelArray[], uint16_t size) {
    for (int i = 0; i < size; i++) {
        pixelArray[i] = ~pixelArray[i];
    }
}

void shiftImage(offset_t offsetCoord, const uint8_t oldImage[], uint8_t newImage[],
    ScreenCoord coords) {
    // Clear the new image
    for (int i = 0; i < coords.x * (coords.y / 8); i++) {
        newImage[i] = 0;
    }

    // Shift the image based on the offset coordinates
    for (int y = 0; y < coords.y; y++) {
        for (int x = 0; x < coords.x; x++) {
            int newX = x + offsetCoord.x;
            int newY = y + offsetCoord.y;

            // Check if the new coordinates are within bounds
            if (newX >= 0 && newX < coords.x && newY >= 0 && newY < coords.y) {
                int oldByteIndex = (y / 8) * coords.x + x;
                int oldBitIndex = y % 8;
                int newByteIndex = (newY / 8) * coords.x + newX;
                int newBitIndex = newY % 8;

                // Extract the bit from the old image
                uint8_t bit = (oldImage[oldByteIndex] >> oldBitIndex) & 1;

                // Set the bit in the new image
                newImage[newByteIndex] |= (bit << newBitIndex);
            }
        }
    }
}