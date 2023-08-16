#ifndef SDNODE_H
#define SDNODE_H


template<typename T>
class SNode {
public:
    SNode(T value) : value(value), next(nullptr) {}

    T value;
    SNode<T> *next;
};
template<typename T>
class DNode {
public:
    DNode(T value) : value(value), prev(nullptr), next(nullptr) {}

    T value;
    DNode<T> *prev;
    DNode<T> *next;
};

#endif