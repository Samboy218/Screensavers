#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"
#include "mazeNode.h"
#include "nodeStack.h"
#include <stdio.h>

class MazeSolver {
    public:
        MazeSolver(Maze* maze);
        bool takeStep();

    private:
        Maze* toSolve;
        NodeStack* stack;
        int curr_x;
        int curr_y;

};

#endif
