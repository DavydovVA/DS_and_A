#ifndef SUBLISTSEARCH_H
#define SUBLISTSEARCH_H

#include "../Node.h"

// O(M * N)

bool SublistSearch(SNode<int> *first, SNode<int> *second) { 
    if (first == nullptr && second == nullptr) {
        return true;
    }
    if (first == nullptr || second == nullptr) {
        return false;
    }

    SNode<int> *ptr1 = first, *ptr2 = second;
    while(second != nullptr) {
        ptr2 = second;

        while (ptr1 != nullptr) {
            if (ptr2 == nullptr) {
                return false;
            }
            else if (ptr1->value == ptr2->value) 
            {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            else {
                break;
            }
        }
        if (ptr1 == nullptr) {
            return true;
        }

        ptr1 = first;
        second = second->next;
    }

    return false;
}

#endif