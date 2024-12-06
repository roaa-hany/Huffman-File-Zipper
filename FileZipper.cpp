#include "FileZipper.h"
#include "LinkedList.h"
#include "HuffmanTree.h"
#include "priority_queue.h"
#include "HuffmanNode.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <stdexcept>
using namespace std;

// Encryption key
string ENCRYPTION_KEY = "FileZipper";

FileZipper::FileZipper() {}

// XOR Encryption/Decryption function
void FileZipper::encryptDecryptFile(const string& filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file for encryption/decryption." << endl;
        return;
    }

    char ch;
    size_t keyIndex = 0;

    while (file.get(ch)) {
        file.seekp(static_cast<streamoff>(file.tellg()) - 1); // Move back to the character position
        file.put(ch ^ ENCRYPTION_KEY[keyIndex]); // XOR with the encryption key
        keyIndex = (keyIndex + 1) % ENCRYPTION_KEY.size(); // Cycle through the key
    }

    file.close();
}

void FileZipper::buildFrequencyTable(const string& filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    char ch;
    int charFrequencies[256] = {0};

    while (inFile.get(ch)) {
        charFrequencies[static_cast<unsigned char>(ch)]++;
    }

    inFile.close();

    for (int i = 0; i < 256; ++i) {
        if (charFrequencies[i] > 0) {
            frequencies.insert(static_cast<char>(i), to_string(charFrequencies[i]));
        }
    }
}

void FileZipper::buildHuffmanCodes(HuffmanNode* root, const string& code) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes.insert(root->data, code);
    }

    buildHuffmanCodes(root->left, code + "0");
    buildHuffmanCodes(root->right, code + "1");
}

void FileZipper::compress(const string& inputFilename, const string& compressedFilename) {
    // Build frequency table
    buildFrequencyTable(inputFilename);

    // Create priority queue and build Huffman tree
    priority_queue pq;

    for (int i = 0; i < 256; ++i) {
        string freqStr = frequencies.find(static_cast<char>(i));
        if (!freqStr.empty()) {
            pq.insert(new HuffmanNode(static_cast<char>(i), stoi(freqStr)));
        }
    }

    HuffmanTree huffmanTree;
    huffmanTree.buildTree(pq);

    // Generate Huffman codes
    buildHuffmanCodes(huffmanTree.getRoot(), "");

    // Write compressed data to file
    ifstream inFile(inputFilename, ios::binary);
    ofstream outFile(compressedFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    string bitString;
    char ch;
    while (inFile.get(ch)) {
        string code = codes.find(static_cast<unsigned char>(ch));
        if (code.empty()) {
            cerr << "Error: Huffman code for character '" << ch << "' not found." << endl;
            return;
        }
        bitString += code;
    }

    // Calculate padding and write it to the file
    int paddingBits = 8 - (bitString.size() % 8);
    if (paddingBits != 8) {
        bitString.append(paddingBits, '0');
    }
    outFile.put(static_cast<char>(paddingBits)); // Store padding bits at the start

    // Write compressed (binary) data
    for (size_t i = 0; i < bitString.size(); i += 8) {
        string byteStr = bitString.substr(i, 8);
        bitset<8> byte(byteStr);
        outFile.put(static_cast<char>(byte.to_ulong()));
    }

    inFile.close();
    outFile.close();

    // Encrypt the compressed file
    encryptDecryptFile(compressedFilename);
}

void FileZipper::decompress(const string& compressedFilename, const string& outputFilename) {
    // Decrypt the compressed file
    encryptDecryptFile(compressedFilename);

    ifstream inFile(compressedFilename, ios::binary);
    ofstream outFile(outputFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    // Read padding bits
    char paddingBitsChar;
    inFile.get(paddingBitsChar);
    int paddingBits = static_cast<int>(paddingBitsChar);

    string bitString;
    char byte;
    while (inFile.get(byte)) {
        bitString += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }

    // Remove padding bits from the bitstring
    if (paddingBits > 0 && paddingBits <= 8) {
        bitString = bitString.substr(0, bitString.size() - paddingBits);
    } else {
        cerr << "Error: Invalid padding bits value." << endl;
        return;
    }

    HuffmanTree huffmanTree;
    huffmanTree.decodeTree(frequencies);

    HuffmanNode* currentNode = huffmanTree.getRoot();

    for (char bit : bitString) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (!currentNode->left && !currentNode->right) {
            outFile.put(currentNode->data);
            currentNode = huffmanTree.getRoot();
        }
    }

    inFile.close();
    outFile.close();
}
