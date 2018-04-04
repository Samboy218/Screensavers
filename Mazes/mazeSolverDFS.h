#ifndef MAZE_SOLVER_DFS_H
#define MAZE_SOLVER_DFS_H

#include "nodeStack.h"
#include "mazeSolver.h"
#include <stdio.h>

class MazeSolverDFS : public MazeSolver {
    public:
        MazeSolverDFS(Maze* maze);
        virtual bool takeStep();

    private:
        //Maze* toSolve;
        NodeStack* stack;
        int curr_x;
        int curr_y;

};

#endif
