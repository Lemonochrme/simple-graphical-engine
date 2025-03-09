#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "font.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

unsigned int framebuffer[WIN_WIDTH * WIN_HEIGHT];

void put_pixel(int x, int y, unsigned int color) {
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
        framebuffer[y * WIN_WIDTH + x] = color;
    }
}

void draw_char(int x, int y, char c, unsigned int color) {
    int index = c - 'A'; 

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (font[index][i] & (0b10000000 >> j)) {
                put_pixel(x + j, y + i, color);
            }
        }
    }
}

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, WIN_WIDTH, WIN_HEIGHT, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, gc, BlackPixel(display, screen));

    // Stocking the framebuffer
    XImage *image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, (char*) framebuffer, WIN_WIDTH, WIN_HEIGHT, 32, 0);

    // fill framebuffer with black background color
    memset(framebuffer, 0, sizeof(framebuffer));

    draw_char(1280/2, 720/2 - 100, 'H', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 90, 'E', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 80, 'L', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 70, 'L', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 60, 'L', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 50, 'O', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 30, 'W', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 20, 'O', 0xFFFFFF);
    draw_char(1280/2, 720/2 - 10, 'R', 0xFFFFFF);
    draw_char(1280/2, 720/2, 'L', 0xFFFFFF);
    draw_char(1280/2, 720/2 + 10, 'D', 0xFFFFFF);

    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XPutImage(display, window, gc, image, 0, 0, 0, 0, WIN_WIDTH, WIN_HEIGHT);
        }
        if (event.type == KeyPress)
            break;
    }

    XCloseDisplay(display);
    return 0;
}
