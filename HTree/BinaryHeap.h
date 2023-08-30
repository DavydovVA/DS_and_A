#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <climits>
#include <iostream>


// Binary tree used to implement priority queue
// Implementation of Min MinBinaryHeap
class MinBinaryHeap {
private:
    int *vect;
    int capacity;
    int heapSize;

    int parent(int index) { return (index - 1) / 2; }
    int left(int index) { return (index * 2) + 1; }
    int right(int index) { return (index * 2) + 2; }

    void FixHeapProperty(int index);

public:
    MinBinaryHeap();

    // insert new key
    void InsertKey(int key);
    // deletes key stored at at index
    void DeleteKey(int index);
    // removes the minimum element (root element)
    int ExtractMin();
    // decreases the key value of key at index to newKey value
    void DecreaseKey(int index, int newKey);
    // to heapify a subtree with the root at given index
    void MinHeapify(int index);

    // returns the root element
    int GetMin() { return vect[0]; }

    ~MinBinaryHeap();

};


MinBinaryHeap::MinBinaryHeap() {
    heapSize = 0;
    capacity = 20;
    vect = new int[capacity];
}


void MinBinaryHeap::FixHeapProperty(int index) {
    // Fix the min heap property, if violated
    while(index != 0 && vect[parent(index)] > vect[index]) {
        std::swap(vect[parent(index)], vect[index]);
        index = parent(index);
    }
}


void MinBinaryHeap::InsertKey(int key) {
    // insert new key
    int index = ++heapSize - 1;
    vect[index] = key;

    FixHeapProperty(index);
}


void MinBinaryHeap::DecreaseKey(int index, int newKey) {
    vect[index] = newKey;

    FixHeapProperty(index);
}


int MinBinaryHeap::ExtractMin() {
    if (heapSize <= 0) {
        return INT_MAX;
    }
    else if (heapSize == 1) {
        heapSize--;
        return vect[0];
    }

    int root = vect[0];
    vect[0] = vect[heapSize -1];
    --heapSize;
    MinHeapify(0);

    return root;
}


void MinBinaryHeap::DeleteKey(int index) {
    DecreaseKey(index, INT_MIN);
    ExtractMin();
}


void MinBinaryHeap::MinHeapify(int index) {
    // A recursive method to heapify a subtree with the root at given index
    // This method assumes that the subtrees are already heapified
    int l = left(index);
    int r = right(index);
    int smallest = index;

    if (l < heapSize && vect[l] < vect[index]) {
        smallest = l;
    }
    if (r < heapSize && vect[r] < vect[smallest])
    {
        smallest = r;
    }

    if (smallest != index) {
        std::swap(vect[index], vect[smallest]);
        MinHeapify(smallest);
    }
}


MinBinaryHeap::~MinBinaryHeap() {
    delete[]vect;
}


#endif