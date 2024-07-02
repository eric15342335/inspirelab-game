#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

bool is_key_pressed(char key) {
    SHORT result = GetAsyncKeyState((int)key);
    return (result & 0x8000) != 0;
}

int main() {
    char key_to_check = 'A'; // Change this to the key you want to check

    while (1) {
        if (is_key_pressed(key_to_check)) {
            printf("1");
        } else {
            printf("0");
        }
        fflush(stdout); // Ensure the output is immediately printed
        Sleep(1); // Check every 1 millisecond
    }

    return 0;
}