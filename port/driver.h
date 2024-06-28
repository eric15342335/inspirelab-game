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
#include <time.h>
void DLY_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
static inline void JOY_sound(int frequency, int duration_ms) {
} //beenping sound is not achievable in macos

#endif

// Platform-specific includes and JOY_sound function
