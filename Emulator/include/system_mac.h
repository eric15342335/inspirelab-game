#ifndef SYSTEM_MAC_H
#define SYSTEM_MAC_H

#include <stdbool.h>

void _beep(int frequency, int duration);
bool is_key_pressed(char smallkey);

#endif