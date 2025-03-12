#include "graphics.h"
#include "font.h"
#include <string.h>

uint32_t framebuffer[WIN_WIDTH * WIN_HEIGHT];

void put_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
        framebuffer[y * WIN_WIDTH + x] = color;
    }
}

void draw_char(int x, int y, char c, uint32_t color, int scale) {
    int index = c - 'A';

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (font[index][i] & (0b10000000 >> j)) {
                for (int k = 0; k < scale; k++) {
                    for (int l = 0; l < scale; l++) {
                        put_pixel(x + (j * scale) + k, y + (i * scale) + l, color);
                    }
                }
            }
        }
    }
}

void draw_string(int x, int y, const char *str, uint32_t color, int scale) {
    int char_width = 8 * scale + 10;
    while (*str) {
        if (*str == ' ') {
            x += char_width;
        } else {
            draw_char(x, y, *str, color, scale);
            x += char_width;
        }
        str++;
    }
}

void draw_circle(int xc, int yc, int radius, uint32_t color) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        put_pixel(xc + x, yc + y, color);
        put_pixel(xc - x, yc + y, color);
        put_pixel(xc + x, yc - y, color);
        put_pixel(xc - x, yc - y, color);
        put_pixel(xc + y, yc + x, color);
        put_pixel(xc - y, yc + x, color);
        put_pixel(xc + y, yc - x, color);
        put_pixel(xc - y, yc - x, color);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}
