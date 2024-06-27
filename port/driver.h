#ifndef DRIVER_H
#define DRIVER_H

#include "oled_min.h"

// OLED commands
#define JOY_init OLED_init
#define JOY_OLED_end _OLED_doNothing
#define JOY_OLED_send(b) _OLED_setBuffer(b)
#define JOY_OLED_data_start(y)                                                         \
    {                                                                                  \
        OLED_setpos(0, y);                                                             \
        OLED_data_start();                                                             \
    }

#endif // DRIVER_H
