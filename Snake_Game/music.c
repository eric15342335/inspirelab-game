#include "music.h"

#include "driver.h"
#include "image.c"

void playAllMusic(void) {
    // sizeof gives the number of bytes, each int value is
    // composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note
    // there are four bytes
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    playMusic((noterange_t){0, notes});
}

void playMusic(noterange_t range) {
    // change this to make the song slower or faster
    int tempo = 150;
    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = range.start*2; thisNote < range.end * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
        #if DEBUG == 1
            OLED_print("note=");
            OLED_printD(melody[thisNote]);
            OLED_print(", dur=");
            OLED_printD(noteDuration);
            OLED_println("");
        #endif
        JOY_sound(melody[thisNote], noteDuration);
    }
}

void playNotes() {
    for (uint8_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
        JOY_sound(notes[i].frequency, 10);
    }
}

void display(const uint8_t pixelArray[], uint16_t size) {
    // OLED_fill(0x00);
    uint8_t y, x;
    for (y = 0; y < 8; y++) {
        JOY_OLED_data_start(y);
        for (x = 0; x < size / 8; x++) {
            JOY_OLED_send(pixelArray[y * 128 + x]);
        }
        JOY_OLED_end();
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
uint8_t image_data_copy[1024];

int main() {
    JOY_init();
    OLED_fill(0x00);
    // copy the image data to a new array
    for (int i = 0; i < 1024; i++) {
        image_data_copy[i] = image_data[i];
    }
    display(image_data_copy, 1024);
    DLY_ms(500);

    for (int i = 0; i < 13; i += 4) {
        for (int j = i; j < i + 6; j++) {
            display(image_data_copy, 1024);
            shiftImage((offset_t){j, j % 6 - 3}, image_data, image_data_copy,
                (ScreenCoord){128, 64});
        }
        // negateImage(image_data_copy, 1024);
        // JOY_sound(i * 20 + 200, 15);
        playMusic((noterange_t){i % 13, i % 13 + 4});
    }
    /*for (int i = 0; i < 13*5; i++) {
        display(image_data_copy, 1024);
        shiftImage((offset_t){i, i % 6 - 3}, image_data, image_data_copy,
            (ScreenCoord){128, 64});
        // negateImage(image_data_copy, 1024);
        //JOY_sound(i * 20 + 200, 15);
    }*/
    

    for (int i = 64; i >= 0; i--) {
        display(image_data_copy, 1024);
        shiftImage((offset_t){-i, i % 6 - 3}, image_data, image_data_copy,
            (ScreenCoord){128, 64});
        // negateImage(image_data_copy, 1024);
        //JOY_sound(i * 20 + 200, 15);
    }
    OLED_fill(0x00);
    OLED_println("Press the right button to start the game");
    DLY_ms(1000);
    rnval = 0xACE1;
    while (!JOY_act_pressed()) {
        if (rnval > 0xFFF0) {
            rnval = 0xACE1;
        }
        rnval += 1;
        DLY_ms(10);
    }
    for (int i = 0; i < 100; i++) {
        OLED_printD(JOY_random());
        OLED_println("");
        DLY_ms(1000);
    }
    while (!JOY_act_pressed()) {
    }
    OLED_fill(0x00);
    // start the game
    playAllMusic();
}
