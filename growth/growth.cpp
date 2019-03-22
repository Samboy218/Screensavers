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

class Board
{
    public:
    Board(int w, int h);
    ~Board();
    void step();
    void init();
    void drawBoard(Display *dpy, Window &root, GC &g, 
                   XColor liveColor, XColor deadColor);
    int getW();
    int getH();


    private:
    unsigned char* board;
    int w;
    int h;
};

int main() 
{
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    srandom(time(NULL));
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


    int liveColor = (random()%(NUM_COLORS-1)) + 1; 

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
            liveColor = (random()%(NUM_COLORS-1)) + 1; 
        }
    }
}

 

Board::Board(int x, int y)
{
    w = x;
    h = y;
    lengthB = w*h;
    board = new unsigned char[lengthB];
    tempBoard = new unsigned char[lengthB];    
    memset(board, 0, lengthB);
    memset(tempBoard, 0, lengthB);
}

Board::~Board()
{
    delete[] board;
    board = NULL;
    delete[] tempBoard;
    tempBoard = NULL;
}

void Board::init(int aliveChance)
{
    //init the board randomly according to the defined frequency
    //probability is 1/aliveChance
    unsigned char* cellPtr;
    cellPtr = board;
    memset(board, 0, lengthB);
    memset(tempBoard, 0, lengthB);
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (random()%aliveChance == 0)
            {
                setCell(x, y);
            }
        }
    }

}

void Board::drawBoard(Display *dpy, Window &root, GC &g, 
                         XColor liveColor, XColor deadColor)
{
    unsigned char* cellPtr;
    cellPtr = board;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if ((*cellPtr) & 0x01)
            {
                XSetForeground(dpy, g, liveColor.pixel);
            }
            else
            {
                XSetForeground(dpy, g, deadColor.pixel);
            }
            cellPtr++;
            XFillRectangle(dpy, root, g, x*CELL_W, y*CELL_H, CELL_W, CELL_H);
        }
    }
}

void Board::step()
{
    unsigned int x, y, count;
    unsigned char*  cellPtr;

    memcpy(tempBoard, board, lengthB);

    cellPtr = tempBoard;

    for (y = 0; y < h; y++)
    {
nextRow:
        x = 0;
        while (x < w)
        {
            while (cellPtr == 0)
            {
                cellPtr++;
                x++;
                if (x >=w)
                    goto nextRow;
                    //wow, the only valid use for goto in c++; I never thought
                    //I would see this day
            }
            //cell was not 0, need to compute
            count = *cellPtr >> 1;
            if (*cellPtr & 0x01)
            {
                //cell is on, kill it unless it has 2 or 3 neighbors
                if ((count != 2) && (count !=3))
                {
                    clearCell(x, y);
                }
            }
            else
            {
                //cell is off, bring it to life if it has 3 neighbors
                if (count == 3)
                {
                    setCell(x, y);
                }
            }
            cellPtr++;
            x++;
        }
    }
}

int Board::getW()
{
    return w;
}

int Board::getH()
{
    return h;
}
