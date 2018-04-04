//#include "nodeStack.h"
#include "mazeSolverA.h"
#include "mazeSolverDFS.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "vroot.h"

#define MAZE_WIDTH 30
#define MAZE_HEIGHT 30
#define FPS_RUN 30

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
    Pixmap double_buffer;
    XWindowAttributes wa;
    //const char* colors[NUM_COLORS] = {"rgb:1d/1f/21", "rgb:cc/66/66", 
    //                                "rgb:b5/bd/68", "rgb:81/a2/be",
    //                                "rgb:f0/c6/74", "rgb:b2/94/bb", 
    //                                "rgb:8a/be/b7", "rgb:c5/c8/c6"};

     const char* colors[NUM_COLORS] = {"rgb:11/11/11", "rgb:cc/33/33", 
                                    "rgb:33/cc/33", "rgb:33/33/cc",
                                    "rgb:cc/cc/33", "rgb:b2/94/bb", 
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
    double_buffer = XCreatePixmap(dpy, root, wa.width, wa.height, wa.depth);
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
    Maze* my_maze = new Maze(w, h, wa.width, wa.height);
    my_maze->genMaze();
    valid_colors wallColor = COLOR_MAGENTA;
    valid_colors bgColor = COLOR_BLACK;
    XColor draw_colors[5];
    draw_colors[0] = xcolors[COLOR_BLACK];
    draw_colors[1] = xcolors[COLOR_RED];
    draw_colors[2] = xcolors[COLOR_YELLOW];
    draw_colors[3] = xcolors[COLOR_BLUE];
    draw_colors[4] = xcolors[COLOR_GREEN];
    //MazeSolver* solver = new MazeSolver(my_maze);
    //MazeSolverA* solver = new MazeSolverA(my_maze);
    MazeSolver* solver;
    solver = new MazeSolverDFS(my_maze);
    my_maze->drawXMaze(dpy, root, g, draw_colors);
    XFlush(dpy);
    int time_wait = CLOCKS_PER_SEC/FPS_RUN;
    clock_t now;
    clock_t previous = clock();
    while (true) {
        while (!solver->takeStep()) {
            now = clock();
            if ((now - previous) < time_wait) {
                usleep(time_wait - (now - previous));
            }
            previous = now;

            my_maze->drawXMaze(dpy, double_buffer, g, draw_colors);
            //XFlush(dpy);
            XCopyArea(dpy, double_buffer, root, g, 0, 0, wa.width, wa.height, 0, 0);
            XFlush(dpy);
        }
        my_maze->drawXMaze(dpy, double_buffer, g, draw_colors);
        XCopyArea(dpy, double_buffer, root, g, 0, 0, wa.width, wa.height, 0, 0);
        XFlush(dpy);

        delete solver;
        delete my_maze;
        my_maze = new Maze(w, h, wa.width, wa.height);
        my_maze->genMaze();
        solver = new MazeSolverA(my_maze);
        sleep(3);
    }
    return 5;
}
