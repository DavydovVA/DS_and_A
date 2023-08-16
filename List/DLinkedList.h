#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "../Node.h"

#include <iostream>


template<typename T>
class DLinkedList {
private:
    int m_count;

    DNode<T> *m_head;
    DNode<T> *m_tail;

public:
    DLinkedList();

    DNode<T>* get(int index);

    void InsertHead(T value);
    void InsertTail(T value);
    void Insert(int index, T value);

    void RemoveHead();
    void RemoveTail();
    void Remove(int index);

    int Count();
    // Returns value's index, or -1
    int Search(T val);

    void PrintChain();
    void RPrintChain();

    ~DLinkedList();
};


template<typename T>
DLinkedList<T>::DLinkedList() {
    m_count = 0;

    m_head = nullptr; // TODO why do we need to init with nulls? but in Slinked we dont?
    m_tail = nullptr;
}

template<typename T>
DNode<T>* DLinkedList<T>::get(int index) {
    if (index < 0 || index >= m_count) {
        return nullptr;
    }

    DNode<T> *node = m_head;

    for(int i = 0; i < m_count; i++){
        node = node->next;
    }

    return node;
}

template<typename T>
void DLinkedList<T>::InsertHead(T value) {
    DNode<T> *node = new DNode<T>(value);

    node->next = m_head;

    if (m_head != nullptr) {
        m_head->prev = node;
    }

    m_head = node;
    if(m_count == 0) {
        m_tail = m_head;
    }

    m_count++;
}

template<typename T>
void DLinkedList<T>::InsertTail(T value) {
    if(m_count == 0) {
        InsertHead(value);
        return;
    }

    DNode<T> *node = new DNode<T>(value);

    m_tail->next = node;
    node->prev = m_tail;
    m_tail = node;

    m_count++;
}

template<typename T>
void DLinkedList<T>::Insert(int index, T value) {
    if (index < 0 || index >= m_count) {
        return;
    }

    if (index == 0) {
        InsertHead(value);
        return;
    }
    else if(index == m_count - 1) {
        InsertTail(value);
        return;
    }

    DNode<T> *node = m_head;
    for(int i = 1; i < index; i++) {
        node = node->next;
    }

    DNode<T> *newNode = new DNode<T>(value);
    newNode->prev = node;
    newNode->next = node->next;
    node->next = newNode;
    newNode->next->prev = newNode;

    m_count++;
}

template<typename T>
void DLinkedList<T>::RemoveHead() {
    if (m_count == 0) {
        return;
    }

    DNode<T> *toDel = m_head;

    m_head = m_head->next;

    delete toDel;

    if (m_head != nullptr) {
        m_head->prev = nullptr;
    }

    m_count--;
}

template<typename T>
void DLinkedList<T>::RemoveTail() {
    if (m_count == 0) {
        return;
    }
    if (m_count == 1) {
        RemoveHead();
        return;
    }

    DNode<T> *toDel = m_tail;

    m_tail = m_tail->prev;
    m_tail->next = nullptr;

    delete toDel;
    m_count--;
}

template<typename T>
void DLinkedList<T>::Remove(int index) {
    if (index < 0 || index >= m_count) {
        return;
    }
    if (index == 0) {
        RemoveHead();
        return;
    }
    if (index == m_count - 1) {
        RemoveTail();
        return;
    }

    DNode<T> *toDel = m_head;
    for(int i = 0; i < index; i++) {
        toDel = toDel->next;
    }

    toDel->prev->next = toDel->next;
    toDel->next->prev = toDel->prev;

    delete toDel;
    m_count--;
}

template<typename T>
int DLinkedList<T>::Count() {
    return m_count;
}

template<typename T>
int DLinkedList<T>::Search(T value) {
    DNode<T> *node = m_head;

    for(int i = 0; i < m_count; i++){
        if (node->value == value) {
            return i;
        }

        node = node->next;
    }

    return -1;
}

template<typename T>
void DLinkedList<T>::PrintChain() {
    DNode<T> *node = m_head;

    std::cout << " nullptr <-> "; 
    while (node !=nullptr) {
        std::cout << node->value << " <-> ";

        node = node->next;
    }

    std::cout << " nullptr\n";
}

template<typename T>
void DLinkedList<T>::RPrintChain() {
    DNode<T> *node = m_tail;

    std::cout << " nullptr <-> "; 
    while (node !=nullptr) {
        std::cout << node->value << " <-> ";

        node = node->prev;
    }

    std::cout << " nullptr\n";
}

template<typename T>
DLinkedList<T>::~DLinkedList() {
    DNode<T> *node = m_head;

    while (node != NULL)
    {
        m_head = m_head->next;
        delete node;
        node = m_head;
    }
}

#endif