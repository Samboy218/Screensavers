#include "bubbleSort.h"

BubbleSort::BubbleSort() {
    currInd = 99;
    swapped = false;
}

void BubbleSort::reset() {
    currInd = 99;
    swapped = false;
}

bool BubbleSort::sortStep() {
    //go through the array, find an out-of-order pair and swap them

    if (swapped) {
        swapped = false;
        return false;
    }

    if (currInd < 1) {
        bool done = true;
        for (int i = 99; i > 0; i--) {
            if (toSort[i] < toSort[i-1]) {
                done = false;
                break;
            }
        }
        if (done)
            return true;
        currInd = 99;
        return false;
    }
    
    if (toSort[currInd] < toSort[currInd-1]) {
            int temp = toSort[currInd];
            toSort[currInd] = toSort[currInd-1];
            toSort[currInd-1] = temp;
            currInd--;
            swapped = true;
            return false;
    }

    //keep it moving
    currInd--;
    return false;
}
