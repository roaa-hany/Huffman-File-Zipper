#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f);
};

struct Compare {
    bool operator()(Node* a, Node* b);
};

unordered_map<char, int> buildFrequencyMap(const string& filename);
Node* buildHuffmanTree(const unordered_map<char, int>& freqMap);
void buildCodeMap(Node* root, const string& code, unordered_map<char, string>& codeMap);
void writeCompressedFile(const string& inputFile, const string& outputFile);
void decompressFile(const string& compressedFile, const string& outputFile);

#endif // HUFFMAN_H
