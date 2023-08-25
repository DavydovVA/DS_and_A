#include "List/DLinkedList.h"
#include "SQ/Stack.h"
#include "SQ/Queue.h"
#include "SQ/Dequeue.h"
#include "Sort/BubbleSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/InsertionSort.h"
#include "Sort/MergeSort.h"
#include "Sort/QuickSort.h"
#include "Sort/CountingSort.h"
#include "Sort/RadixSort.h"
#include "Search/BinarySearch.h"
#include "Search/TernarySearch.h"
#include "Search/InterpolationSearch.h"
#include "Search/JumpSearch.h"
#include "Search/ExponentialSearch.h"
#include "Search/SublistSearch.h"
#include "String/tasks.h"

#include <cstring>

#define isP() false

bool (isP) () {
    return true;
}

void TestList() {
    DLinkedList<int> list;

    for(int i = 0; i < 15; i++) {
        list.InsertTail(i);
    }

    list.InsertHead(-1);
    list.Insert(1, 11);
    list.InsertTail(15);

    list.RemoveHead();
    list.RemoveTail();
    list.Remove(1);

    list.PrintChain();
    list.RPrintChain();

    std::cout << std::endl << list.Search(14) << std::endl;
    std::cout << list.Search(-1) << std::endl;
}

void TestStack() {
    cStack<int> stack;

    stack.PrintChain();
    for(int i = 0; i < 3; i++) {
        stack.Push(i);
        stack.PrintChain();
    }

    stack.Pop();
    stack.PrintChain();

    if (stack.IsEmpty() == false) {
        std::cout << stack.Top() << std::endl;
    }

    while (stack.IsEmpty() == false) {
        stack.Pop();
    }

    stack.PrintChain();
}

void TestQueue() {
    Queue<int> q;

    for(int i = 0; i < 14; i++) {
        q.Enqueue(i);
        q.PrintChain();
    }

    //while(q.IsEmpty() == false) {
    //    q.Dequeue();
    //    q.PrintChain();
    //}
}

void TestDequeue() {
    Dequeue<int> d;

    for (int i = 0; i < 20; i++) {
        if (i % 2 == 0) {
            d.EnqueueFront(i);
        }
        else {
            d.EnqueueBack(i);
        }

        d.PrintChain();        
    }

    int count {0};

    //while(d.IsEmpty() == false) {
    //    if (count % 2 == 0) {
    //        d.DequeueFront();
    //    }
    //    else {
    //        d.DequeueBack();
    //    }
    //    count++;

    //    d.PrintChain();
    //}
}

bool isValidPCons(char str[]) {
    int len= strlen(str);

    cStack<char> stack;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            stack.Push(str[i]);
        }
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (stack.IsEmpty() == true) {
                return false;
            }

            char c = stack.Top();

            // Difference between similar ASCII chars = { 1, 2 }
            if (str[i] - c > 2) {
                return false;
            }

            stack.Pop();
        }
    }

    return stack.IsEmpty();
}

void TestSearch(int argc, char **argv) {
if (argc < 2) {
        std::cout << "Too few arguments: should be 1 integer\n";
        return;
    }
    else if (argc > 2) {
        std::cout << "Too many arguments: should be 1 integer\n";
        return;
    }

    int value = std::atoi(argv[1]);

    int arr[] = { 7767, 84235, 5112, 424, 9, 24, 166, 6, 766, 7, 303, 0, 51, 1 };

    QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl << ExponentialSearch(arr, sizeof(arr) /sizeof(arr[0]), value) << std::endl;
}

void TestSublistSearch() {
    SNode<int> *first = new SNode<int>(1);

    SNode<int> *tmp = first;
    for (int i = 0; i < 3; i++) {
        tmp->next = new SNode<int>(i + 2);
        tmp = tmp->next;
    }

    SNode<int> *second = new SNode<int>(1);
    tmp = new SNode<int>(2);
    second->next = tmp;

    for(int i = 1; i < 4; i++) {
        tmp->next = new SNode<int>(i + 1);
        tmp = tmp->next;
    }

    std::cout << SublistSearch(first, second) << std::endl;
}

int main(int argc, char *argv[]) {
    std::string str1 = "valera aa";
    std::string str2 = "vlraeaaa";

    std::cout << isAnagram(str1, str2) << std::endl;
    std::cout << str1 << " " << str2 << std::endl;

    return 0;
}