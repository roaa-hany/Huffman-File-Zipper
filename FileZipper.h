#ifndef FILEZIPPER_H
#define FILEZIPPER_H

#include <string>
#include "LinkedList.h"
#include "HuffmanNode.h"

// FileZipper class
class FileZipper {
public:
    FileZipper();

    // Compresses the input file, encrypts it, and writes to the output file
    void compress(const std::string& inputFilename, const std::string& compressedFilename);

    // Decrypts the file, decompresses it, and writes to the output file
    void decompress(const std::string& compressedFilename, const std::string& outputFilename);

private:
    // Encrypts or decrypts data in a file using XOR encryption
    void encryptDecryptFile(const std::string& filename);

    // Builds the frequency table from the input file
    void buildFrequencyTable(const std::string& filename);

    // Builds the Huffman codes from the Huffman tree
    void buildHuffmanCodes(HuffmanNode* root, const std::string& code);

    LinkedList frequencies; // Stores the frequency table as a linked list
    LinkedList codes;       // Stores the Huffman codes as a linked list
};

#endif // FILEZIPPER_H
