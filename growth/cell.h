#ifndef CELL_H
#define CELL_H

class Cell {
    public:
    Cell();
    Cell(int x_pos, int y_pos);
    void init(int facID);
    int curr_health;
    int faction_id;
    int move_id;
    int x;
    int y;
};

#endif
