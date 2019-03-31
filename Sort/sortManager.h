#ifndef MANAGER_H
#define MANAGER_H

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bubbleSort.h"
#include "sorter.h"
//manages all of the arrays and sorters used
class SortManager {
    public:
    SortManager(int num_arrays, int width, int height);
    bool stepAll();
    void setSorter(int index, Sorter* sorter);
    void drawArrays(Display *dpy, Window &root, GC &g, XColor* colors);
    void drawAll(Display *dpy, Window &root, GC &g, XColor* colors);
    void shuffleAll();


    private:
    int** arrays;
    Sorter** sorters;
    bool* done;
    int numArrays;
    int cell_w;
    int cell_h;
};

#endif
