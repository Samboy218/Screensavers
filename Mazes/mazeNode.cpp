#include "mazeNode.h"

MazeNode::MazeNode() {
    walls = 0xFF;
    visited = false;
    seen = false;
    on_stack = false;
}

bool MazeNode::isVisited() {
    return visited;
}

bool MazeNode::visit() {
    visited = true;
    return true;
}

bool MazeNode::isSeen() {
    return seen;
}

void MazeNode::see(bool val) {
    seen = val;
}

bool MazeNode::onStack() {
    return on_stack;
}

void MazeNode::setOnStack(bool val) {
    on_stack = val;
}

bool MazeNode::unvisit() {
    visited = false;
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

Direction MazeNode::getParent() {
    return parent;
}

void MazeNode::setParent(Direction val) {
    parent = val;
}

int MazeNode::getF() {
    return f;
}

void MazeNode::setF(int val) {
    f = val;
}

int MazeNode::getH() {
    return h;
}

void MazeNode::setH(int val) {
    h = val;
}

int MazeNode::getG() {
    return g;
}

void MazeNode::setG(int val) {
    g = val;
}

uint8_t MazeNode::getWalls() {
    return walls;
}
