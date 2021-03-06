#ifndef MAZE_NODE_H
#define MAZE_NODE_H
#include <stdint.h>
enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, DIRECTION_NONE} ;
class MazeNode {
    public:
        MazeNode();
        MazeNode(MazeNode* toCopy);
        bool isVisited();
        bool isSeen();
        void see(bool val);
        bool onStack();
        void setOnStack(bool val);
        bool visit();
        bool unvisit();
        bool hasWall(Direction dir);
        void removeWall(Direction  dir);
        int getX();
        int getY();
        void setX(int val);
        void setY(int val);
        Direction getParent();
        void setParent(Direction dir);
        int getF();
        int getH();
        int getG();
        void setF(int val);
        void setH(int val);
        void setG(int val);
        uint8_t getWalls();



    private:
        //each bit says whether there is a wall
        //0x01 is N
        //0x02 is NE
        //0x04 is E
        //0x08 is SE
        //0x10 is S
        //0x20 is SW
        //0x40 is W
        //0x80 is NW
        uint8_t walls;
        //used for A*
        Direction parent;
        int f;
        int h;
        int g;
        bool visited;
        bool seen;
        bool on_stack;
        int x;
        int y;
};
#endif
