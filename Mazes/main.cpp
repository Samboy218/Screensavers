#include "maze.h"
#include "nodeStack.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "vroot.h"

#define MAZE_WIDTH 30
#define MAZE_HEIGHT 30

enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};

int main(int argc, char** argv) {
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    const char* colors[NUM_COLORS] = {"rgb:1d/1f/21", "rgb:cc/66/66", 
                                    "rgb:b5/bd/68", "rgb:81/a2/be",
                                    "rgb:f0/c6/74", "rgb:b2/94/bb", 
                                    "rgb:8a/be/b7", "rgb:c5/c8/c6"};
    XColor xcolors[NUM_COLORS];
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
    for (int i = 0; i<NUM_COLORS; i++) 
    {
        XAllocNamedColor(dpy, 
                        DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                        colors[i], 
                        &sc, &xc);
        xcolors[i] = sc;
    }
    //set foreground color
    XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));

    int w, h;
    srand(clock());
    int width = (wa.width/16);
    int height = (wa.height/16);
    w = width;
    h = height;
    //printf("Usage: %s <width> <height>\n", argv[0]);
    //exit(1);
    Maze* my_maze = new Maze(w, h);
    my_maze->genMaze();
    valid_colors wallColor = COLOR_MAGENTA;
    valid_colors bgColor = COLOR_BLACK;
    my_maze->drawXMaze(dpy, root, g, xcolors[wallColor], xcolors[bgColor]);
    XFlush(dpy);
}
