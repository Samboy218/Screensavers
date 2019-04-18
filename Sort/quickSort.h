#ifndef QUICK_H
#define QUICK_H

#include "sorter.h"
#include <stack>
#include <array>
#include "stdio.h"

class QuickSort : public Sorter {
    public:
    QuickSort();
    virtual bool sortStep();
    virtual void reset();
    private:
    std::stack<int*>* partStack;
    int i;
    int j;
    int pivot;
};

#endif
