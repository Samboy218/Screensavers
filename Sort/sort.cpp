#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include "vroot.h"

/*
sorting methods to implement:
Merge depth/breadth first
Heap sift up/down
radix  MSD/LSD
bitonic
cocktail
insertion
shell
comb
quick
bogosort (maybe dont have that one appear too often)
*/


#define CELL_HEIGHT 15
#define CELL_WIDTH 15
#define NUM_FACTION 7

//the speed to run at (FPS)
#define FPS_RUN 60

//for this simulation we'll need to define a bunch more colors
enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};



int main() 
{
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    srand(time(NULL));
    char counter[20];
    int generation = 0;

    const char* colors[NUM_COLORS] = {"rgb:1d/1f/21", "rgb:ac/46/46", 
                                    "rgb:95/9d/48", "rgb:61/82/9e",
                                    "rgb:d0/a6/54", "rgb:92/74/9b", 
                                    "rgb:6a/9e/97", "rgb:a5/a8/a6"};
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

    //now we can make art
    int gridW = wa.width/CELL_WIDTH;
    int gridH = wa.height/CELL_HEIGHT;

    int timeWait = CLOCKS_PER_SEC / FPS_RUN;
    clock_t now;
    clock_t previous = clock();
    while(1)
    {
        now = clock();
        if ((now - previous) < timeWait)
        {
            //printf("had to wait %d us at gen %d\n", timeWait-(now-previous), generation);
            usleep(timeWait - (now - previous));
        }
        previous = now;

        //process moves until we are done with this time step



        XFlush(dpy);
    }
    return 0;
}

 
