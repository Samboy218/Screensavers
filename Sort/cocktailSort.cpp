#include "cocktailSort.h"


CocktailSort::CocktailSort() {
    currInd = 0;
    //true means we were incrementing, false means we were decrementing
    direction = true;
}

void CocktailSort::reset() {
    currInd = 0;
    direction = true;
}

bool CocktailSort::sortStep() {
    //go through the array, find an out-of-order pair and swap them
    switch (direction) {
        case true:
        for (int i = currInd; i < 99; i++) {
            if (toSort[i] > toSort[i+1]) {
                int temp = toSort[i];
                toSort[i] = toSort[i+1];
                toSort[i+1] = temp;
                currInd = i+1;
                direction = true;
                return false;
            }
        }
        //no swap, we've gone through the array now do it backwards
        for (int i = 99; i > 0; i--) {
            if (toSort[i] < toSort[i-1]) {
                int temp = toSort[i];
                toSort[i] = toSort[i-1];
                toSort[i-1] = temp;
                currInd = i-1;
                direction = false;
                return false;
            }
        }

        break;

        case false:
        for (int i = currInd; i > 0; i--) {
            if (toSort[i] < toSort[i-1]) {
                int temp = toSort[i];
                toSort[i] = toSort[i-1];
                toSort[i-1] = temp;
                currInd = i-1;
                direction = false;
                return false;
            }
        }
        //no swap, we've gone through the array now do it backwards
        for (int i = 0; i < 99; i++) {
            if (toSort[i] > toSort[i+1]) {
                int temp = toSort[i];
                toSort[i] = toSort[i+1];
                toSort[i+1] = temp;
                currInd = i+1;
                direction = true;
                return false;
            }
        }

        break;
    }
    //no swap and that means we are done
    return true;
}
