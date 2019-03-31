#ifndef BOGO_H
#define BOGO_H

#include "sorter.h"
#include <time.h>
#include <stdlib.h>

class BogoSort : public Sorter {
    public:
    BogoSort();
    virtual bool sortStep();
    virtual void reset();
};

#endif
