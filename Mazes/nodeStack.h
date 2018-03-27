#ifndef NODE_STACK_H
#define NODE_STACK_H
#include "mazeNode.h"

class NodeStack {
    public:
        NodeStack();
        ~NodeStack();
        bool isEmpty();
        void push(MazeNode* node);
        MazeNode* pop();
        MazeNode* peek();

    private:
        MazeNode** nodes;
        int size;
        int capacity;
        void resize();
};

#endif
