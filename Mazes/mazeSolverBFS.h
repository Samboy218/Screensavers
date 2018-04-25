#ifndef MAZE_SOLVER_BFS_H
#define MAZE_SOLVER_BFS_H

#include "nodeQueue.h"
#include "mazeSolver.h"

class MazeSolverBFS : public MazeSolver {
    public:
        MazeSolverBFS(Maze* maze);
        virtual bool takeStep();
    private:
        NodeQueue* queue;
        int curr_x;
        int curr_y;
};

#endif
