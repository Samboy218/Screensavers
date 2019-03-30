#ifndef MANAGER_H
#define MANAGER_H

//manages all of the arrays and sorters used
class SortManager {
    public:
    SortManager(int num_arrays, int num_sorters);
    bool stepAll();

    private:
    int** arrays;
    Sorter* sorters;
}

#endif
