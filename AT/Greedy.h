#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <iostream>
#include <queue>


void MinimalChangeCoin(double changingValue) {
    constexpr double denom[] = { 0.01, 0.05, 0.10, 0.25, 1, 2, 5, 10, 20, 50, 100 };

    // result as vector
    std::vector<double> result;

    for (int i = sizeof(denom) / sizeof(denom[0]) - 1; i >= 0; i--) {
        while (changingValue >= denom[i]) {
            changingValue -= denom[i];
            result.push_back(denom[i]);
        }

        if (changingValue < denom[0]) {
            break;
        }
    }

    for(const auto& el : result) {
        std::cout << el << std::endl;
    }
}


namespace HuffmanCode {
    // The most frequent character will have the smallest
    // code and the least frequent character will be the
    // largest code. Thе variable length codes аѕѕіgnеd tо
    // іnрut сhаrасtеrѕ are prеfіx codes.
    // There are mаіnlу twо mаjоr parts іn Huffmаn cоdіng:
    // building a Huffman tree from input characters and
    // traversing thе Huffmаn trее and аѕѕіgning codes tо сhаrасtеrѕ.

    class MinHeapNode {
    public:
        char data;
        int frequency;
        MinHeapNode *left;
        MinHeapNode *right;

        MinHeapNode(char data, int freq) {
            this->data = data;
            frequency = freq;
            left = nullptr;
            right = nullptr;
        }
    };

    void PrintMHT(MinHeapNode * root, std::string str)
    {
        if (!root)
            return;

        if (root->data != '$')
        {
            std::cout << root->data << ": ";
            std::cout << str << std::endl;
        }

        PrintMHT(root->left, str + "0");
        PrintMHT(root->right, str + "1");
    }

    void MHTDestructor(MinHeapNode *root) {
        if (root == nullptr) {
            return;
        }

        if (root->left) {
            MHTDestructor(root->left);
        }

        if (root->right) {
            MHTDestructor(root->right);
        }

        delete root;
    }

    void HuffmanCode(char chs[], int freqs[], int size) {
        auto compare = [] (MinHeapNode* left, MinHeapNode*right) {
            return left->frequency > right->frequency;
        };

        std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, decltype(compare)> minHeap(compare);

        for (int i = 0; i < size; i++){
            minHeap.push(new MinHeapNode(chs[i], freqs[i]));
        }

        while(minHeap.size() != 1) {
            auto left = minHeap.top();
            minHeap.pop();
            auto right = minHeap.top();
            minHeap.pop();

            MinHeapNode *temp = new MinHeapNode('$', left->frequency + right->frequency);
            temp->left = left;
            temp->right = right;

            minHeap.push(temp);
        }

        PrintMHT(minHeap.top(), "");
        MHTDestructor(minHeap.top());
    }
}

#endif