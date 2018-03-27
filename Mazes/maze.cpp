#include "maze.h"
#include "stdio.h"

Maze::Maze(int width, int height, int draw_w, int draw_h) {
    w = width;
    h = height;
    window_h = draw_h;
    window_w = draw_w;
    maze = (MazeNode**)malloc(sizeof(MazeNode*)*w*h);
    //init all nodes
    int curr_ind = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            maze[curr_ind] = new MazeNode();
            maze[curr_ind]->setX(x);
            maze[curr_ind]->setY(y);
            curr_ind++;
        }
    }
}

Maze::~Maze() {
    for (int i = 0; i < w*h; i++) {
        delete maze[i];
    }
    free(maze);
}

bool Maze::allVisited() {
    for (int i = 0; i < w*h; i++) {
        if (!maze[i]->isVisited())
            return false;
    }
    return true;
}
bool Maze::visit(int x, int y) {
    return visit(getNode(x, y));
}

bool Maze::visit(MazeNode* node) {
    if (node == NULL)
        return false;
    return node->visit();
}

bool Maze::unvisit(MazeNode* node) {
    if (node == NULL)
        return false;
    return node->unvisit();
}

int Maze::getW() {
    return w;
}

int Maze::getH() {
    return h;
}

bool Maze::removeWall(int x, int y, Direction dir) {
    MazeNode* node1 = getNode(x, y);
    MazeNode* node2;
    Direction dir2;
    switch (dir) {
        case NORTH:
            node2 = getNode(x, y+1);
            dir2 = SOUTH;
            break;
        case NORTHWEST:
            node2 = getNode(x-1, y+1);
            dir2 = SOUTHEAST;
            break;
        case NORTHEAST:
            node2 = getNode(x+1, y+1);
            dir2 = SOUTHWEST;
            break;
        case SOUTH:
            node2 = getNode(x, y-1);
            dir2 = NORTH;
            break;
        case SOUTHWEST:
            node2 = getNode(x-1, y-1);
            dir2 = NORTHEAST;
            break;
        case SOUTHEAST:
            node2 = getNode(x+1, y-1);
            dir2 = NORTHWEST;
            break;
        case WEST:
            node2 = getNode(x-1, y);
            dir2 = EAST;
            break;
        case EAST:
            node2 = getNode(x+1, y);
            dir2 = WEST;
            break;
        default:
            node2=NULL;
    }
    if (! (node1 && node2))
        return false;

    node1->removeWall(dir);
    node2->removeWall(dir2);
    return true;
}


bool Maze::removeWall(int x1, int y1, int x2, int y2) {
    MazeNode* node1 = getNode(x1, y1);
    if (!node1)
        return false;
    MazeNode* node2 = getNode(x2, y2);
    if (!node2)
        return false;
    int xdiff = x1 - x2;
    int ydiff = y1 - y2;
    if (xdiff > 1 || xdiff < -1 || ydiff > 1 || ydiff < -1 || xdiff == ydiff)
        return false;
    //now get the direction for each node
    Direction dir1;
    Direction dir2;
    if (xdiff == 0 && ydiff == 1) {
        dir1 = NORTH;
        dir2 = SOUTH;
    }
    else if (xdiff == 1 && ydiff == 1) {
        dir1 = NORTHEAST;
        dir2 = SOUTHWEST;
    }
    else if (xdiff == -1 && ydiff == 1) {
        dir1 = NORTHWEST;
        dir2 = SOUTHEAST;
    }
    else if (xdiff == 0 && ydiff == -1) {
        dir1 = SOUTH;
        dir2 = NORTH;
    }
    else if (xdiff == 1 && ydiff == -1) {
        dir1 = SOUTHEAST;
        dir2 = NORTHWEST;
    }
    else if (xdiff == -1 && ydiff == -1) {
        dir1 = SOUTHWEST;
        dir2 = NORTHEAST;
    }
    else if (xdiff == 1 && ydiff == 0) {
        dir1 = EAST;
        dir2 = WEST;
    }
    else if (xdiff == -1 && ydiff == 0) {
        dir1 = WEST;
        dir2 = EAST;
    }

    node1->removeWall(dir1);
    node2->removeWall(dir2);
    return true;
}

MazeNode* Maze::getNode(int x, int y) {
    if (x < 0 || x > w-1 || y < 0 || y > h-1)
        return NULL;
    int offset = y*w + x;
    return maze[offset];
}

