#pragma once

#include "oled_min.h"

#include <stdbool.h>
#include <stdlib.h>

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
#define DLY_ms(milliseconds) Sleep(milliseconds)
#define JOY_sound(freq, dur) Beep(freq, dur)

static inline bool is_key_pressed(char smallkey) {
    char capitalkey = smallkey - 32;
    SHORT result =
        GetAsyncKeyState((int)capitalkey); // windows.h requires capital letters
    return (result & 0x8000) != 0;
}

#else
#include "system_mac.h"
#include <unistd.h>

#define JOY_sound(freq, dur) _beep(freq, dur)

static inline void DLY_ms(int milliseconds) {
    usleep(milliseconds * 1000);
}

#endif

#define JOY_act_pressed() is_key_pressed('f')
#define JOY_act_released() !is_key_pressed('f')
#define JOY_up_pressed() is_key_pressed('w')
#define JOY_down_pressed() is_key_pressed('s')
#define JOY_left_pressed() is_key_pressed('a')
#define JOY_right_pressed() is_key_pressed('d')
#define JOY_pad_pressed()                                                              \
    (is_key_pressed('w') || is_key_pressed('s') || is_key_pressed('a') ||              \
        is_key_pressed('d'))
#define JOY_pad_released()                                                             \
    (!is_key_pressed('w') && !is_key_pressed('s') && !is_key_pressed('a') &&           \
        !is_key_pressed('d'))
#define JOY_all_released() (JOY_act_released && !JOY_pad_released)

#define JOY_random() rand()
#define JOY_setseed(seed) srand(seed)
#define JOY_setseed_default() srand(0x1234)
