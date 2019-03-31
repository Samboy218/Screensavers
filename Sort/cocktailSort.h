#ifndef COCKTAIL_H
#define COCKTAIL_H

#include "sorter.h"

class CocktailSort : public Sorter {
    public:
    CocktailSort();
    virtual bool sortStep();
    virtual void reset();
    private:
    bool direction;
    int currInd;
};

#endif
