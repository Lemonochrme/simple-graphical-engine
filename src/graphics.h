
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

extern uint32_t framebuffer[WIN_WIDTH * WIN_HEIGHT];

void put_pixel(int x, int y, uint32_t color);
void draw_char(int x, int y, char c, uint32_t color, int scale);
void draw_string(int x, int y, const char *str, uint32_t color, int scale);
void draw_circle(int xc, int yc, int radius, uint32_t color);

#endif // GRAPHICS_H
