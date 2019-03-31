#ifndef SORTER_H
#define SORTER_H

class Sorter {
    public:
    //returns true if the array is sorted after this operation
    virtual bool sortStep() = 0;
    int* getArray();
    void setArray(int* array);

    protected:
    int* toSort;
};

#endif
