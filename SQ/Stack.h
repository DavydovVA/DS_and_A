#ifndef STACK_H
#define STACK_H

#include "../Node.h"

#include <iostream>


template<typename T>
class cStack {
private:
    int m_count;

    SNode<T> *m_tail;

public:
    cStack();

    T Top();
    void Pop();
    void Push(T value);

    bool IsEmpty();

    void PrintChain();

    ~cStack();

};

template<typename T>
cStack<T>::cStack() {
    m_count = 0;

    m_tail = nullptr;
}

template<typename T>
T cStack<T>::Top() {
    return m_tail->value;
}

template<typename T>
void cStack<T>::Pop() {
    if (IsEmpty()) {
        return;
    }

    SNode<T> *toPop = m_tail;
    m_tail = m_tail->next;
    delete toPop;

    m_count--;
}

template<typename T>
void cStack<T>::Push(T value) {
    SNode<T> *node = new SNode<T>(value);

    node->next = m_tail;
    m_tail = node;

    m_count++;
}

template<typename T>
bool cStack<T>::IsEmpty() {
    return m_count < 1;
}

template<typename T>
void cStack<T>::PrintChain() {
    SNode<T> *node = m_tail;

    while(node) {
        std::cout << node->value << " -> ";
        node = node->next;
    }

    std::cout << "nullptr\n";
}

template<typename T>
cStack<T>::~cStack() {
    SNode<T> *node = m_tail;

    while(node) {
        m_tail = m_tail->next;
        delete node;
        node = m_tail;
    }
}

#endif