//#include "nodeStack.h"
#include "mazeSolverA.h"
#include "mazeSolverDFS.h"
#include "mazeSolverBFS.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "vroot.h"

#define MAZE_WIDTH 30
#define MAZE_HEIGHT 30
#define FPS_RUN 60

enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};

int main(int argc, char** argv) {
    srand(clock());
    Display* dpy;
    Window root;
    GC g;
    Pixmap double_buffer_1;
    Pixmap double_buffer_2;
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
    double_buffer_1 = XCreatePixmap(dpy, root, wa.width/2, wa.height, wa.depth);
    double_buffer_2 = XCreatePixmap(dpy, root, wa.width/2, wa.height, wa.depth);
    //init colors
    for (int i = 0; i<NUM_COLORS; i++) 
    {
        XAllocNamedColor(dpy, 
                        DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                        colors[i], 
                        &sc, &xc);
        xcolors[i] = sc;
    }

    XColor draw_colors[5];
    draw_colors[0] = xcolors[COLOR_BLACK];
    draw_colors[1] = xcolors[COLOR_RED];
    draw_colors[2] = xcolors[COLOR_YELLOW];
    draw_colors[3] = xcolors[COLOR_BLUE];
    draw_colors[4] = xcolors[COLOR_GREEN];


    //set foreground color
    XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));

    int w, h;
    srand(clock());
    int width = (wa.width/32);
    int height = (wa.height/16);
    w = width;
    h = height;
    Maze* my_maze = new Maze(w, h, wa.width/2, wa.height);
    my_maze->genMaze();

    Maze* maze_1 = new Maze(my_maze);
    MazeSolver* solver_1;

    Maze* maze_2 = new Maze(my_maze);
    MazeSolver* solver_2;
    switch (rand()%3) {
        case 0:
            solver_1 = new MazeSolverA(maze_1);
            if (rand()%2) 
                solver_2 = new MazeSolverBFS(maze_2);
            else
                solver_2 = new MazeSolverDFS(maze_2);
        break;
        case 1:
            solver_1 = new MazeSolverBFS(maze_1);
            if (rand()%2) 
                solver_2 = new MazeSolverA(maze_2);
            else
                solver_2 = new MazeSolverDFS(maze_2);

        break;
        case 2:
            solver_1 = new MazeSolverDFS(maze_1);
            if (rand()%2) 
                solver_2 = new MazeSolverBFS(maze_2);
            else
                solver_2 = new MazeSolverA(maze_2);

        break;
    }

    int time_wait = CLOCKS_PER_SEC/FPS_RUN;
    clock_t now;
    clock_t previous = clock();
    while (true) {
        maze_1->drawXMaze(dpy, double_buffer_1, g, draw_colors);
        maze_2->drawXMaze(dpy, double_buffer_2, g, draw_colors);
        while (!(solver_1->takeStep() & solver_2->takeStep())) {
            now = clock();
            if ((now - previous) < time_wait) {
                usleep(time_wait - (now - previous));
            }
            previous = now;

            maze_1->drawXMazeNode(dpy, double_buffer_1, g, draw_colors, solver_1->redraw);
            maze_2->drawXMazeNode(dpy, double_buffer_2, g, draw_colors, solver_2->redraw);
            XCopyArea(dpy, double_buffer_1, root, g, 0, 0, wa.width/2, wa.height, 0, 0);
            XCopyArea(dpy, double_buffer_2, root, g, 0, 0, wa.width/2, wa.height, wa.width/2, 0);
            XFlush(dpy);
        }
        maze_1->drawXMaze(dpy, double_buffer_1, g, draw_colors);
        maze_2->drawXMaze(dpy, double_buffer_2, g, draw_colors);
        XCopyArea(dpy, double_buffer_1, root, g, 0, 0, wa.width/2, wa.height, 0, 0);
        XCopyArea(dpy, double_buffer_2, root, g, 0, 0, wa.width/2, wa.height, wa.width/2, 0);
        XFlush(dpy);

        delete solver_1;
        delete solver_2;
        delete my_maze;
        delete maze_1;
        delete maze_2;
        my_maze = new Maze(w, h, wa.width/2, wa.height);
        my_maze->genMaze();
        maze_1 = new Maze(my_maze);
        maze_2 = new Maze(my_maze);
        switch (rand()%3) {
            case 0:
                solver_1 = new MazeSolverA(maze_1);
                if (rand()%2) 
                    solver_2 = new MazeSolverBFS(maze_2);
                else
                    solver_2 = new MazeSolverDFS(maze_2);
            break;
            case 1:
                solver_1 = new MazeSolverBFS(maze_1);
                if (rand()%2) 
                    solver_2 = new MazeSolverA(maze_2);
                else
                    solver_2 = new MazeSolverDFS(maze_2);

            break;
            case 2:
                solver_1 = new MazeSolverDFS(maze_1);
                if (rand()%2) 
                    solver_2 = new MazeSolverBFS(maze_2);
                else
                    solver_2 = new MazeSolverA(maze_2);

            break;
        }

        sleep(3);
    }
    return 5;
}
