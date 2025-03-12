#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "graphics.h"

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

    XImage *image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen),
                                 ZPixmap, 0, (char*) framebuffer, WIN_WIDTH, WIN_HEIGHT, 32, 0);

    memset(framebuffer, 0, sizeof(framebuffer));

    draw_string(20, 20, "Hello, World !", 0xFFFFFF, 3);

    // Rosace
    draw_circle(640, 360, 100, 0xFFFFFF); 
    draw_circle(740, 360, 100, 0xFFFFFF); 
    draw_circle(540, 360, 100, 0xFFFFFF); 
    draw_circle(690, 443, 100, 0xFFFFFF); 
    draw_circle(590, 443, 100, 0xFFFFFF); 
    draw_circle(690, 277, 100, 0xFFFFFF); 
    draw_circle(590, 277, 100, 0xFFFFFF); 

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
