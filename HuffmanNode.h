//
// Created by hp on 11/23/2024.
//

#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H


struct HuffmanNode {
public:
    char data;       // The character stored at this node
    int freq;        // Frequency of the character
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int f) {
        data = d;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
    HuffmanNode(char d, int f, HuffmanNode* l, HuffmanNode* r) {
        data = d;
        freq = f;
        left = l;
        right = r;
    }

    // Overloading the compare operator for priority queue insertion
    bool operator>(const HuffmanNode& other) const {
        return freq > other.freq;
    }
};

#endif //HUFFMANNODE_H
