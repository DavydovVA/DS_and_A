#ifndef INTERPOLATIONSEARCH_H
#define INTERPOLATIONSEARCH_H

// O(log log n)

// Probability of error: consider searched valuetoo big (23242526),
// array's size is 10 elements, the fristone os zero, so,
// the second part of middle equation will be too big, out of array's bounds
int InterpolationSearch(int arr[], int start, int end, int value) {
    if (start <= end) {
        int middle = start + ((value - arr[start]) * (end - start) / (arr[end] - arr[start]));

        if (value == arr[middle]) {
            return middle;
        }
        else if (value < arr[middle]) {
            return InterpolationSearch(arr, start, middle - 1, value);
        }
        else {
            return InterpolationSearch(arr, middle + 1, end, value);
        }
    }

    return -1;
}

#endif