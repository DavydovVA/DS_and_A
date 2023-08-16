#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "../SQ/Queue.h"

#include <utility>

// O(d * n)

void RadixSort(int arr[], int size) {
    constexpr int digitsCount = 10;
    Queue<int> *buckets = new Queue<int>[digitsCount];

    int largestNumber {0}; // d = number of digits in greates value
    for(int i = 0; i < size; i++) {
        if (arr[i] > largestNumber) {
            largestNumber = arr[i];
        }
    }

    for(int exp = 1; largestNumber / exp > 0; exp *= 10) {
        for(int i = 0; i < size; i++) {
            buckets[(arr[i] / exp) % 10].Enqueue(arr[i]);
        }

        int index = 0;
        for(int bn = 0; bn < digitsCount; bn++) {
            while(buckets[bn].IsEmpty() == false) {
                arr[index++] = buckets[bn].Top();
                buckets[bn].Dequeue();
            }
        }
    }

    delete []buckets;
}

#endif