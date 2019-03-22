#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include "vroot.h"

//have some number of competing blobs of growth
//each blob is a different color
//each blob has different characteristics
//  speed, strength, accuracy, health
//each cell in the blob can attack and has HP
//when a cell is killed, it is converted
//when the board is all one color, restart

// the size, in pixels, of each cell
#define CELL_H 5
#define CELL_W 5

//the speed to run at (FPS)
#define FPS_RUN 30

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

    //now we can make art
    //init GOL
    int gridW = wa.width/CELL_W;
    int gridH = wa.height/CELL_H;
    //printf("w: %d, h: %d\n", wa.width, wa.height);


    int liveColor = (rand()%(NUM_COLORS-1)) + 1; 

    Board board(gridW, gridH);
    board.init(LIFE_CHANCE);

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

        //draw a generation
        board.drawBoard(dpy, root, g, xcolors[liveColor], xcolors[0]);
        sprintf(counter, "Generation: %d", generation);
        //XSetForeground(dpy, g, xcolors[liveColor].pixel);
        //XDrawString(dpy, root, g, 50, 50, counter, strlen(counter));
        generation++;
        XFlush(dpy);
        board.step();

        if (generation >= NEXT_AT) 
        {
            board.init(LIFE_CHANCE);
            generation = 0;
            liveColor = (rand()%(NUM_COLORS-1)) + 1; 
        }
    }
}

 
