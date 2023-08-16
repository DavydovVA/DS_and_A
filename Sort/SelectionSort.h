#ifndef SELECTIONSORT_H
#define SELECTIONSSORT_H

#include <utility>

// O(n2)

void SelectionSort(int arr[], int size) {
    int minIndex {0};

    for(int i = 0; i < size - 1; i++) {
        minIndex = i;

        for(int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        std::swap(arr[i], arr[minIndex]);
    }
}

#endif