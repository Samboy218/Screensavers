#include "quickSort.h"

QuickSort::QuickSort() {
    partStack = new std::stack<int* >;
    int* init = (int*)malloc(sizeof(int)*2);
    init[0] = 0;
    init[1] = 99;
    partStack->push(init);
    i = -1;
    j = -1;
    pivot = -1;
}

void QuickSort::reset() {
    while (!partStack->empty()) {
        free (partStack->top());
        partStack->pop();
    }
    int* init = (int*)malloc(sizeof(int)*2);
    init[0] = 0;
    init[1] = 99;
    partStack->push(init);
    i = -1;
    j = -1;
    pivot = -1;
}

bool QuickSort::sortStep() {
    //partition
    //make pivot middle of range (hoare partition)
    //start i at low, start j at high
    //increment i until we find an element >= pivot
    //decrement j until we find an element <= pivot
    //if i ==j, we are done. otherwise swap i and j and continue

    //check if i,j,pivot are -1
    if (i == -1 || j == -1 || pivot == -1) {
        //the next thing should be on the stack
        if (partStack->empty())
            return true;
        int* next = partStack->top();
        i = next[0];
        j = next[1];
        pivot = toSort[(i+j)/2];
        //printf("sorting %d,%d,%d\n", i, j, pivot);
    }

    if (toSort[i] < pivot) {
        i++;
        return false;
    }
    if (toSort[j] > pivot) {
        j--;
        return false;
    }
    //if we get here, both i and j are ready to swap

    if (i >= j) {
        //this partition is sorted
        //the top of the stack should still be us
        int* curr = partStack->top();
        partStack->pop();
        int oldLow = curr[0];
        int oldHigh = curr[1];
        free(curr);

        int* nextLow = (int*)malloc(sizeof(int)*2);
        nextLow[0] = oldLow;
        nextLow[1] = j;
        if (nextLow[0] < nextLow[1]) {
            partStack->push(nextLow);
            //printf("pushing %d,%d\n", nextLow[0], nextLow[1]);
        }

        int* nextHigh = (int*)malloc(sizeof(int)*2);
        nextHigh[0] = j+1;
        nextHigh[1] = oldHigh;
        if (nextHigh[0] < nextHigh[1]) {
            partStack->push(nextHigh);
            //printf("pushing %d,%d\n", nextHigh[0], nextHigh[1]);
        }

        //if the stack is empty after this, then we are done
        if (partStack->empty()) {
            return true;
        }
        i = -1;
        j = -1;
        pivot = -1;
        return false;
    }
    //swap i and j
    int temp = toSort[i];
    toSort[i] = toSort[j];
    toSort[j] = temp;
    return false;
}
