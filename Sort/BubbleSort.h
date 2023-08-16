#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <utility>

// O(n2)

void BubbleSort(int arr[], int size) {
    bool isSwapped = true;

    int unsortedSize = size;
    do {
        isSwapped = false;

        for(int i = 0; i < unsortedSize - 1; i++){
            if(arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }

        unsortedSize--;

    } while(isSwapped == true);
}

#endif