#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H


int LinearSearch(int arr[], int size, int value) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == value) {
            return i;
        }
    }

    return -1;
}

#endif