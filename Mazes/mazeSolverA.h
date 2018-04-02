#ifndef MAZE_SOLVER_A_H
#define MAZE_SOLVER_A_H

#include "maze.h"
#include "mazeNode.h"
#include <algorithm>
#include <stdio.h>
#include <vector>

class MazeSolverA {
    public:
        MazeSolverA(Maze* maze);
        bool takeStep();

    private:
        Maze* toSolve;
        std::vector<MazeNode*>* open;
        std::vector<MazeNode*>* closed;
        int getG(MazeNode* node);
        int getH(MazeNode* node);
        bool isInOpen(MazeNode* node);
        bool isInClosed(MazeNode* node);
        int curr_x;
        int curr_y;
        Direction getDirection(MazeNode* parent, MazeNode* child);
        void paintPath(MazeNode* node);
};

#endif
