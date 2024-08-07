#pragma once

#include "oled_min.h"

#include <stdbool.h>
#include <stdlib.h>

// OLED commands
#define JOY_OLED_end _OLED_doNothing
#define JOY_OLED_send(b) _OLED_setBuffer(b)
#define JOY_OLED_data_start(y)                                                         \
    {                                                                                  \
        OLED_setpos(0, y);                                                             \
        OLED_data_start();                                                             \
    }


#ifdef _WIN32
#include <windows.h>
#define JOY_init()
#define DLY_ms(milliseconds) Sleep(milliseconds)
#define JOY_sound(freq, dur) Beep(freq, dur)

#define JOY_act_pressed() is_key_pressed('F')
#define JOY_act_released() !is_key_pressed('F')
#define JOY_up_pressed() is_key_pressed('W')
#define JOY_down_pressed() is_key_pressed('S')
#define JOY_left_pressed() is_key_pressed('A')
#define JOY_right_pressed() is_key_pressed('D')

static inline bool is_key_pressed(char capitalkey) {
    SHORT result =
        GetAsyncKeyState((int)capitalkey); // windows.h requires capital letters
    return (result & 0x8000) != 0;
}

#elif defined(__APPLE__)
#include "system_mac.h"
#include <unistd.h>

#define JOY_init() pthread_init()
#define DLY_ms(milliseconds) usleep(milliseconds * 1000)
#define JOY_sound(freq, dur) _beep(freq, dur)

#define JOY_act_pressed() is_key_pressed(F_Key)
#define JOY_act_released() !is_key_pressed(F_Key)
#define JOY_up_pressed() is_key_pressed(W_Key)
#define JOY_down_pressed() is_key_pressed(S_Key)
#define JOY_left_pressed() is_key_pressed(A_Key)
#define JOY_right_pressed() is_key_pressed(D_Key)

#endif

#define JOY_pad_pressed()                                                              \
    (JOY_up_pressed() || JOY_down_pressed() || JOY_left_pressed() || JOY_right_pressed())
#define JOY_pad_released()                                                             \
    (!JOY_up_pressed() && !JOY_down_pressed() && !JOY_left_pressed() && !JOY_right_pressed())
#define JOY_all_released() (JOY_act_released && !JOY_pad_released)

#define JOY_random() rand()
#define JOY_setseed(seed) srand(seed)
#define JOY_setseed_default() srand(0x1234)
