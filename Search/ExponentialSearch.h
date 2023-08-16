#ifndef EXPONENTIALSEARCH_H
#define EXPONENTIALSEARCH_H

#include "BinarySearch.h"

#include <cmath>

// O(log n)

int ExponentialSearch(int arr[], int size, int value) {
    if (size <= 0) {
        return -1;
    }

    int block {1};

    while (block < size &&arr[block] < value) {
        block *= 2;
    }

    return RBianrySearch(arr, block / 2, std::min(block, size), value);
}



#endif