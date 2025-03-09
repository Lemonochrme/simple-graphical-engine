#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void draw_pixel(Display *display, Window window, GC gc, int x, int y) {
    XDrawPoint(display, window, gc, x, y);
}

void draw_line(Display *display, Window window, GC gc, int x1, int y1, int x2, int y2) {
    XDrawLine(display, window, gc, x1, y1, x2, y2);
}

void draw_rectangle(Display *display, Window window, GC gc, int x, int y, int width, int height) {
    XDrawRectangle(display, window, gc, x, y, width, height);
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
    
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            draw_pixel(display, window, gc, 400, 300);
            draw_line(display, window, gc, 100, 100, 700, 500);
            draw_rectangle(display, window, gc, 200, 200, 400, 200);
        }
        if (event.type == KeyPress)
            break;
    }
    
    XCloseDisplay(display);
    return 0;
}
