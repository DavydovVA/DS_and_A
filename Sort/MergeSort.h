#ifndef MERGESORT_H
#define MERGESORT_H

#include <utility>

// O(n logn)

void Merge(int arr[], int startIndex, int midIndex, int endIndex) {
    int totalItems = endIndex - startIndex + 1;

    int *temp = new int[totalItems];

    int leftIndex = startIndex, rightIndex = midIndex + 1;

    int mergedIndex = 0;
    while(leftIndex <= midIndex && rightIndex <= endIndex) 
    {
        if (arr[leftIndex] < arr[rightIndex]) {
            temp[mergedIndex] = arr[leftIndex++];
        }
        else {
            temp[mergedIndex] = arr[rightIndex++];
        }

        mergedIndex++;
    }

    // If rhere is something left in left part
    while(leftIndex <= midIndex) {
        temp[mergedIndex++] = arr[leftIndex++];
    }

    // If there is something left in right part
    while(rightIndex <= endIndex) {
        temp[mergedIndex++] = arr[rightIndex++];
    }

    for(int i = 0; i < totalItems; i++) {
        arr[startIndex + i] = temp[i];
    }

    delete temp;
}


void MergeSort(int arr[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int middleIndex = (startIndex + endIndex) / 2;

        MergeSort(arr, startIndex, middleIndex);
        MergeSort(arr, middleIndex + 1, endIndex);

        Merge(arr, startIndex, middleIndex,endIndex);
    }
}

#endif