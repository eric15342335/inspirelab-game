#ifndef DRIVER_H
#define DRIVER_H

#include "oled_min.h"

#include <time.h>

// OLED commands
#define JOY_init OLED_init
#define JOY_OLED_end _OLED_doNothing
#define JOY_OLED_send(b) _OLED_setBuffer(b)
#define JOY_OLED_data_start(y)                                                         \
    {                                                                                  \
        OLED_setpos(0, y);                                                             \
        OLED_data_start();                                                             \
    }

#ifdef _WIN32
#include <windows.h>
static inline void DLY_ms(int milliseconds) { 
    Sleep(milliseconds); 
}
static inline void JOY_sound(int frequency, int duration_ms) {
    Beep(frequency, duration_ms);
}

#else
#include <unistd.h>
void DLY_ms(int milliseconds) {
    usleep(milliseconds * 1000);
}
static inline void JOY_sound(int frequency, int duration_ms) {
} //beenping sound is not achievable in macos

#endif

#endif