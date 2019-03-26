#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include "maze.h"
#include <vector>

class MazeSolver {
    public:
        MazeSolver(Maze* maze);
        virtual bool takeStep() = 0;
        std::vector<MazeNode*>* redraw;

    protected:
        Maze* toSolve;
};

#endif
