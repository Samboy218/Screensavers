#include "bogoSort.h"
BogoSort::BogoSort() {
    srand(time(NULL));

}

void BogoSort::reset() {
}

bool BogoSort::sortStep() {
    for (int j = 99; j > 0; j--) {
        int randIndex = rand()%j;
        int temp = toSort[j];
        toSort[j] = toSort[randIndex];
        toSort[randIndex] = temp;
    }
    for (int i = 0; i < 99; i++) {
        if (toSort[i] > toSort[i+1])
            return false;
    }
    return true;
}
