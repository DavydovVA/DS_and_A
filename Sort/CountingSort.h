#ifndef COUNTINGSORT_H
#define COUNTINGSORT_H

#include <utility>

// O(n + k)

void CountingSort(int arr[], int size) {
    // Suppose, the spectre of possible values are [0, 9]
    int counterValue {10}; // k
    int *counter = new int[counterValue];

    for(int i = 0; i < size; i++) {
        counter[arr[i]]++;
    }

    int index {0};
    for(int i = 0; i < counterValue; i++) {
        while(counter[i]) {
            arr[index++] = i;

            counter[i]--;
        }
    }

    delete counter;
}

#endif