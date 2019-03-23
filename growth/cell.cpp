#include "cell.h"

Cell::Cell() {
    x = -1;
    y = -1;
    faction_id = -1;
    curr_health = 0;
    move_id = 0;
}
Cell::Cell(int x_pos, int y_pos) {
    x = x_pos;
    y = y_pos;
    faction_id = -1;
    curr_health = 0;
    move_id = 0;
}
void Cell::init(int facID) {
    faction_id = facID;
    curr_health = 0;
    move_id = 0;
}

