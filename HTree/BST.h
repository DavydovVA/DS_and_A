#ifndef BST_H
#define BST_H

#include "../Node.h"

#include <iostream>


template<typename T>
class BST {
private:
    BSTNode<T> *root;

    BSTNode<T> * Insert(BSTNode<T> *node, T key);
    void PrintTreeInOrder(BSTNode<T> *node);
    BSTNode<T> * Search(BSTNode<T> *node, T key);

    BSTNode<T> * FindMin(BSTNode<T> *node);
    BSTNode<T> * FindMax(BSTNode<T> *node);

    BSTNode<T> * Successor(BSTNode<T> *node);
    BSTNode<T> * Predcessor(BSTNode<T> *node);

    BSTNode<T> * Remove(BSTNode<T> *node, T key);

    void DeleteTree(BSTNode<T> *node);

public:
    BST();

    void Insert(T key);
    void PrintTreeInOrder();
    bool Search(T key);

    T FindMin();
    T FindMax();

    T Successor(T key);
    T Predcessor(T key);

    void Remove(T key);

    ~BST();

};


template<typename T>
BST<T>::BST() {
    root = nullptr;
}


template<typename T>
BSTNode<T> * BST<T>::Insert(BSTNode<T> *node, T key) {
    // O(h), or, if scewed, O(n)
    if (node == nullptr) {
        node = new BSTNode<T>(key);

        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
    }
    else if (node->key < key) {
        node->right = Insert(node->right, key);
        node->right->parent = node;
    }
    else {
        node->left = Insert(node->left, key);
        node->left->parent = node;
    }

    return node;
}


template<typename T>
void BST<T>::Insert(T key) {
    root = Insert(root, key);
}


template<typename T>
void BST<T>::PrintTreeInOrder(BSTNode<T> *node) {
    if (node == nullptr) {
        return;
    }

    PrintTreeInOrder(node->left);

    std::cout << node->key << " ";

    PrintTreeInOrder(node->right);
}


template<typename T>
void BST<T>::PrintTreeInOrder() {
    PrintTreeInOrder(root);
    std::cout << std::endl;
}


template<typename T>
BSTNode<T> * BST<T>::Search(BSTNode<T> *node, T key) {
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->key == key) {
        return node;
    }
    else if (node->key < key) {
        return Search(node->right, key);
    }
    else {
        return Search(node->left, key);
    }
}


template<typename T>
bool BST<T>::Search(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? false : true;
}


template<typename T>
BSTNode<T> * BST<T>::FindMin(BSTNode<T> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->left == nullptr) {
        return node;
    }
    else {
        return FindMin(node->left);
    }
}


template<typename T>
T BST<T>::FindMin() {
    return FindMin(root)->key;
}


template<typename T>
BSTNode<T> * BST<T>::FindMax(BSTNode<T> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->right == nullptr) {
        return node;
    }
    else {
        return FindMax(node->right);
    }
}


template<typename T>
T BST<T>::FindMax() {
    return FindMax(root)->key;
}


template<typename T>
BSTNode<T> * BST<T>::Successor(BSTNode<T> *node) {
    if (node->right != nullptr) {
        return FindMin(node->right);
    }

    BSTNode<T> *parent = node->parent;
    BSTNode<T> *current = node;
    while (parent != nullptr && current == parent->right) {
        current = parent;
        parent = current->parent;
    }

    return parent == nullptr ? nullptr : parent;
}


template<typename T>
T BST<T>::Successor(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? -1 : Successor(node)->key;
}


template<typename T>
BSTNode<T> * BST<T>::Predcessor(BSTNode<T> *node) {
    if (node->left != nullptr) {
        return FindMax(node->left);
    }

    BSTNode<T> *parent = node->parent;
    BSTNode<T> *current = node;

    while(parent != nullptr && parent->left == current) {
        current = parent;
        parent = current->parent;
    }

    return parent == nullptr ? nullptr : parent;
}


template<typename T>
T BST<T>::Predcessor(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? -1 : Predcessor(node)->key;
}


template<typename T>
BSTNode<T> * BST<T>::Remove(BSTNode<T> *node, T key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->key < key) {
        node->right = Remove(node->right, key);
        return node;
    }
    else if (node->key > key) {
        node->left = Remove(node->left, key);
        return node;
    }

    // Target Node is found
    // if nodeis a leaf
    if (node->left == nullptr && node->right == nullptr) {
        BSTNode<T> *temp = node;
        node = nullptr;

        delete temp;
    }
    //if node has only 1 child
    else if (node->left == nullptr) {
        node->right->parent = node->parent;

        BSTNode<T> *temp = node;
        node = node->right;

        delete temp;
    }
    else if (node->right == nullptr) {
        node->left->parent = node->parent;

        BSTNode<T> *temp = node;
        node = node->left;

        delete temp;
    }
    // if node has 2 childs
    else {
        // find successor or predecessor key
        BSTNode<T> *successor = Successor(node);
        // replace node's key with successor's key
        node->key = successor->key;
        // delete old successor's key
        node->right = Remove(node->right, successor->key);
    }

    return node;
}


template<typename T>
void BST<T>::Remove(T key) {
    Remove(root, key);
}


template<typename T>
void BST<T>::DeleteTree(BSTNode<T> *node) {
    if (node->left !=nullptr){
        DeleteTree(node->left);
    }

    if (node->right != nullptr) {
        DeleteTree(node->right);
    }

    delete node;
}


template<typename T>
BST<T>::~BST() {
    if (root !=nullptr) {
        DeleteTree(root);
    }
}


#endif