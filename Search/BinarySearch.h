#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

// O(log n)

int RBianrySearch(int arr[], int start, int end, int value) {
    if (start <= end) {
        int middle = start + (end - start) / 2;

        if(value == arr[middle]) {
            return middle;
        }
        else if (value < arr[middle]) {
            return RBianrySearch(arr, start, middle - 1, value);
        }
        else {
            return RBianrySearch(arr, middle + 1, end, value);
        }
    }

    return -1;
}

int IBinarySearch(int arr[], int size, int value) {
    int start = 0, end = size - 1, middle = 0;

    while (start <= end) {
        middle = start + (end -start) / 2;

        if (value == arr[middle]) {
            return middle;
        }
        else if (value < arr[middle]) {
            end = middle - 1;
        }
        else {
            start = middle + 1;
        }
    }

    return -1;
}

#endif