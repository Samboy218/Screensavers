#include "nodeQueue.h"

NodeQueue::NodeQueue() {
    nodes = new MazeNode*[2];
    nodes[0] = NULL;
    nodes[1] = NULL;
    size = 0;
    capacity = 2;
    head = 0;
    tail = 0;
}

NodeQueue::~NodeQueue() {
    delete[] nodes;
    size = 0;
    capacity = 0;
}

bool NodeQueue::isEmpty() {
    return size == 0;
}

//put an item at tail, increment tail (with wrap), increment size
void NodeQueue::enqueue(MazeNode* node) {
    if (size == capacity)
        resize();
    nodes[tail] = node;
    tail = (tail+1) % capacity;
    size++;
}

//remove node at head, increment head (with wrap), decrement size
MazeNode* NodeQueue::dequeue() {
    if (size == 0)
        return NULL;
    MazeNode* to_ret = nodes[head];
    nodes[head] = NULL;
    head = (head+1) % capacity;
    size--;
    return to_ret;
}

//return node at head
MazeNode* NodeQueue::peek() {
    if (size == 0)
        return NULL;
    return nodes[head];
}

void NodeQueue::resize() {
    MazeNode** new_nodes = new MazeNode*[capacity*2];
    int new_ind = 0;
    //we've wrapped around
    if (tail <= head) {
        for (int i = head; i < capacity; i++) {
            new_nodes[new_ind] = nodes[i];
            nodes[i] = NULL;
            new_ind++;
        }
        for (int i = 0; i < tail; i++) {
            new_nodes[new_ind] = nodes[i];
            nodes[i] = NULL;
            new_ind++;
        }
    }
    //we haven't wrapped around
    else {
        for (int i = head; i < tail; i++) {
            new_nodes[new_ind] = nodes[i];
            nodes[i] = NULL;
            new_ind++;
        }
    }
    capacity *= 2;
    delete[] nodes;
    head = 0;
    tail = size;
    nodes = new_nodes;
}
