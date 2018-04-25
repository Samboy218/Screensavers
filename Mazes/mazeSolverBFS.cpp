#include "mazeSolverBFS.h"

MazeSolverBFS::MazeSolverBFS(Maze* maze):MazeSolver(maze) {
    curr_x = 0;
    curr_y = 0;
    MazeNode* start = toSolve->getNode(curr_x, curr_y);
    start->visit();
    queue = new NodeQueue();
    queue->enqueue(start);
    start->setOnStack(true);
}

bool MazeSolverBFS::takeStep() {
    //make every node around us seen
    if (queue->isEmpty())
        return true;
    if (curr_x == toSolve->getW()-1 && curr_y == toSolve->getH()-1)
        return true;
    //MazeNode* temp_node = toSolve->getNode(curr_x, curr_y);
    MazeNode* temp_node = queue->dequeue();
    temp_node->setOnStack(false);
    curr_x = temp_node->getX();
    curr_y = temp_node->getY();
    if (curr_x == toSolve->getW()-1 && curr_y == toSolve->getH()-1)
        return true;

    uint8_t walls = temp_node->getWalls();
    //now visit the surrounding nodes
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
            temp_node->setParent(NORTHWEST);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y);
    if (!(walls & 0x04) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(WEST);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x, curr_y+1);
    if (!(walls & 0x10) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(NORTH);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x+1, curr_y-1);
    if (!(walls & 0x02) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(SOUTHWEST);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y+1);
    if (!(walls & 0x20) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(NORTHEAST);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x, curr_y-1);
    if (!(walls & 0x01) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(SOUTH);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y);
    if (!(walls & 0x40) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(EAST);
            queue->enqueue(temp_node);
        }
    }
    temp_node = toSolve->getNode(curr_x-1, curr_y-1);
    if (!(walls & 0x80) && temp_node) {
        if (!temp_node->isVisited()){
            temp_node->visit();
            temp_node->setOnStack(true);
            temp_node->setParent(SOUTHEAST);
            queue->enqueue(temp_node);
        }
    }
    return false;
}

