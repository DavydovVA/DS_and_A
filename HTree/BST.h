#ifndef BST_H
#define BST_H

//#define BALANCED_TREE

#include "../Node.h"

#include <iostream>
#include <cassert>


template <typename T>
class BST {
private:
    BSTNode<T> *root;

    BSTNode<T> *Insert(BSTNode<T> *node, T key);
    void PrintTreeInOrder(BSTNode<T> *node);
    BSTNode<T> *Search(BSTNode<T> *node, T key);

    BSTNode<T> *FindMin(BSTNode<T> *node);
    BSTNode<T> *FindMax(BSTNode<T> *node);

    BSTNode<T> *Successor(BSTNode<T> *node);
    BSTNode<T> *Predcessor(BSTNode<T> *node);

    BSTNode<T> *Remove(BSTNode<T> *node, T key);

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

#ifdef BALANCED_TREE
    int GetHeight(BSTNode<T> *node);
    void UpdateHeight(BSTNode<T> *node);

    BSTNode<T> *RotateLeft(BSTNode<T> *node);
    BSTNode<T> *RotateRight(BSTNode<T> *node);

    BSTNode<T> * BalanceNode(BSTNode<T> *node);
#endif
};

template <typename T>
BST<T>::BST() {
    root = nullptr;
}

template <typename T>
BSTNode<T> *BST<T>::Insert(BSTNode<T> *node, T key) {
    // O(h), or, if scewed, O(n)
    if (node == nullptr) {
        node = new BSTNode<T>(key);

        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
#ifdef BALANCED_TREE
        node->height = 0; // balanced
#endif
    }
    else if (node->key < key) {
        node->right = Insert(node->right, key);
        node->right->parent = node;
    }
    else {
        node->left = Insert(node->left, key);
        node->left->parent = node;
    }

#ifdef BALANCED_TREE
    // balanced
    node = BalanceNode(node);

    UpdateHeight(node);
#endif

    return node;
}

template <typename T>
void BST<T>::Insert(T key) {
    root = Insert(root, key);
}

template <typename T>
void BST<T>::PrintTreeInOrder(BSTNode<T> *node) {
    if (node == nullptr) {
        return;
    }

    PrintTreeInOrder(node->left);

    std::cout << node->key << " ";

    PrintTreeInOrder(node->right);
}

template <typename T>
void BST<T>::PrintTreeInOrder() {
    PrintTreeInOrder(root);
    std::cout << std::endl;
}

template <typename T>
BSTNode<T> *BST<T>::Search(BSTNode<T> *node, T key) {
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

template <typename T>
bool BST<T>::Search(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? false : true;
}

template <typename T>
BSTNode<T> *BST<T>::FindMin(BSTNode<T> *node) {
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

template <typename T>
T BST<T>::FindMin() {
    return FindMin(root)->key;
}

template <typename T>
BSTNode<T> *BST<T>::FindMax(BSTNode<T> *node) {
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

template <typename T>
T BST<T>::FindMax() {
    return FindMax(root)->key;
}

template <typename T>
BSTNode<T> *BST<T>::Successor(BSTNode<T> *node) {
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

template <typename T>
T BST<T>::Successor(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? -1 : Successor(node)->key;
}

template <typename T>
BSTNode<T> *BST<T>::Predcessor(BSTNode<T> *node) {
    if (node->left != nullptr) {
        return FindMax(node->left);
    }

    BSTNode<T> *parent = node->parent;
    BSTNode<T> *current = node;

    while (parent != nullptr && parent->left == current) {
        current = parent;
        parent = current->parent;
    }

    return parent == nullptr ? nullptr : parent;
}

template <typename T>
T BST<T>::Predcessor(T key) {
    BSTNode<T> *node = Search(root, key);

    return node == nullptr ? -1 : Predcessor(node)->key;
}

template <typename T>
BSTNode<T> *BST<T>::Remove(BSTNode<T> *node, T key) {
    if (node == nullptr) {
        return nullptr;
    }

    // Target Node is found
    if (node->key == key) {
        // if node is a leaf
        if (node->left == nullptr && node->right == nullptr) {
            BSTNode<T> *temp = node;
            node = nullptr;

            delete temp;
        }
        // if node has only 1 child
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
    }
    else if (node->key < key) {
        node->right = Remove(node->right, key);
    }
    else {
        node->left = Remove(node->left, key);
    }

#ifdef BALANCED_TREE
    if (node != nullptr) {
        node = BalanceNode(node);

        UpdateHeight(node);
    }
#endif

    return node;
}

template <typename T>
void BST<T>::Remove(T key) {
    Remove(root, key);
}

template <typename T>
void BST<T>::DeleteTree(BSTNode<T> *node) {
    if (node->left != nullptr) {
        DeleteTree(node->left);
    }

    if (node->right != nullptr) {
        DeleteTree(node->right);
    }

    delete node;
}

template <typename T>
BST<T>::~BST(){
    if (root != nullptr) {
        DeleteTree(root);
    }
}

#ifdef BALANCED_TREE
template <typename T>
int BST<T>::GetHeight(BSTNode<T> *node) {
    return node == nullptr ? -1 : node->height;
}

template <typename T>
void BST<T>::UpdateHeight(BSTNode<T> *node) {
    node->height = std::max(
                       GetHeight(node->left),
                       GetHeight(node->right)) +
                   1;
}

template <typename T>
BSTNode<T> *BST<T>::RotateLeft(BSTNode<T> *node) {
    // The node must have a right child
    assert(node->right != nullptr);

    BSTNode<T> *balancedNode = node->right;

    balancedNode->parent = node->parent;
    node->parent = balancedNode;

    node->right = balancedNode->left;

    if (balancedNode->left != nullptr) {
        balancedNode->left->parent = node;
    }

    balancedNode->left = node;

    // Update heights
    UpdateHeight(node);
    UpdateHeight(balancedNode);

    return balancedNode;
}

template <typename T>
BSTNode<T> *BST<T>::RotateRight(BSTNode<T> *node) {
    // The node must have a left child
    assert(node->left != nullptr);

    BSTNode<T> *balancedNode = node->left;

    balancedNode->parent = node->parent;
    node->parent = balancedNode;

    node->left = balancedNode->right;

    if (balancedNode->right != nullptr) {
        balancedNode->right->parent = node;
    }

    balancedNode->right = node;

    // Update heights
    UpdateHeight(node);
    UpdateHeight(balancedNode);

    return balancedNode;
}

template <typename T>
BSTNode<T> * BST<T>::BalanceNode(BSTNode<T> *node) {
    int balance = GetHeight(node->left) - GetHeight(node->right);

    // if left heavy
    if (balance == 2) {
        int balance2 =
            GetHeight(node->left->left) - GetHeight(node->left->right);

        if (balance2 == 1) {
            node = RotateRight(node);
        }
        else {
            node->left = RotateLeft(node->left);
            node = RotateRight(node);
        }
    }
    // if right heavy
    else if (balance == -2) {
        int balance2 =
            GetHeight(node->right->left) - GetHeight(node->right->right);

        if (balance2 == -1) {
            node = RotateLeft(node);
        }
        else {
            node->right = RotateRight(node->right);
            node =  RotateLeft(node);
        }
    }

    return node;
}
#endif

#undef BALANCED_TREE

#endif