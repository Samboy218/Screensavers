#include "mazeSolverDFS.h"

MazeSolverDFS::MazeSolverDFS(Maze* maze):MazeSolver(maze) {
    curr_x = 0;
    curr_y = 0;
    MazeNode* start = toSolve->getNode(curr_x, curr_y);
    start->visit();
    stack = new NodeStack();
    redraw = new std::vector<MazeNode*>;
    stack->push(start);
    start->setOnStack(true);
}

bool MazeSolverDFS::takeStep() {
    //make every node around us seen
    redraw->clear();    
    if (stack->isEmpty())
        return true;
    MazeNode* temp_node = toSolve->getNode(curr_x, curr_y);
    uint8_t walls = temp_node->getWalls();
    temp_node = toSolve->getNode(curr_x, curr_y-1);
    if (!(walls & 0x01) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y-1);
    if (!(walls & 0x02) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y);
    if (!(walls & 0x04) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y+1);
    if (!(walls & 0x08) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x, curr_y+1);
    if (!(walls & 0x10) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y+1);
    if (!(walls & 0x20) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y);
    if (!(walls & 0x40) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y-1);
    if (!(walls & 0x80) && temp_node) {
        temp_node->see(true);
        redraw->push_back(temp_node);
    }
    //if we are at the end, return true
    if (curr_x == toSolve->getW()-1 && curr_y == toSolve->getH()-1)
        return true;
    //now visit the next node
    //order of preference:
    //SE 0x08
    //E 0x04
    //S 0x10
    //NE 0x02
    //SW 0x20
    //N 0x01
    //W 0x40
    //NW 0x80
    temp_node = toSolve->getNode(curr_x+1, curr_y+1);
    if (!(walls & 0x08) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x++;
            curr_y++;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y);
    if (!(walls & 0x04) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x++;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x, curr_y+1);
    if (!(walls & 0x10) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_y++;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y-1);
    if (!(walls & 0x02) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x++;
            curr_y--;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y+1);
    if (!(walls & 0x20) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x--;
            curr_y++;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x, curr_y-1);
    if (!(walls & 0x01) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_y--;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y);
    if (!(walls & 0x40) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x--;
            return false;
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y-1);
    if (!(walls & 0x80) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            stack->push(temp_node);
            redraw->push_back(temp_node);
            curr_x--;
            curr_y--;
            return false;
        }
    }
    temp_node = stack->pop();
    temp_node->setOnStack(false);
    redraw->push_back(temp_node);
    temp_node = stack->peek();
    curr_x = temp_node->getX();
    curr_y = temp_node->getY();
    return false;
}