void Maze::drawMaze() {
    //try to draw it so that walls aren't 2 squares thick.
    int draw_w = w*2 + 1;
    int draw_h = h*2 + 1;
    int** draw_pattern = new int*[draw_w];
    for (int i = 0; i < draw_w; i++) {
        draw_pattern[i] = new int[draw_h];
        for (int j = 0; j < draw_h; j++) {
            draw_pattern[i][j] = 0;
        }
    }
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            MazeNode* node = getNode(x, y);
            uint8_t walls = node->getWalls();
            int pat_x = x*2 + 1;
            int pat_y = y*2 + 1;

            draw_pattern[pat_x][pat_y] = !node->isVisited();
            //increment, so if either wall is closed it will be drawn closed
            draw_pattern[pat_x][pat_y-1] += walls & 0x01;
            draw_pattern[pat_x-1][pat_y-1] += walls & 0x02;
            draw_pattern[pat_x-1][pat_y] += walls & 0x04;
            draw_pattern[pat_x-1][pat_y+1] += walls & 0x08;
            draw_pattern[pat_x][pat_y+1] += walls & 0x10;
            draw_pattern[pat_x+1][pat_y+1] += walls & 0x20;
            draw_pattern[pat_x+1][pat_y] += walls & 0x40;
            draw_pattern[pat_x+1][pat_y-1] += walls & 0x80;

        }
    }
    //now draw form the generated pattern
    for (int y = 0; y < draw_h; y++) {
        for (int x = 0; x < draw_w; x++) {
            if (draw_pattern[x][y] != 0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    for (int i = 0; i < draw_w; i++) {
        delete[] draw_pattern[i];
    }
    delete[] draw_pattern;

}

//basically do what the above draw function does, but into a file
void Maze::toFile(char* filename) {
    //try to draw it so that walls aren't 2 squares thick.
    int draw_w = w*2 + 1;
    int draw_h = h*2 + 1;
    int** draw_pattern = new int*[draw_w];
    for (int i = 0; i < draw_w; i++) {
        draw_pattern[i] = new int[draw_h];
        for (int j = 0; j < draw_h; j++) {
            draw_pattern[i][j] = 0;
        }
    }
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            MazeNode* node = getNode(x, y);
            uint8_t walls = node->getWalls();
            int pat_x = x*2 + 1;
            int pat_y = y*2 + 1;

            draw_pattern[pat_x][pat_y] = !node->isVisited();
            //increment, so if either wall is closed it will be drawn closed
            draw_pattern[pat_x][pat_y-1] += walls & 0x01;
            draw_pattern[pat_x-1][pat_y-1] += walls & 0x02;
            draw_pattern[pat_x-1][pat_y] += walls & 0x04;
            draw_pattern[pat_x-1][pat_y+1] += walls & 0x08;
            draw_pattern[pat_x][pat_y+1] += walls & 0x10;
            draw_pattern[pat_x+1][pat_y+1] += walls & 0x20;
            draw_pattern[pat_x+1][pat_y] += walls & 0x40;
            draw_pattern[pat_x+1][pat_y-1] += walls & 0x80;

        }
    }
    //now dump it into a file
    FILE* out_file;
    out_file = fopen(filename, "w");
    for (int y = 0; y < draw_h; y++) {
        for (int x = 0; x < draw_w; x++) {
            if (draw_pattern[x][y] != 0)
                fprintf(out_file, "1");
            else
                fprintf(out_file, "0");
        }
        fprintf(out_file, "\n");
    }
    fclose(out_file);
    for (int i = 0; i < draw_w; i++) {
        delete[] draw_pattern[i];
    }
    delete[] draw_pattern;
}

