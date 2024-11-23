//
// Created by hp on 11/23/2024.
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "priority_queue.h"
#include "LinkedList.h"
#include "HuffmanNode.h"
#include <vector>
#include <string>

// Huffman Tree class
class HuffmanTree {
private:
    HuffmanNode* root;

public:
    HuffmanTree();
    void buildTree(priority_queue& minHeap);
    void decodeTree(const LinkedList& frequencies);
    void generateCodes(HuffmanNode* node, string str, vector<pair<char, string>>& codes);
    HuffmanNode* getRoot() const;
};

#endif // HUFFMANTREE_H
