//
// Created by hp on 11/23/2024.
//

#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

// Node structure for Huffman tree
struct HuffmanNode {
public:
    char data;       // The character stored at this node
    int freq;        // Frequency of the character
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(char data, int freq, HuffmanNode* l, HuffmanNode* r) : data(data), freq(freq), left(l), right(r) {}

    // Compare function for priority queue
    bool operator>(const HuffmanNode& other) const {
        return freq > other.freq;
    }
};

#endif //HUFFMANNODE_H
