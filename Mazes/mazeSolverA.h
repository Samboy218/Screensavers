#ifndef MAZE_SOLVER_A_H
#define MAZE_SOLVER_A_H

#include "mazeSolver.h"
#include <algorithm>
#include <stdio.h>
#include <vector>

class MazeSolverA : public MazeSolver {
    public:
        MazeSolverA(Maze* maze);
        virtual bool takeStep();

    private:
        //Maze* toSolve;
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
