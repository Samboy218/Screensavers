#ifndef MOVE_H
#define MOVE_H

class Move {
    public:
    Move(int t, int i, int x, int y);
    int time;
    int id;
    int origin_x;
    int origin_y;
};

class compareMove {
    public:
    bool operator()(Move lhs, Move rhs)
    {
        return lhs.time > rhs.time;
    }
};

#endif
