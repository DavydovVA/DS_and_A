#ifndef TERNARYSEARCH_H
#define TERNARYSEARCH_H

// O(log3n)

int RTernarySearch(int arr[], int start, int end, int value) {
    if (start <= end) {
        int middleLeft = start + (end - start) / 3;
        int middleRight = middleLeft + (end - start) / 3;

        if (value == arr[middleLeft]) {
            return middleLeft;
        }
        else if (value == arr[middleRight]) {
            return middleRight;
        }
        else if (value < arr[middleLeft]) {
            return RTernarySearch(arr, start, middleLeft, value);
        }
        else if (value > arr[middleRight]) {
            return RTernarySearch(arr, middleRight + 1, end,value);
        }
        else {
            return RTernarySearch(arr, middleLeft + 1, middleRight, value);
        }
    }

    return -1;
}

int ITernarySearch(int arr[], int size, int value) {
    int start = 0, midL = 0, midR = 0, end = size - 1;

    while (start <= end) {
        midL = start + (end - start) / 3;
        midR = midL + (end - start) / 3;

        if (value == arr[midL]) {
            return midL;
        }
        else if (value == arr[midR]) {
            return midR;
        }
        else if (value < arr[midL]) {
            end = midL - 1;
        }
        else if (value > arr[midR]) {
            start = midR + 1;
        }
        else {
            start = midL + 1;
            end = midR - 1;
        }
    }

    return -1;
}


#endif