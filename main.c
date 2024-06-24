#include "driver.h"
int main() {
    JOY_init();
    OLED_init();
    OLED_fill(0xF0);
}
