#ifndef SORTER_H
#define SORTER_H

class Sorter {
    public:
    //returns true if the array is sorted after this operation
    Sorter();
    ~Sorter();
    virtual bool sortStep() = 0;
    virtual void reset() = 0;
    int* getArray();
    void setArray(int* array);

    protected:
    int* toSort;
};

#endif
