#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <utility>

// O(n2) - worst, O(n logn) - best

int Partition(int arr[], int start, int end) {
    int pivot = arr[start];
    int middle = start;

    for (int i = start + 1; i <= end; i++) {
        if (arr[i] < pivot) {
            middle++;

            std::swap(arr[i], arr[middle]);
        }
    }

    std::swap(arr[start], arr[middle]);

    return middle;
}

void QuickSort(int arr[], int start, int end) {
    if (start < end) {
        int middle = Partition(arr, start, end);

        QuickSort(arr, start, middle);
        QuickSort(arr, middle + 1, end);
    }
}

#endif