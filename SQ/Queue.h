#ifndef QUEUE_H
#define QUEUE_H

#include "../Node.h"

#include <iostream>


template<typename T>
class Queue {
private:
    int m_count;

    SNode<T> *m_front;
    SNode<T> *m_back;

public:
    Queue();

    bool IsEmpty();

    T Top();

    void Enqueue(T value);
    void Dequeue();

    void PrintChain();

    ~Queue();

};


template<typename T>
Queue<T>::Queue() {
    m_count = 0;

    m_front = nullptr;
    m_back = nullptr;
}

template<typename T>
bool Queue<T>::IsEmpty() {
    return m_count < 1;
}

template<typename T>
T Queue<T>::Top() {
    return m_front->value;
}

template<typename T>
void Queue<T>::Enqueue(T value) {
    SNode<T> *node = new SNode<T>(value);

    if (m_count == 0) {
        m_front = node;
    }
    else {
        m_back->next = node;
    }

    m_back = node;

    m_count++;
}

template<typename T>
void Queue<T>::Dequeue() {
    if (m_count < 1) {
        return;
    }

    SNode<T> *node = m_front;

    m_front = m_front->next;

    delete node;

    m_count--;
}

template<typename T>
void Queue<T>::PrintChain() {
    SNode<T> *node = m_front;

    while(node != nullptr) {
        std:: cout << node->value << " <- ";

        node = node->next;
    }

    std::cout << "nullptr\n";
}

template<typename T>
Queue<T>::~Queue() {
    SNode<T> * node = m_front;

    while(node) {
        m_front = m_front->next;
        delete node;
        node = m_front;
    }
}

#endif