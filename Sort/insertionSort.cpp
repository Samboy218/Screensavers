#include "insertionSort.h"

InsertionSort::InsertionSort() {
    currHead = 0;
    currInd = -1;
    currVal = -1;
    swapped = false;
}

void InsertionSort::reset() {
    currHead = 1;
    currInd = 0;
    currVal = -1;
    swapped = false;
}

bool InsertionSort::sortStep() {
    if (swapped) {
        swapped = false;
        return false;
    }

    if (currVal == -1)
        currVal = toSort[currHead];

    //if we have looked at everything, we are the smallest

    if (currInd < 0) {
        toSort[0] = currVal;
        swapped = true;
        currHead++;
        currInd = currHead-1;
        currVal = toSort[currHead];
        return currHead > 99;
    }
    //compare the current value to whatever is at the current index, if currVal is larger then we go to the right of it
    if (toSort[currInd] < currVal) {
        toSort[currInd+1] = currVal;
        swapped = true;
        currHead++;
        currInd = currHead-1;
        currVal = toSort[currHead];
        return currHead > 99;
    }
    else {
        //otherwise we need to look at the next element down
        toSort[currInd+1] = toSort[currInd];
        swapped = true;
        currInd--;
        return false;
    }

}
