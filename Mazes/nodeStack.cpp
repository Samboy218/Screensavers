#include "nodeStack.h"
#include "stdlib.h"

NodeStack::NodeStack() {
    nodes = new MazeNode*[1];
    nodes[0] = NULL;
    size = 0;
    capacity = 1;
}

NodeStack::~NodeStack() {
    delete[] nodes;
    size = 0;
    capacity = 0;
}

bool NodeStack::isEmpty() {
    return size==0;
}

void NodeStack::push(MazeNode* node) {
    if (size == capacity)
        resize();
    nodes[size] = node;
    size++;
}

MazeNode* NodeStack::pop() {
    if (size==0)
        return NULL;
    size--;
    MazeNode* to_ret = nodes[size];
    nodes[size] = NULL;
    return to_ret;
}

MazeNode* NodeStack::peek() {
    if (size==0)
        return NULL;
    return nodes[size-1];
}

void NodeStack::resize() {
    //just double the size of the array
    MazeNode** new_nodes = new MazeNode*[capacity*2];
    for (int i = 0; i < size; i++) {
        new_nodes[i] = nodes[i];
        nodes[i] = NULL;
    }
    capacity *= 2;
    delete[] nodes;
    nodes = new_nodes;
}
