#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include "vroot.h"

#include "sortManager.h"
#include "bubbleSort.h"
#include "cocktailSort.h"
#include "insertionSort.h"

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

//the speed to run at (FPS)
#define FPS_RUN 60



int main() 
{
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    srand(time(NULL));
    char counter[20];
    int generation = 0;

    const char* colors[100] = {"rgb:fd/e7/25", "rgb:f8/e6/21", "rgb:f1/e5/1d", "rgb:ec/e5/1b", "rgb:e5/e4/19", "rgb:df/e3/18", "rgb:d8/e2/19", 
                               "rgb:d0/e1/1c", "rgb:ca/e1/1f", "rgb:c2/df/23", "rgb:bd/df/26", "rgb:b5/de/2b", "rgb:ad/dc/30", "rgb:a8/db/34", 
                               "rgb:a0/da/39", "rgb:9b/d9/3c", "rgb:93/d7/41", "rgb:8e/d6/45", "rgb:86/d5/49", "rgb:7f/d3/4e", "rgb:7a/d1/51", 
                               "rgb:73/d0/56", "rgb:6e/ce/58", "rgb:67/cc/5c", "rgb:60/ca/60", "rgb:5c/c8/63", "rgb:56/c6/67", "rgb:52/c5/69", 
                               "rgb:4c/c2/6c", "rgb:48/c1/6e", "rgb:42/be/71", "rgb:3d/bc/74", "rgb:3a/ba/76", "rgb:35/b7/79", "rgb:32/b6/7a", 
                               "rgb:2e/b3/7c", "rgb:2a/b0/7f", "rgb:28/ae/80", "rgb:25/ac/82", "rgb:24/aa/83", "rgb:22/a7/85", "rgb:20/a4/86", 
                               "rgb:1f/a2/87", "rgb:1f/a0/88", "rgb:1f/9e/89", "rgb:1e/9b/8a", "rgb:1f/99/8a", "rgb:1f/96/8b", "rgb:20/93/8c", 
                               "rgb:20/92/8c", "rgb:21/8f/8d", "rgb:22/8d/8d", "rgb:23/8a/8d", "rgb:24/87/8e", "rgb:25/85/8e", "rgb:26/82/8e", 
                               "rgb:26/81/8e", "rgb:27/7e/8e", "rgb:28/7c/8e", "rgb:29/79/8e", "rgb:2a/76/8e", "rgb:2b/74/8e", "rgb:2c/71/8e",
                               "rgb:2d/70/8e", "rgb:2e/6d/8e", "rgb:30/6a/8e", "rgb:31/68/8e", "rgb:32/65/8e", "rgb:33/63/8d", "rgb:34/60/8d", 
                               "rgb:36/5d/8d", "rgb:37/5b/8d", "rgb:38/58/8c", "rgb:39/55/8c", "rgb:3b/52/8b", "rgb:3c/50/8b", "rgb:3d/4d/8a", 
                               "rgb:3e/49/89", "rgb:3f/47/88", "rgb:41/44/87", "rgb:42/41/86", "rgb:43/3e/85", "rgb:44/3a/83", "rgb:45/38/82", 
                               "rgb:46/34/80", "rgb:46/32/7e", "rgb:47/2e/7c", "rgb:47/2c/7a", "rgb:48/28/78", "rgb:48/24/75", "rgb:48/21/73",
                               "rgb:48/1d/6f", "rgb:48/1b/6d", "rgb:48/17/69", "rgb:47/13/65", "rgb:47/10/63", "rgb:46/0b/5e", "rgb:46/08/5c",
                               "rgb:45/04/57", "rgb:44/01/54"};
    XColor xcolors[100];
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
    for (int i = 0; i<100; i++) 
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
    //try to make cells square
    int cellSize = wa.height/100;
    int numArrays = wa.width/cellSize;
    SortManager manager = SortManager(numArrays, wa.width, wa.height);
    for (int i = 0; i < numArrays; i++) {
        if (i < numArrays/3)
            manager.setSorter(i, new CocktailSort());
        else if (i < numArrays*2/3) 
            manager.setSorter(i, new InsertionSort());
        else
            manager.setSorter(i, new BubbleSort());
    }
    manager.shuffleAll();
    manager.drawAll(dpy, root, g, xcolors);

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
        //printf("doing step\n");

        //process moves until we are done with this time step
        if (manager.stepAll()) {
            sleep(1);
            manager.shuffleAll();
            manager.drawAll(dpy, root, g, xcolors);
        }
        else {
            manager.drawArrays(dpy, root, g, xcolors);
        }

        XFlush(dpy);
    }
    return 0;
}

 
