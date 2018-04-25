#ifndef NODE_QUEUE_H
#define NODE_QUEUE_H

#include "mazeNode.h"
#include <stdlib.h>

class NodeQueue {
    public:
        NodeQueue();
        ~NodeQueue();
        bool isEmpty();
        void enqueue(MazeNode* node);
        MazeNode* dequeue();
        MazeNode* peek();

    private:
        MazeNode** nodes;
        int size;
        int capacity;
        int head;
        int tail;
        void resize();
};

#endif
