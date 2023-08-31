#ifndef SSTHASH_H
#define SSTHASH_H

// Separate chaining technique

#include <list>
#include <string>

#define HASH_TABLE_SIZE 7


class SSTHash {
private:
    std::list<std::pair<int, std::string>> hashTable[HASH_TABLE_SIZE];

    int HashFunction(int key) {
        return key % HASH_TABLE_SIZE;
    }

public:
    SSTHash() {}

    void Insert(int key, std::string value);
    void Delete(int key);
    std::string Search(int key);
    bool isEmpty();
};


void SSTHash::Insert(int key, std::string value) {
    int index = HashFunction(key);
    bool isExists { false };

    for(auto &pair : hashTable[index]) {
        if (pair.first == key) {
            pair.second = std::move(value);
            isExists = true;
        }
    }

    if (isExists == false){
        hashTable[index].emplace_back(key, value);
    }
}


void SSTHash::Delete(int key) {
    int index = HashFunction(key);

    auto &cell = hashTable[index];
    for(auto it = cell.begin(); it != cell.end(); it++) {
        if (it->first == key) {
            cell.erase(it);
            break;
        }
    }
}


std::string SSTHash::Search(int key) {
    int index = HashFunction(key);

    for(const auto &pair : hashTable[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }

    return "";
}


bool SSTHash::isEmpty() {
    for (const auto &cell : hashTable) {
        if (cell.size() > 0) {
            return false;
        }
    }

    return true;
}


#endif