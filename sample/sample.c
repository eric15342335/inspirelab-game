#include "driver.h"
#include <stdint.h>
#define SCREEN_X 128
#define SCREEN_Y 64
#define AXIS_Y_STORAGE 8
#define BUFFER_SIZE SCREEN_X * SCREEN_Y / AXIS_Y_STORAGE

uint8_t displayBuffer[BUFFER_SIZE];

void display(void) {
    // x horizontal y vertical
    uint8_t y, x;
    for (y = 0; y < 8; y++) {
        JOY_OLED_data_start(y);
        for (x = 0; x < 128; x++) {
            JOY_OLED_send(displayBuffer[y * 128 + x]);
        }
        JOY_OLED_end();
    }
    _OLED_refresh_display();
}

void clearBuffer() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        displayBuffer[i] = 0;
    }
}

inline void setPixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < SCREEN_X && y >= 0 && y < SCREEN_Y) {
        if (color) {
            displayBuffer[(y / 8) * SCREEN_X + x] |= (1 << (y % 8));
        } else {
            displayBuffer[(y / 8) * SCREEN_X + x] &= ~(1 << (y % 8));
        }
    }
}


static inline int FastMultiply( uint32_t big_num, uint32_t small_num ) __attribute__((section(".data")));
static inline int FastMultiply( uint32_t big_num, uint32_t small_num )
{
	int ret = 0;
	uint32_t multiplicand = small_num;
	uint32_t mutliplicant = big_num;
	do
	{
		if( multiplicand & 1 )
			ret += mutliplicant;
		mutliplicant<<=1;
		multiplicand>>=1;
	} while( multiplicand );
	return ret;
}
#define R(mul, shift, x, y) \
    _ = (x); \
    (x) -= FastMultiply((mul), (y)) >> (shift); \
    (y) += FastMultiply((mul), _) >> (shift); \
    _ = (3145728 - FastMultiply((x), (x)) - FastMultiply((y), (y))) >> 11; \
    (x) = FastMultiply((x), _) >> 10; \
    (y) = FastMultiply((y), _) >> 10;

void drawDonut(int frame) {
    int sA = 1024, cA = 0, sB = 1024, cB = 0, _;
    clearBuffer();

    // Adjust rotation angles based on frame
    for (int i = 0; i < frame; i++) {
        R(5, 7, cA, sA);
        R(5, 8, cB, sB);
    }

    int sj = 0, cj = 1024;
    for (int j = 0; j < 1; j++) { // original 90
        int si = 0, ci = 1024;  // sine and cosine of angle i
        for (int i = 0; i < 324; i++) { // original 324
            int R1 = 2, R2 = 4096, K2 = FastMultiply(10240, 1024);  // Adjusted for larger donut
            int x0 = FastMultiply(R1, cj) + R2,
                x1 = FastMultiply(ci, x0) >> 10,
                x2 = FastMultiply(cA, sj) >> 10,
                x3 = FastMultiply(si, x0) >> 10,
                x4 = FastMultiply(R1, x2) - (FastMultiply(sA, x3) >> 10),
                x5 = FastMultiply(sA, sj) >> 10,
                x6 = K2 + FastMultiply(R1, 1024 * x5) + FastMultiply(cA, x3),
                x = SCREEN_X / 2 + (SCREEN_X / 2) * (FastMultiply(cB, x1) - FastMultiply(sB, x4)) / x6,
                y = SCREEN_Y / 2 + (SCREEN_Y / 2) * (FastMultiply(cB, x4) + FastMultiply(sB, x1)) / x6;

            if (SCREEN_Y > y && y > 0 && x > 0 && SCREEN_X > x) {
                setPixel(x, y, 1); // Set pixel without light contrast
            }
            R(5, 8, ci, si);  // rotate i
        }
        R(9, 7, cj, sj);  // rotate j
    }
}

int main() {
    JOY_init();
    OLED_println("Hello, World!");
    DLY_ms(100);
    OLED_clear();
    int frame = 0;

    while (1) {
        drawDonut(frame);
        display();
        frame += 4;
        if (frame >= 1024) {
            frame = 0;
        }
        //DLY_ms(1);
        _OLED_refresh_display(); // Refresh the display
    }

    return 0;
}