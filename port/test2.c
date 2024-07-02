#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

bool is_key_pressed(char key) {
    int ch;

    timeout(0); // Non-blocking getch
    while ((ch = getch()) != ERR) {
        if (ch == key) {
            return true;
        }
    }
    return false;
}

int main() {
    char key_to_check = 'a'; // Change this to the key you want to check

    initscr(); // Initialize the ncurses screen
    raw(); // Line buffering disabled
    keypad(stdscr, TRUE); // Enable function keys
    noecho(); // Don't echo while we do getch

    while (1) {
        if (is_key_pressed(key_to_check)) {
            printf("1");
        } else {
            printf("0");
        }
        fflush(stdout); // Ensure the output is immediately printed
        usleep(500000); // Check every 1 millisecond
    }

    endwin(); // End the ncurses mode
    return 0;
}