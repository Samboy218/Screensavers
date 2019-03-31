#include "bubbleSort.h"

BubbleSort::BubbleSort() {
    currInd = 0;
}

void BubbleSort::reset() {
    currInd = 0;
}

bool BubbleSort::sortStep() {
    //go through the array, find an out-of-order pair and swap them
    for (int i = currInd; i < 99; i++) {
        if (toSort[i] > toSort[i+1]) {
            int temp = toSort[i];
            toSort[i] = toSort[i+1];
            toSort[i+1] = temp;
            currInd = i+1;
            return false;
        }
    }
    //no swap, but we don't know if we're done
    for (int i = 0; i < 99; i++) {
        if (toSort[i] > toSort[i+1]) {
            int temp = toSort[i];
            toSort[i] = toSort[i+1];
            toSort[i+1] = temp;
            currInd = i+1;
            return false;
        }
    }
    //no swap and that means we are done
    return true;
}
