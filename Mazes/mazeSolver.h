#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include "maze.h"

class MazeSolver {
    public:
        MazeSolver(Maze* maze);
        virtual bool takeStep() = 0;

    protected:
        Maze* toSolve;
};

#endif
