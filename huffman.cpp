#include "huffman.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>
#include <stdexcept>

using namespace std;

Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}


bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

//long getfilesize(string& inputfile) {
//  ifstream file(inputfile, ios::binary | ios::ate);
//  if (!file.is_open()) {
//      cerr << "Error calculating the size of the file." << endl;
//      return -1;
//  }
//  long size = file.tellg();
//  file.close();
//  return size;
//}

unordered_map<char, int> buildFrequencyMap(const string& filename) {
    unordered_map<char, int> freqMap;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        throw runtime_error("Cannot open file for reading.");
    }

    char ch;
    while (file.get(ch)) {
        freqMap[ch]++;
    }

    file.close();
    return freqMap;
}

Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.top();
}


void buildCodeMap(Node* root, const string& code, unordered_map<char, string>& codeMap) {
    if (!root) return;

    if (!root->left && !root->right) {
        codeMap[root->ch] = code;
    }

    buildCodeMap(root->left, code + "0", codeMap);
    buildCodeMap(root->right, code + "1", codeMap);
}

void writeCompressedFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    unordered_map<char, int> freqMap = buildFrequencyMap(inputFile);
    Node* huffmanTree = buildHuffmanTree(freqMap);
    unordered_map<char, string> codeMap;
    buildCodeMap(huffmanTree, "", codeMap);

    if (!inFile.is_open() || !outFile.is_open()) {
        throw runtime_error("Cannot open file for reading/writing.");
    }

    string encodedString = "";
    char ch;
    while (inFile.get(ch)) {
        encodedString += codeMap.at(ch);
    }


    int padding = 8 - encodedString.length() % 8;
    for (int i = 0; i < padding; ++i) {
        encodedString += "0";
    }
    outFile.put(padding);
    outFile << codeMap.size() << '\n';
    for (const auto& pair : codeMap) {
        outFile << pair.first << " " << pair.second << '\n';
    }
    for (size_t i = 0; i < encodedString.size(); i += 8) {
        bitset<8> byte(encodedString.substr(i, 8));
        outFile.put(static_cast<char>(byte.to_ulong()));
    }
    inFile.close();
    outFile.close();
}

void decompressFile(const string& compressedFile, const string& outputFile) {
    ifstream inFile(compressedFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        throw runtime_error("Cannot open file");
    }
    int padding = inFile.get();

    unordered_map<string, char> reverseCodeMap;
    size_t mapSize;
    inFile >> mapSize;
    inFile.ignore();

    for (size_t i = 0; i < mapSize; ++i) {
        char ch;
        string code;
        inFile.get(ch);
        inFile.ignore();
        getline(inFile, code);
        reverseCodeMap[code] = ch;
    }

    string encodedString = "";
    char byte;
    while (inFile.get(byte)) {
        encodedString += bitset<8>(byte).to_string();
    }

    encodedString = encodedString.substr(0, encodedString.size() - padding);

    string currentCode = "";
    for (char bit : encodedString) {
        currentCode += bit;
        if (reverseCodeMap.count(currentCode)) {
            outFile.put(reverseCodeMap[currentCode]);
            currentCode = "";
        }
    }

    inFile.close();
    outFile.close();
}