void Maze::genMaze() {
    int num_start = rand() % (2 * (w + h - 2));
    int start_x;
    int start_y;
    if (num_start > 0 && num_start <= w) {
        start_x = num_start;
        start_y = 0;
    }
    if (num_start > w && num_start <= w+h-1) {
        start_x = w-1;
        start_y = num_start - w;
    }
    if (num_start > w+h-1 && num_start <= w+h-1+w-1) {
        start_x = num_start - (w+h-1);
        start_y = h-1;
    }
    if (num_start > w+h-1+w-1 && num_start <= w+h-1+w-1+h-2) {
        start_x = 0;
        start_y = num_start - (w+h-1+w-1);
    }
    MazeNode* curr_node = getNode(start_x, start_y);
    NodeStack* my_stack = new NodeStack();
    my_stack->push(curr_node);
    MazeNode* neighbors[4];
    int curr_x = start_x;
    int curr_y = start_y;
    MazeNode* next_node = NULL;
    //visit the first node and push it onto the stack
    //get a neighbor that is unvisited, and make him the current node
    //then repeat this process until the stack is empty
    while (!my_stack->isEmpty()) {
        //my_maze->drawMaze();
        //printf("\n");
        if (curr_node == NULL)
            printf("fuuuuck\n");
        curr_node->visit();
        curr_x = curr_node->getX();
        curr_y = curr_node->getY();
        neighbors[0] = getNode(curr_x+1, curr_y);
        neighbors[1] = getNode(curr_x-1, curr_y);
        neighbors[2] = getNode(curr_x, curr_y+1);
        neighbors[3] = getNode(curr_x, curr_y-1);
        //we'll do a small version of reservior sampling
        int valid_seen = 0;
        next_node = NULL;
        for (int i = 0; i < 4; i++) {
            if (neighbors[i] == NULL || neighbors[i]->isVisited())
                continue;
            valid_seen++;
            if (rand() % valid_seen == 0)
                next_node = neighbors[i];
        }
        //if next_node is NULL, then no valid neighbor exists
        if (next_node == NULL) {
            my_stack->pop();
            curr_node = my_stack->peek();
        }
        //if it isn't null, then break the wall between the two nodes
        else {
            removeWall(curr_x, curr_y, next_node->getX(), next_node->getY());
            //now push the next node and make it the current node
            my_stack->push(next_node);
            curr_node = next_node;
            next_node = NULL;
        }
    }
    getNode(0, 0)->removeWall(NORTH);
    getNode(w-1, h-1)->removeWall(SOUTH);
    //now unvisit all nodes
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            getNode(x, y)->unvisit();
        }
    }
}

void Maze::drawXMaze(Display *dpy, Window &root, GC &g, XColor* colors) {
    //go through each node, and draw it. easy
    //colors is an array of xcolors where
    //colors[0] = bgcolor, colors[1]=wall, colors[2]=seen, colors[3]=visited
    //colors[4] = on stack
    int pixel_thick_x = (window_w/w)/4;
    int pixel_thick_y = (window_h/h)/4;
    int block_w = pixel_thick_x * 4;
    int block_h = pixel_thick_y * 4;
    //printf("x:%d, y:%d\n", block_w*w, block_h*h);
    MazeNode* curr;
    uint8_t walls;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            curr = getNode(x, y);
            int curr_x = x*block_w;
            int curr_y = y*block_h;
            //draw a full rectangle, and then blank out the parts that are open
            XSetForeground(dpy, g, colors[1].pixel);
            XFillRectangle(dpy, root, g, 
                           curr_x, curr_y, block_w, block_h);
            if (curr->onStack())
                XSetForeground(dpy, g, colors[4].pixel);
            else if (curr->isVisited())
                XSetForeground(dpy, g, colors[3].pixel);
            else if (curr->isSeen())
                XSetForeground(dpy, g, colors[2].pixel);
            else
                XSetForeground(dpy, g, colors[0].pixel);

            XFillRectangle(dpy, root, g,
                        curr_x+pixel_thick_x, curr_y+pixel_thick_y,
                        pixel_thick_x*2, pixel_thick_y*2);
            walls = curr->getWalls();
            if (!(walls & 0x01)) {
                XFillRectangle(dpy, root, g,
                            curr_x+pixel_thick_x, curr_y,
                            pixel_thick_x*2, pixel_thick_y);
            }
            //for some reason east and west get flipped...
            if (!(walls & 0x40)) {
                XFillRectangle(dpy, root, g,
                            curr_x+pixel_thick_x*3, curr_y+pixel_thick_y,
                            pixel_thick_x, pixel_thick_y*2);
            }
            if (!(walls & 0x10)) {
                XFillRectangle(dpy, root, g,
                            curr_x+pixel_thick_x, curr_y+pixel_thick_y*3,
                            pixel_thick_x*2, pixel_thick_y);
            }
            if (!(walls & 0x04)) {
                XFillRectangle(dpy, root, g,
                            curr_x, curr_y+pixel_thick_y,
                            pixel_thick_x, pixel_thick_y*2);
            }
        }
    }
}
