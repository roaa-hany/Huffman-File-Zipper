#include "HuffmanTree.h"
#include "LinkedList.h"
#include "priority_queue.h"
#include "HuffmanNode.h"
#include <vector>

using namespace std;
// HuffmanTree class implementation
HuffmanTree::HuffmanTree() : root(nullptr) {}

void HuffmanTree::buildTree(priority_queue& pq) {
    while (pq.getSize() > 1) {
        HuffmanNode* left = pq.removeMin();
        HuffmanNode* right = pq.removeMin();

        int combinedFrequency = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFrequency, left, right);
        pq.insert(newNode);
    }

    root = pq.removeMin();
}

void HuffmanTree::generateCodes(HuffmanNode* node, string str, vector<pair<char, string>>& codes) {
    if (!node) return;

    if (node->data != '\0') {
        codes.push_back({node->data, str});
    }

    generateCodes(node->left, str + "0", codes);
    generateCodes(node->right, str + "1", codes);
}

HuffmanNode* HuffmanTree::getRoot() const {
    return root;
}

void HuffmanTree::decodeTree(const LinkedList& frequencies) {
    priority_queue pq;

    // Traverse the linked list and add nodes to the priority queue
    Node* current = frequencies.getHead(); // Assume LinkedList has a getHead() method
    while (current) {
        char character = current->key;
        int frequency = stoi(current->value); // Convert stored string value to integer
        pq.insert(new HuffmanNode(character, frequency));
        current = current->next;
    }

    // Build the tree using the priority queue
    while (pq.getSize() > 1) {
        HuffmanNode* left = pq.removeMin();
        HuffmanNode* right = pq.removeMin();

        int combinedFrequency = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFrequency, left, right);
        pq.insert(newNode);
    }

    root = pq.removeMin();
}
