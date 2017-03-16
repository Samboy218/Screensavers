#include <stdlib.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include "vroot.h"

#define NUMCOLORS 8

int main() {
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;

    char* colors[NUMCOLORS] = {"rgb:00/00/00", "rgb:ff/00/00", "rgb:00/ff/00", 
                                "rgb:00/00/ff", "rgb:ff/ff/00", "rgb:ff/00/ff", 
                                "rgb:00/ff/ff", "rgb:ff/ff/ff"};
    XColor xcolors[NUMCOLORS];
    XColor xc, sc;

    //open display
    dpy = XOpenDisplay(getenv("DISPLAY"));

    //get root window
    root = DefaultRootWindow(dpy);

    //get window attributes
    XGetWindowAttributes(dpy, root, &wa);

    //create a graphical context
    g = XCreateGC(dpy, root, 0, NULL);

    //init colors
    for (int i = 0; i<NUMCOLORS; i++) {
        XAllocNamedColor(dpy, 
                        DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                        colors[i], 
                        &sc, &xc);
        xcolors[i] = sc;
    }

    //set foreground color
    XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));

    //now we can make art
    while(1) {

        int squareWidth = 50;
        int squareHeight = 40;
        int squarePosX = random()%(wa.width - squareWidth);
        int squarePosY = random()%(wa.height - squareHeight);

        //get random color
        XSetForeground(dpy, g, xcolors[random()%NUMCOLORS].pixel);
        
        //write string
        XDrawString(dpy, root, g, random()%(wa.width), random()%(wa.height), "Hello, World!", strlen("Hello, World"));

        //draw rectangle
        XFillRectangle(dpy, root, g, squarePosX, squarePosY, squareWidth, squareHeight);

        if (random()%500 < 1) {
            XClearWindow(dpy, root);
        }

        XFlush(dpy);
        usleep(10000);
    }
}
