#ifndef INSERTION_H
#define INSERTION_H

#include "sorter.h"

class InsertionSort : public Sorter {
    public:
    InsertionSort();
    virtual bool sortStep();
    virtual void reset();
    private:
    int currHead;
    int currInd;
    int currVal;
};

#endif
