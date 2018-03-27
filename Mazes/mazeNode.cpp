#include "mazeNode.h"

MazeNode::MazeNode() {
    walls = 0xFF;
    visited = false;
}

bool MazeNode::isVisited() {
    return visited;
}

bool MazeNode::visit() {
    if (visited) 
        return false;
    visited = true;
    return true;
}

bool MazeNode::hasWall(Direction dir) {
    //I think this works
    uint8_t mask = 1 << dir;
    return (walls & mask);
}

void MazeNode::removeWall(Direction  dir) {
    uint8_t mask = 1 << dir;
    walls &= ~mask;
}

int MazeNode::getX() {
    return x;
}

int MazeNode::getY() {
    return y;
}

void MazeNode::setX(int val) {
    x = val;
}

void MazeNode::setY(int val) {
    y = val;
}

uint8_t MazeNode::getWalls() {
    return walls;
}
