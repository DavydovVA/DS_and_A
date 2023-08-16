#ifndef SLinkedList_H
#define SLinkedList_H

#include "../Node.h"

#include <iostream>


template<typename T>
class SLinkedList {
private:
    int m_count;

    SNode<T> *m_head;
    SNode<T> *m_tail;

public:
    SLinkedList();

    SNode<T>* get(int index);

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

    ~SLinkedList();
};


template<typename T>
SLinkedList<T>::SLinkedList() {
    m_count = 0;
}

template<typename T>
SNode<T>* SLinkedList<T>::get(int index) {
    if (index < 0 || index >= m_count) {
        return nullptr;
    }

    SNode<T> *node = m_head;

    for(int i = 0; i < m_count; i++){
        node = node->next;
    }

    return node;
}

template<typename T>
void SLinkedList<T>::InsertHead(T value) {
    SNode<T> *node = new SNode<T>(value);

    node->next = m_head;

    m_head = node;

    if (m_count == 0) {
        m_tail = m_head;
    }

    m_count++;
}

template<typename T>
void SLinkedList<T>::InsertTail(T value) {
    if (m_count == 0) {
        InsertHead(value);
        return;
    }

    SNode<T> *node = new SNode<T>(value);

    m_tail->next = node;
    m_tail = node;

    m_count++;
}

template<typename T>
void SLinkedList<T>::Insert(int index, T value) {
    if (index < 0 || index >= m_count) {
        return;
    }

    if (index == 0) {
        InsertTail(value);
        return;
    }
    if (index == m_count - 1) {
        InsertTail(value);
        return;
    }

    SNode<T> *newNode = new SNode<T>(value);

    SNode<T> *node = m_head;
    for(int i = 0; i < index; i++) {
        node = node->next;
    }

    newNode->next = node->next;
    node->next = newNode;

    m_count++;
}

template<typename T>
void SLinkedList<T>::RemoveHead() {
    if (m_count == 0) {
        return;
    }

    SNode<T> *node = m_head;

    m_head = m_head->next;

    delete node;

    m_count--;
}

template<typename T>
void SLinkedList<T>::RemoveTail() {
    if (m_count == 0) {
        return;
    }
    if(m_count == 1) {
        RemoveHead();
        return;
    }

    SNode<T> *node = m_head;
    while(node->next->next != nullptr) {
        node = node->next;
    }

    SNode<T> *tail = node->next;
    node->next = nullptr;
    m_tail = node;

    delete tail;

    m_count--;
}

template<typename T>
void SLinkedList<T>::Remove(int index) {
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

    SNode<T> *node = m_head;
    for (int i = 1; i < index; i++) {
        node = node->next;
    }

    SNode<T> *toDel = node->next;
    node->next = toDel->next;

    delete toDel;

    m_count--;
}

template<typename T>
int SLinkedList<T>::Count() {
    return m_count;
}

template<typename T>
int SLinkedList<T>::Search(T value) {
    SNode<T> *node = m_head;

    for(int i = 0; i < m_count; i++){
        if (node->value == value) {
            return i;
        }

        node = node->next;
    }

    return -1;
}

template<typename T>
void SLinkedList<T>::PrintChain() {
    SNode<T> *node = m_head;

    while (node !=nullptr) {
        std::cout << node->value << " -> ";

        node = node->next;
    }

    std::cout << " nullptr\n";
}

template<typename T>
SLinkedList<T>::~SLinkedList() {
    SNode<T> *node = m_head;

    while (node != NULL)
    {
        m_head =m_head->next;
        delete temp;
        node = m_head;
    }
}

#endif