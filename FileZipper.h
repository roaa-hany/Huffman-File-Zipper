//
// Created by hp on 11/23/2024.
//

#ifndef FILEZIPPER_H
#define FILEZIPPER_H

#include <string>
#include "HuffmanTree.h"
#include "priority_queue.h"
#include "LinkedList.h"

class FileZipper {
private:
    LinkedList frequencies; // Linked list to store character frequencies
    LinkedList codes;       // Linked list to store Huffman codes

    void buildFrequencyTable(const string& filename);
    void buildHuffmanCodes(HuffmanNode* root, const string& code);

public:
    FileZipper();
    void compress(const string& inputFilename, const string& compressedFilename);
    void decompress(const string& compressedFilename, const string& outputFilename);
};

#endif // FILEZIPPER_H
