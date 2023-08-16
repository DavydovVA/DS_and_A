#ifndef DEQUEUE_H
#define DEQUEUE_H

#include "../Node.h"

#include <iostream>


template<typename T>
class Dequeue {
private:
    int m_count;

    DNode<T> *m_front;
    DNode<T> *m_back;

public:
    Dequeue();

    T Front();
    void EnqueueFront(T value);
    void DequeueFront();

    T Back();
    void EnqueueBack(T value);
    void DequeueBack();


    bool IsEmpty();
    void PrintChain();

    ~Dequeue();
};


template<typename T>
Dequeue<T>::Dequeue() {
    m_count = 0;

    m_front = nullptr;
    m_back = nullptr;
}

template<typename T>
T Dequeue<T>::Front() {
    return m_front->value;
}

template<typename T>
void Dequeue<T>::EnqueueFront(T value) {
    if (m_count == 0) {
        EnqueueBack(value);
        return;
    }

    DNode<T> *node = new DNode<T>(value);

    node->next = m_front;
    m_front->prev = node;
    m_front = node;

    m_count++;
}

template<typename T>
void Dequeue<T>::DequeueFront() {
    if (m_count < 1) {
        return;
    }

    DNode<T> *node = m_front;

    m_front = m_front->next;

    delete node;

    if (m_front != nullptr) {
        m_front->prev = nullptr;
    }

    m_count--;
}

template<typename T>
T Dequeue<T>::Back() {
    return m_back->value;
}

template<typename T>
void Dequeue<T>::EnqueueBack(T value) {
    DNode<T> *node = new DNode<T>(value);

    if (m_count == 0) {
        m_front = node;
    }
    else {
        m_back->next = node;
        node->prev = m_back;
    }

    m_back = node;

    m_count++;
}

template<typename T>
void Dequeue<T>::DequeueBack() {
    if (m_count == 0) {
        return;
    }
    if (m_count == 1) {
        DequeueFront();
        return;
    }

    DNode<T> *node = m_back;

    m_back = m_back->prev;
    m_back->next = nullptr;

    delete node;

    m_count--;
}

template<typename T>
bool Dequeue<T>::IsEmpty() {
    return m_count < 1;
}

template<typename T>
void Dequeue<T>::PrintChain() {
    DNode<T> *node = m_front;

    std::cout << "nullptr <-> ";
    while(node != nullptr) {
        std::cout << node->value << " <-> ";
        node = node->next;
    }

    std::cout << "nullptr\n";
}

template<typename T>
Dequeue<T>::~Dequeue() {
    DNode<T> *node = m_front;

    while(node != nullptr) {
        m_front = m_front->next;
        delete node;
        node =m_front;
    }
}

#endif