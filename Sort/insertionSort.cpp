#include "insertionSort.h"

InsertionSort::InsertionSort() {
    currHead = 0;
    currInd = -1;
    currVal = -1;
}

void InsertionSort::reset() {
    currHead = 1;
    currInd = 0;
    currVal = -1;
}

bool InsertionSort::sortStep() {
    if (currVal == -1)
        currVal = toSort[currHead];

    //if we have looked at everything, we are the smallest

    if (currInd < 0) {
        toSort[0] = currVal;
        currHead++;
        currInd = currHead-1;
        currVal = toSort[currHead];
        return currHead > 99;
    }
    //compare the current value to whatever is at the current index, if currVal is larger then we go to the right of it
    if (toSort[currInd] < currVal) {
        toSort[currInd+1] = currVal;
        currHead++;
        currInd = currHead-1;
        currVal = toSort[currHead];
        return currHead > 99;
    }
    else {
        //otherwise we need to look at the next element down
        toSort[currInd+1] = toSort[currInd];
        currInd--;
        return false;
    }

}
/*
bool InsertionSort::sortStep() {
    int curr = toSort[currHead];
    for (int i = currHead; i > 0; i--) {
        //go from the top of the sorted list until we find an element less than us, the we go to the right of that element
        if (toSort[i-1] < curr) {
            toSort[i] = curr;
            currHead++;
            return currHead > 100;
        }
        else {
            toSort[i] = toSort[i-1];
        }
    }
    //the current element is the smallest element
    toSort[0] = curr;
    currHead++;
    return currHead > 100;
}
*/
