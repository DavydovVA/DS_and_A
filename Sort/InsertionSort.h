#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <utility>

// O(n)

void InsertionSort(int arr[], int size) {
    int refValue {0};

    for(int i = 0; i < size; i++) {
        refValue = arr[i];

        int j;
        for(j = i - 1; j >= 0; j--) {
            if (arr[j] > refValue) {
                arr[j + 1] = arr[j];
            }
            else {
                break;
            }
        }

        arr[j + 1] = refValue;
    }
}



#endif