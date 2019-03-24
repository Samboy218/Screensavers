#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include "cell.h"
#include "faction.h"
#include <X11/Xlib.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <stdio.h>


class Board {
    public:
    Board(int w, int h, int num_fac, int cell_width, int cell_height, XColor* xcolors);
    ~Board();
    bool step(int step_time);
    void init();
    void drawBoard(Display *dpy, Window &root, GC &g);
    void drawBoard(Display *dpy, Window &root, GC &g, int x, int y);
    bool checkDone();
    int getW();
    int getH();

    std::vector<std::vector<Cell> > board;
    std::vector<Faction> factions;
    std::priority_queue<Move, std::vector<Move>, compareMove> moves;
    int w;
    int h;
    int cell_w;
    int cell_h;
    int setCell(int x, int y, int facID, int step_time);
    XColor* colors;
};

#endif
