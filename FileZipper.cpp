#include "FileZipper.h"
#include "LinkedList.h"
#include "HuffmanTree.h"
#include "priority_queue.h"
#include "HuffmanNode.h"
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

// Encryption key used for XOR-based encryption/decryption
string ENCRYPTION_KEY = "FileZipper";

// Constructor for FileZipper class
FileZipper::FileZipper() {}

// XOR Encryption/Decryption function
// This function will read the file and XOR each byte with the encryption key.
void FileZipper::encryptDecryptFile(const string& filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file for encryption/decryption." << endl;
        return;
    }

    char ch;
    size_t keyIndex = 0;

    // Read the file byte by byte
    while (file.get(ch)) {
        // Move back to the character position and perform XOR with the encryption key
        file.seekp(static_cast<streamoff>(file.tellg()) - 1);
        file.put(ch ^ ENCRYPTION_KEY[keyIndex]);

        // Cycle through the encryption key
        keyIndex = (keyIndex + 1) % ENCRYPTION_KEY.size();
    }

    file.close();
}

// Function to build the frequency table from the input file
void FileZipper::buildFrequencyTable(const string& filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    char ch;
    int charFrequencies[256] = {0}; // Array to hold frequency of each byte (0-255)

    // Count the frequency of each byte in the file
    while (inFile.get(ch)) {
        charFrequencies[static_cast<unsigned char>(ch)]++;
    }

    inFile.close();

    // Insert the characters with non-zero frequencies into the frequency map
    for (int i = 0; i < 256; ++i) {
        if (charFrequencies[i] > 0) {
            frequencies.insert(static_cast<char>(i), to_string(charFrequencies[i]));
        }
    }
}

// Recursive function to generate Huffman codes for each character
void FileZipper::buildHuffmanCodes(HuffmanNode* root, const string& code) {
    if (!root) return;

    // If the node is a leaf node, insert the character and its code into the map
    if (!root->left && !root->right) {
        codes.insert(root->data, code);
    }

    // Recursively build codes for left and right child nodes
    buildHuffmanCodes(root->left, code + "0");
    buildHuffmanCodes(root->right, code + "1");
}

// Function to compress the input file using Huffman coding and store the result in the output file
void FileZipper::compress(const string& inputFilename, const string& compressedFilename) {
    // Build the frequency table for the input file
    buildFrequencyTable(inputFilename);

    // Create a priority queue and build the Huffman tree
    priority_queue pq;

    // Add nodes for each character with non-zero frequency to the priority queue
    for (int i = 0; i < 256; ++i) {
        string freqStr = frequencies.find(static_cast<char>(i));
        if (!freqStr.empty()) {
            pq.insert(new HuffmanNode(static_cast<char>(i), stoi(freqStr)));
        }
    }

    HuffmanTree huffmanTree;
    huffmanTree.buildTree(pq); // Build the Huffman tree from the priority queue

    // Generate Huffman codes for each character based on the Huffman tree
    buildHuffmanCodes(huffmanTree.getRoot(), "");

    // Open the input and output files for reading and writing
    ifstream inFile(inputFilename, ios::binary);
    ofstream outFile(compressedFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    string bitString;
    char ch;

    // Read each character from the input file and replace it with its Huffman code
    while (inFile.get(ch)) {
        string code = codes.find(static_cast<unsigned char>(ch));
        if (code.empty()) {
            cerr << "Error: Huffman code for character '" << ch << "' not found." << endl;
            return;
        }
        bitString += code;
    }

    // Calculate padding required to make the bitstring a multiple of 8
    int paddingBits = 8 - (bitString.size() % 8);
    if (paddingBits != 8) {
        bitString.append(paddingBits, '0');
    }

    // Write the padding bits count to the output file
    outFile.put(static_cast<char>(paddingBits));

    // Write the compressed (binary) data to the output file
    for (size_t i = 0; i < bitString.size(); i += 8) {
        string byteStr = bitString.substr(i, 8);
        bitset<8> byte(byteStr);
        outFile.put(static_cast<char>(byte.to_ulong()));
    }

    inFile.close();
    outFile.close();

    // Encrypt the compressed file after compression
    encryptDecryptFile(compressedFilename);
}

// Function to decompress the compressed file using Huffman coding and store the result in the output file
void FileZipper::decompress(const string& compressedFilename, const string& outputFilename) {
    // Decrypt the compressed file before decompressing
    encryptDecryptFile(compressedFilename);

    ifstream inFile(compressedFilename, ios::binary);
    ofstream outFile(outputFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    // Read padding bits from the compressed file
    char paddingBitsChar;
    inFile.get(paddingBitsChar);

    int paddingBits = paddingBitsChar;

    string bitString;
    char byte;

    // Read the compressed file byte by byte and convert to a bitstring
    while (inFile.get(byte)) {
        bitString += bitset<8>(static_cast<unsigned char>(byte)).to_string();
    }

    // Remove padding bits from the bitstring
    if (paddingBits > 0 && paddingBits <= 8) {
        bitString = bitString.substr(0, bitString.size() - paddingBits);
    }
    else {
        cerr << "Error: Invalid padding bits value." << endl;
        return;
    }

    // Decode the Huffman tree to decode the compressed file
    HuffmanTree huffmanTree;
    huffmanTree.decodeTree(frequencies);

    HuffmanNode* currentNode = huffmanTree.getRoot();

    // Traverse the bitstring and decode it using the Huffman tree
    for (char bit : bitString) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        // If a leaf node is reached, write the decoded character to the output file
        if (!currentNode->left && !currentNode->right) {
            outFile.put(currentNode->data);
            currentNode = huffmanTree.getRoot(); // Reset to root of the tree
        }
    }

    inFile.close();
    outFile.close();
}
