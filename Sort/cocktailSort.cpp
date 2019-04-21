#include "cocktailSort.h"


CocktailSort::CocktailSort() {
    currInd = 99;
    //true means we were decrementing, false means we're incrementing
    direction = true;
    swapped = false;
}

void CocktailSort::reset() {
    currInd = 99;
    direction = true;
    swapped = false;
}

bool CocktailSort::sortStep() {

    if (swapped) {
        swapped = false;
        return false;
    }
    bool check = false;
    if (currInd == 0 && direction) {
        direction = false;
        check = true;
    }
    if (currInd == 99 && !direction) {
        direction = true;
        check = true;
    }

    if (check) {
        bool done = true;
        for (int i = 0; i < 99; i++) {
            if (toSort[i] > toSort[i+1])
                done = false;
        }
        return done;
    }


    switch (direction) {
        case true:
            if (toSort[currInd] < toSort[currInd-1]) {
                int temp = toSort[currInd];
                toSort[currInd] = toSort[currInd-1];
                toSort[currInd-1] = temp;
                currInd--;
                swapped = true;
                return false;
            }
            currInd--;
        break;
        case false:
            if (toSort[currInd] > toSort[currInd+1]) {
                int temp = toSort[currInd];
                toSort[currInd] = toSort[currInd+1];
                toSort[currInd+1] = temp;
                currInd++;
                swapped = true;
                return false;
            }
            currInd++;
        break;
    }
    return false;
}
