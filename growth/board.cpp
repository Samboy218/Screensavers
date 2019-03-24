#include "board.h"

Board::Board(int x, int y, int num_fac, int cell_width, int cell_height, XColor* xcolors)
{
    w = x;
    h = y;
    std::vector<std::vector<Cell> > tmp_board;
    for (int x = 0; x < w; x++) {
        std::vector<Cell> row;
        for (int y = 0; y < h; y++) {
            Cell curr_cell(x, y);
            row.push_back(curr_cell);
        }
        tmp_board.push_back(row);
    }
    board = tmp_board;

    for (int i = 0; i < num_fac; i++) {
        factions.emplace_back();
    }
    cell_w = cell_width;
    cell_h = cell_height;
    colors = xcolors;

}

Board::~Board()
{
}

void Board::init()
{
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            board.at(x).at(y).init(-1);
        }
    }
    //each faction gets 3 staring locations
    //init the board randomly
    //make the factions
    int interval = w/factions.size();
    for (int i = 0; i < factions.size(); i++) {
        factions.at(i).init(i);
        for (int j = 0; j < 3; j++) {
            int start_x = (rand()%w);
            int start_y = (rand()%h);

            setCell(start_x, start_y, i, 0);
        }
    }
}

int Board::setCell(int x, int y, int facID, int step_time) {
    if (x < 0 || x >= w || y < 0 || y >= h || facID > factions.size())
        return -1;
    board.at(x).at(y).init(facID);
    board.at(x).at(y).curr_health = factions.at(facID).getHealth();
    unsigned int time = factions.at(facID).getSpeed() + step_time;
    int id = rand();
    moves.push(Move(time, id, x, y));
    board.at(x).at(y).move_id = id;
}

void Board::drawBoard(Display *dpy, Window &root, GC &g)
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int fac = board.at(x).at(y).faction_id;
            XSetForeground(dpy, g, colors[fac+1].pixel);
            XFillRectangle(dpy, root, g, x*cell_w, y*cell_h, cell_w, cell_h);
        }
    }
}

void Board::drawBoard(Display *dpy, Window &root, GC &g, int x, int y)
{
    //only draw the neighbors of the passed in cell
    for (int i = x-1; i < x+2; i++) {
        if (i < 0 || i >= w)
            continue;
        for (int j = y-1; j < y+2; j++) {
            if (j < 0 || j >= h)
                continue;
            int fac = board.at(i).at(j).faction_id;
            XSetForeground(dpy, g, colors[fac+1].pixel);
            XFillRectangle(dpy, root, g, x*cell_w, y*cell_h, cell_w, cell_h);

        }
    }
}

bool Board::step(int step_time)
{
    if (moves.size() == 0)
        return false;

    //pop a move
    Move currMove = moves.top();
    if (currMove.time > step_time)
        return false;
    moves.pop();
    while (currMove.id != board.at(currMove.origin_x).at(currMove.origin_y).move_id) {
        currMove = moves.top();
        moves.pop();
    }
    Cell currCell = board.at(currMove.origin_x).at(currMove.origin_y);
    //do the move
    //check if a move can be made
    Cell neighbors[8];
    //U,UR,R,DR,D,DL,L,UL
    if (currMove.origin_y > 0)
        neighbors[0] = board.at(currMove.origin_x).at(currMove.origin_y-1);

    if (currMove.origin_y > 0 && currMove.origin_x < board.size()-1)
        neighbors[1] = board.at(currMove.origin_x + 1).at(currMove.origin_y-1);

    if (currMove.origin_x < board.size()-1)
        neighbors[2] = board.at(currMove.origin_x + 1).at(currMove.origin_y);

    if (currMove.origin_y < board.at(0).size()-1 && currMove.origin_x < board.size()-1)
        neighbors[3] = board.at(currMove.origin_x + 1).at(currMove.origin_y + 1);

    if (currMove.origin_y < board.at(0).size()-1 )
        neighbors[4] = board.at(currMove.origin_x).at(currMove.origin_y + 1);

    if (currMove.origin_y < board.at(0).size()-1 && currMove.origin_x > 0)
        neighbors[5] = board.at(currMove.origin_x - 1).at(currMove.origin_y + 1);

    if (currMove.origin_x > 0)
        neighbors[6] = board.at(currMove.origin_x - 1).at(currMove.origin_y);

    if (currMove.origin_y > 0 && currMove.origin_x > 0)
        neighbors[7] = board.at(currMove.origin_x - 1).at(currMove.origin_y - 1);

    int moveChoice = -1;
    int valid_seen = 0;

    for (int i = 0; i < 8; i++) {
        if (neighbors[i].x == -1 || neighbors[i].faction_id == currCell.faction_id)
            continue;
        valid_seen++;
        if (rand() % valid_seen == 0)
            moveChoice = i;

    }
    //no valid move from this node
    //but actually still queue a move because we may have one in the future
    if (moveChoice != -1) {

        //okay now we have a valid move, now strike!
        unsigned int hitPower = factions.at(currCell.faction_id).getStrength();
        unsigned int hitAccuracy = factions.at(currCell.faction_id).getAccuracy();

        unsigned int targetArmor;
        if (neighbors[moveChoice].faction_id < 0)
            targetArmor = 0;
        else
            targetArmor = factions.at(neighbors[moveChoice].faction_id).getArmor();
        targetArmor++;
        //generate a random number for accuracy and armor, larger number wins
        if (rand()%hitAccuracy > rand()%targetArmor)
            board.at(neighbors[moveChoice].x).at(neighbors[moveChoice].y).curr_health -= hitPower;
        
        if (board.at(neighbors[moveChoice].x).at(neighbors[moveChoice].y).curr_health <= 0)
            setCell(neighbors[moveChoice].x, neighbors[moveChoice].y, currCell.faction_id, step_time);
    }
    //queue another move
    unsigned int time = factions.at(currCell.faction_id).getSpeed() + step_time;
    int id = rand();
    moves.push(Move(time, id, currCell.x, currCell.y));
    board.at(currCell.x).at(currCell.y).move_id = id;
    if (moveChoice == -1)
        return false;
    return true;

}

bool Board::checkDone() {
    int curr_fac = board.at(0).at(0).faction_id;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (board.at(i).at(j).faction_id != curr_fac)
                return false;
        }
    }
    return true;
}
