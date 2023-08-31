#ifndef OATHASH_H
#define OATHASH_H

// Open addressing technique

#define HASH_TABLE_SIZE 7

#include <string>
#include <iostream>


class HashElement {
public:
    int key;
    std::string value;
    HashElement(int key, std::string value) {
        this->key = key;
        this->value = std::move(value);
    }
};


class OATHash {
private:
    int currnetSize;
    HashElement * *hashTable;
    HashElement *deleted;

    int HashFunction(int key) {
        return key % HASH_TABLE_SIZE;
    }

public:
    OATHash();

    void Insert(int key, std::string value);
    void Delete(int key);
    std::string Search(int key);
    bool isEmpty();

    void PrintHashTable();

    ~OATHash();

};


OATHash::OATHash() {
    currnetSize = 0;

    hashTable = new HashElement * [HASH_TABLE_SIZE];

    deleted = new HashElement(-1, "");
}


void OATHash::Insert(int key, std::string value) {
    if (currnetSize >= HASH_TABLE_SIZE) {
        return;
    }

    int index = HashFunction(key);

    // Find next free space using
    // linear probing
    while(hashTable[index] != nullptr &&
        hashTable[index]->key != key &&
        hashTable[index]->key != deleted->key)
    {
        ++index;
        index %= HASH_TABLE_SIZE;
    }

    if (hashTable[index] == nullptr ||
        hashTable[index]->key == deleted->key)
    {
        ++currnetSize;
        hashTable[index] = new HashElement(key, value);
    }
}


void OATHash::Delete(int key) {
    int index = HashFunction(key);

    while(hashTable[index] != nullptr &&
        hashTable[index]->key != deleted->key)
    {
        if (hashTable[index]->key == key) {
            --currnetSize;

            delete hashTable[index];
            hashTable[index] = deleted;

            return;
        }

        // linear probing
        ++index;
        index %= HASH_TABLE_SIZE;
    }
}


std::string OATHash::Search(int key) {
    int index = HashFunction(key);

    while(hashTable[index] != nullptr &&
        hashTable[index]->key != deleted->key)
    {
        if (hashTable[index]->key == key) {
            return hashTable[index]->value;
        }

        ++index;
        index %= HASH_TABLE_SIZE;
    }

    return "";
}


bool OATHash::isEmpty() {
    return currnetSize == 0;
}


void OATHash::PrintHashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable[i] != nullptr &&
            hashTable[i]->key != deleted->key)
        {
            std::cout << i << std::endl;
            std::cout << hashTable[i]->key << std::endl;
            std::cout << hashTable[i]->value << std::endl;
            std::cout << std::endl;
        }
    }
}


OATHash::~OATHash() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable[i] == nullptr ||
            hashTable[i] == deleted)
        {
            continue;
        }

        delete hashTable[i];
    }

    delete[]hashTable;

    delete deleted;
}

#endif