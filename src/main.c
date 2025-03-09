#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

unsigned int framebuffer[WIN_WIDTH * WIN_HEIGHT];

void put_pixel(int x, int y, unsigned int color) {
    if (x >= 0 && x < WIN_WIDTH && y>= 0 && y < WIN_HEIGHT) {
        framebuffer[y * WIN_WIDTH + x] = color;
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
    memset(framebuffer, 000, sizeof(framebuffer)); 

    // draw horizontal line in white
    for (int i = 0; i < 500; i++) {
        put_pixel(100 + i, 100 + i, 0xFFFFFF);
    }

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
