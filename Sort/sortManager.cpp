#include "sortManager.h"

SortManager::SortManager(int num_arrays, int width, int height) {
    srandom(time(NULL));
    numArrays = num_arrays;
    cell_w = width/numArrays;
    cell_h = height/100;
    arrays = (int **)malloc(sizeof(int*)*num_arrays);
    for (int i = 0; i < num_arrays; i++) {
        arrays[i] = (int*)malloc(sizeof(int)*100);
        for (int j = 0; j < 100; j++) {
            arrays[i][j] = j;
        }
    }
    sorters = (Sorter **)malloc(sizeof(Sorter*)*num_arrays);
}

//returns true if all arrays are sorted
bool SortManager::stepAll() {
    bool isDone = true;
    for (int i = 0; i < numArrays; i++) {
        //printf("taking a step on %d\n", i);
        if (!sorters[i]->sortStep())
            isDone = false;
    }
    return isDone;
}

void SortManager::drawArrays(Display *dpy, Window &root, GC &g, XColor* colors) {
    for (int i = 0; i < numArrays; i++) {
        int* curr = sorters[i]->getArray();
        for (int j = 0; j < 100; j++) {
            //printf("curr: %d\n", curr[j]);
            XSetForeground(dpy, g, colors[curr[j]].pixel);
            XFillRectangle(dpy, root, g, i*cell_w, j*cell_h, cell_w, cell_h);
        }
    }
}

void SortManager::setSorter(int index, Sorter* sorter) {
    sorters[index] = sorter;
    sorters[index]->setArray(arrays[index]);
}


void SortManager::shuffleAll() {
    for (int i = 0; i < numArrays; i++) {
        for (int j = 99; j > 0; j--) {
            int randIndex = rand()%j;
            int temp = arrays[i][j];
            arrays[i][j] = arrays[i][randIndex];
            arrays[i][randIndex] = temp;
        }
    }
}
