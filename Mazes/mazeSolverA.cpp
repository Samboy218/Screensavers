#include "mazeSolverA.h"

MazeSolverA::MazeSolverA(Maze* maze) : MazeSolver(maze) {
    curr_x = 0;
    curr_y = 0;
    MazeNode* start = toSolve->getNode(curr_x, curr_y);
    start->visit();
    open = new std::vector<MazeNode*>;
    closed = new std::vector<MazeNode*>;
    redraw = new std::vector<MazeNode*>;
    start->setParent(DIRECTION_NONE);
    int g = getG(start);
    int f = g+getH(start);
    start->setF(f);
    start->setG(g);
    start->see(true);
    open->push_back(start);
}

bool MazeSolverA::takeStep() {
    //get the lowest square in the open list, S
    //put S in the closed list
    //for each wakable adjacent square to S
        //if in closed, ignore it
        //if in open list, check if the F score from current square is better
        //if not in open, add it and compute its scores
    redraw->clear();    
    if (open->size() == 0)
        return true;
    if (curr_x == toSolve->getW()-1 && curr_y == toSolve->getH()-1)
        return true;
    MazeNode* curr_node;
    MazeNode* lowest_node = open->at(0);
    int lowest_score = lowest_node->getF();
    for (int i = 0; i < open->size(); i++) {
        curr_node = open->at(i);
        if (curr_node->getF() < lowest_score) {
            lowest_node = curr_node;
            lowest_score = curr_node->getF();
        }
    }
    //okay now we have S
    std::remove(open->begin(), open->end(), lowest_node);
    open->resize(open->size()-1);
    lowest_node->visit();
    closed->push_back(lowest_node);
    redraw->push_back(lowest_node);
    curr_x = lowest_node->getX();
    curr_y = lowest_node->getY();
    if (curr_x == toSolve->getW()-1 && curr_y == toSolve->getH()-1) {
        paintPath(lowest_node);
        return true;
    }
    uint8_t walls = lowest_node->getWalls();
    int x_vals[4] = {0, 0, 1, -1};
    int y_vals[4] = {-1, 1, 0, 0};
    int wall_vals[4] = {0x01, 0x10, 0x04, 0x40};
    for (int i = 0; i < 4; i++) {
        curr_node = toSolve->getNode(curr_x + x_vals[i], curr_y + y_vals[i]);
        if (!curr_node)
            continue;
        if (!(walls & wall_vals[i])) {
            if (isInClosed(curr_node))
                continue;
            if (isInOpen(curr_node)) {
                Direction old_parent = curr_node->getParent();
                //get the score as if we came from the current node
                curr_node->setParent(getDirection(lowest_node, curr_node));
                int curr_g = getG(curr_node);
                int curr_h = getH(curr_node);
                int curr_f = curr_g+curr_h;
                if (curr_f < curr_node->getF()) {
                    curr_node->setF(curr_f);
                    curr_node->setG(curr_g);
                }
                //other path was better, reset the old parent
                else {
                    curr_node->setParent(old_parent);
                }
            }
            else {
                curr_node->setParent(getDirection(lowest_node, curr_node));
                if (curr_node->getParent() == DIRECTION_NONE)
                    printf("ooooohhh crap thats bad\n");
                int g = getG(curr_node);
                int h = getH(curr_node);
                int f = g+h;
                curr_node->setG(g);
                curr_node->setH(h);
                curr_node->setF(f);
                curr_node->see(true);
                open->push_back(curr_node);
                redraw->push_back(curr_node);
            }
        }
    }
    return false;
}

int MazeSolverA::getG(MazeNode* node) {
    //return the parent's G+1
    MazeNode* parent;
    int x = node->getX();
    int y = node->getY();
    switch (node->getParent()) {
        case NORTH:
            parent = toSolve->getNode(x, y-1);
            break;
        case EAST:
            parent = toSolve->getNode(x+1, y);
            break;
        case SOUTH:
            parent = toSolve->getNode(x, y+1);
            break;
        case WEST:
            parent = toSolve->getNode(x-1, y);
            break;
        default:
            parent = NULL;
    }
    if (parent)
        return parent->getG() + 1;
    //no parent
    return 0;
}

int MazeSolverA::getH(MazeNode* node) {
    //get the manhattan distance to the end
    int xDiff = node->getX() - (toSolve->getW()-1);
    int yDiff = node->getY() - (toSolve->getH()-1);
    if (xDiff < 0)
        xDiff *= -1;
    if (yDiff < 0)
        yDiff *= -1;
    return xDiff + yDiff;
}

bool MazeSolverA::isInOpen(MazeNode* node) {
    for (int i = 0; i < open->size(); i++) {
        if (open->at(i) == node)
            return true;
    }
    return false;
}

bool MazeSolverA::isInClosed(MazeNode* node) {
    for (int i = 0; i < closed->size(); i++) {
        if (closed->at(i) == node)
            return true;
    }
    return false;
}

Direction MazeSolverA::getDirection(MazeNode* parent, MazeNode* child) {
    if (!(parent && child))
        return DIRECTION_NONE;
    int x_diff = parent->getX() - child->getX();
    int y_diff = parent->getY() - child->getY();
    if (x_diff < -1 || x_diff > 1 || y_diff < -1 || y_diff > 1)
        return DIRECTION_NONE;
    if (x_diff == 0 && y_diff == -1)
        return NORTH;
    if (x_diff == 0 && y_diff == 1)
        return SOUTH;
    if (x_diff == 1 && y_diff == 0)
        return EAST;
    if (x_diff == -1 && y_diff == 0)
        return WEST;
    return DIRECTION_NONE;
}

void MazeSolverA::paintPath(MazeNode* node) {
    if (!node)
        return;
    MazeNode* curr = node;
    MazeNode* parent;
    int x = curr->getX();
    int y = curr->getY();

    while (curr) {
        curr->setOnStack(true);
        redraw->push_back(curr);
        switch (curr->getParent()) {
            case NORTH:
                y--;
                break;
            case EAST:
                x++;
                break;
            case SOUTH:
                y++;
                break;
            case WEST:
                x--;
                break;
            default:
                return;
        }
        curr = toSolve->getNode(x, y);
    }
}
