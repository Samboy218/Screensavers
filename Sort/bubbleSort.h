#ifndef BUBBLE_H
#define BUBBLE_H

#include "sorter.h"

class BubbleSort : public Sorter {
    public:
    BubbleSort();
    virtual bool sortStep();
    private:
    int currInd;
};

#endif
