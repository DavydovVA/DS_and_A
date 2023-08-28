#ifndef BTSSDNODE_H
#define BTSSDNODE_H


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


template<typename T>
class BSTNode {
public:
    explicit BSTNode(T key) : key(key), left(nullptr), right(nullptr) {}

    T key;
    BSTNode<T> *left;
    BSTNode<T> *right;
    BSTNode<T> *parent;
};

#endif