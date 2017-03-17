#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "vroot.h"

// 1/LIFE_CHANCE is the probability a cell will begin with life
#define LIFE_CHANCE 3

// the size, in pixels, of each cell
#define CELL_H 5
#define CELL_W 5
#define SIM_SPEED 30000
#define NEXT_AT 2000

using std::vector;

enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};

bool GOLInitBoard(vector<vector<bool> > &board);
bool step(vector<vector<bool> > &board1, vector<vector<bool> > &board2);
bool drawBoard(Display *dpy, Window &root, GC &g, 
            vector<vector<bool> > board, XColor liveColor);

int main() {
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    srandom(time(NULL));
    char counter[20];
    int generation = 0;

    const char* colors[NUM_COLORS] = {"rgb:00/00/00", "rgb:ff/00/00", 
                                    "rgb:00/ff/00", "rgb:00/00/ff",
                                    "rgb:ff/ff/00", "rgb:ff/00/ff", 
                                    "rgb:00/ff/ff", "rgb:ff/ff/ff"};
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
    for (int i = 0; i<NUM_COLORS; i++) {
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

    vector<vector<bool> > buf1;
    vector<vector<bool> > buf2;
    buf1.resize(gridW + 2);
    buf2.resize(gridW + 2);

    for (int i = 0; i< gridW + 2; i++) {
        buf1[i].resize(gridH + 2);
        buf2[i].resize(gridH + 2);
    }

    int liveColor = (random()%(NUM_COLORS-1)) + 1; 

    GOLInitBoard(buf1);

    while(1) {
        drawBoard(dpy, root, g, buf1, xcolors[liveColor]);
        sprintf(counter, "Generation: %d", generation);
        XSetForeground(dpy, g, xcolors[liveColor].pixel);
        XDrawString(dpy, root, g, 50, 50, counter, strlen(counter));
        generation++;
        XFlush(dpy);
        step(buf1, buf2);
        usleep(SIM_SPEED);

        drawBoard(dpy, root, g, buf2, xcolors[liveColor]);
        sprintf(counter, "Generation: %d", generation);
        XSetForeground(dpy, g, xcolors[liveColor].pixel);
        XDrawString(dpy, root, g, 50, 50, counter, strlen(counter));
        generation++;
        XFlush(dpy);
        step(buf2, buf1);
        usleep(SIM_SPEED);

        if (generation >= NEXT_AT) {
            GOLInitBoard(buf1);
            generation = 0;
            liveColor = (random()%(NUM_COLORS-1)) + 1; 
        }
    }


}

bool GOLInitBoard(vector<vector<bool> > &board) {
    for (int x = 0; x < board.size(); x++) {
        for (int y = 0; y < board[x].size(); y++) {
            //the outside is a buffer area of always 0, for no wrapping
            if (x == 0 || y == 0 
                || x == board.size() - 1 
                || y == board[x].size() - 1) {
                board[x][y] = 0;
            }
            else if (random()%LIFE_CHANCE == 0)
                board[x][y] = 1;
            else
                board[x][y] = 0;
        }
    }
    return true;
}

bool step(vector<vector<bool> > &board1, vector<vector<bool> > &board2) {
    int live = 0;

    for (int x = 0; x < board1.size(); x++) {
        for (int y = 0; y < board1[x].size(); y++) {
             
            //again, keep that outer buffer at 0
            if (x == 0 || y == 0 
            || x == board1.size() - 1 
            || y == board1[x].size() - 1) {
               board2[x][y] = 0;
               continue;
            }

            live = board1[x-1][y-1] + board1[x-1][y] + board1[x-1][y+1] +
                board1[x+1][y-1] + board1[x+1][y] + board1[x+1][y+1] +
                board1[x][y-1] + board1[x][y+1] ;

            if (board1[x][y] == 1) {
                switch (live) {
                    case 2:
                    case 3:
                    board2[x][y] = 1;
                    break;

                    default:
                    board2[x][y] = 0;
                }
            }
            else if (live == 3) {
                board2[x][y] = 1;
            }
            else {
                board2[x][y] = 0;
            }
        }
    }
    return true;
}

bool drawBoard(Display *dpy, Window &root, GC &g, 
            vector<vector<bool> > board, XColor liveColor) {

    for (int x = 0; x < board.size(); x++) {
        for (int y = 0; y < board[x].size(); y++) {

            if (x == 0 || y == 0 
            || x == board.size() - 1 || y == board[x].size() - 1) {
                continue;
            }

            if (board[x][y] == 1) {
                XSetForeground(dpy, g, liveColor.pixel);
            }

            else {
                XSetForeground(dpy, g, 
                        BlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
            }

            XFillRectangle(dpy, root, g, x*CELL_W, y*CELL_H, CELL_W, CELL_W);
        }
    }
}
