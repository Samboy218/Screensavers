#include "sorter.h"

Sorter::Sorter() {
    toSort = new int[100];
}
Sorter::~Sorter() {
    delete[] toSort;
}

int* Sorter::getArray() {
    return toSort;
}

void Sorter::setArray(int* array) {
    for (int i = 0; i < 100; i++) {
        toSort[i] = array[i];
    }
}
