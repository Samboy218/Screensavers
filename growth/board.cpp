#include "board.h"
//TODO
Board::Board(int x, int y, int num_fact)
{
    w = x;
    h = y;
    num_factions = num_fact;
    factions = (Faction*)malloc(sizeof(Faction)*num_blobs);
    lengthB = w*h;
    board = new unsigned char[lengthB];
    tempBoard = new unsigned char[lengthB];    
    memset(board, 0, lengthB);
    memset(tempBoard, 0, lengthB);
}

//TODO
Board::~Board()
{
    delete[] board;
    board = NULL;
    delete[] tempBoard;
    tempBoard = NULL;
}

void Board::init()
{
    //init the board randomly
    //make the factions
    int interval = w/num_factions;
    for (int x = 0; x < num_factions; x++) {
        int start_x = (rand()%interval) + (interval * x);
        int start_y = rand()%h;
        setCell(start_x, start_y, x);
        }
    }

}

//TODO
void Board::drawBoard(Display *dpy, Window &root, GC &g, XColor liveColor, XColor deadColor)
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
//TODO
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
