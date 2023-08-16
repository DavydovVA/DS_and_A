#ifndef JUMPSEARCH_H
#define JUMPSEARCH_H

#include <cmath>

// O(sqrt n)

int JumpSearch(int arr[], int size, int value) {
    if (size <= 0) {
        return -1;
    }

    int step = static_cast<int>(std::sqrt(static_cast<double>(size)));

    // Find a correct block
    const int s = size % step;
    for(int block = size - (s ? s : step); block >= 0; block -= step) {
        if (arr[block] <= value) {
            // Linear Search in block
            for(int j = block; j < block + step && j < size; j++) {
                if (arr[j] == value) {
                    return j;
                }
            }
        }
    }

    return -1;
}

#endif