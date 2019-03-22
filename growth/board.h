#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "faction.h"

class Board {
    public:
    Board(int w, int h);
    ~Board();
    void step();
    void init();
    void drawBoard(Display *dpy, Window &root, GC &g, XColor liveColor, XColor deadColor);
    int getW();
    int getH();


    private:
    Cell* board;
    Faction* factions;
    int w;
    int h;
};

#endif
