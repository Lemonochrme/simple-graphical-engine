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

    for (int i = 0; i < 8; i++) {  // Iterate over rows
        for (int j = 0; j < 8; j++) {  // Iterate over columns
            if (font8x8_basic[(int)c][i] & (1 << j)) {  // Flip bit reading order
                for (int k = 0; k < scale; k++) {
                    for (int l = 0; l < scale; l++) {
                        put_pixel(x + j * scale + k, y + i * scale + l, color); // Flip X position
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

void draw_rectangle(int x, int y, int width, int height, uint32_t color) { 
    for (int i = 0; i < width; i++) {
        put_pixel(x + i, y, color);
        put_pixel(x + i, y + height - 1,  color);
    }
    for (int i = 0; i < height; i++) {
        put_pixel(x, y + i, color);
        put_pixel(x + width - 1, y + i, color);
    }
}