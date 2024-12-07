#include "HuffmanTree.h"
#include "LinkedList.h"
#include "priority_queue.h"
#include "HuffmanNode.h"
#include <vector>

using namespace std;

// Constructor initializes the root pointer to null
HuffmanTree::HuffmanTree(){
    root = nullptr;
}

// Function to build the Huffman tree from a priority queue
// The priority queue contains nodes with characters and their frequencies
void HuffmanTree::buildTree(priority_queue& pq) {
    // While there is more than one node in the priority queue, combine the two with the smallest frequencies
    while (pq.getSize() > 1) {
        // Remove the two nodes with the lowest frequencies
        HuffmanNode* left = pq.removeMin();
        HuffmanNode* right = pq.removeMin();

        // Create a new node with the combined frequency of the two nodes
        int combinedFrequency = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFrequency, left, right);

        // Insert the new node back into the priority queue
        pq.insert(newNode);
    }

    // The remaining node in the priority queue is the root of the Huffman tree
    root = pq.removeMin();
}

// Function to generate the Huffman codes from the Huffman tree
// Traverses the tree and builds the code for each character
void HuffmanTree::generateCodes(HuffmanNode* node, string str, vector<pair<char, string>>& codes) {
    if (!node) return; // Base case: return if node is null

    // If it's a leaf node, store the character and its Huffman code
    if (node->data != '\0') {
        codes.push_back({node->data, str});
    }

    // Recursively generate the codes for the left and right child nodes
    generateCodes(node->left, str + "0", codes);
    generateCodes(node->right, str + "1", codes);
}

// Getter function to retrieve the root of the Huffman tree
HuffmanNode* HuffmanTree::getRoot() const {
    return root;
}

// Function to decode the Huffman tree from the given frequency list (LinkedList)
// The frequency list is assumed to contain characters and their frequencies
void HuffmanTree::decodeTree(const LinkedList& frequencies) {
    priority_queue pq;

    // Traverse the linked list and insert nodes into the priority queue
    Node* current = frequencies.getHead(); // Assuming LinkedList has a getHead() method to get the first node
    while (current) {
        // Convert the frequency stored as a string to an integer
        char character = current->key;
        int frequency = stoi(current->value); // Convert stored string value to integer

        // Insert a new Huffman node with the character and frequency into the priority queue
        pq.insert(new HuffmanNode(character, frequency));
        current = current->next; // Move to the next node in the linked list
    }

    // Build the Huffman tree using the priority queue
    while (pq.getSize() > 1) {
        // Remove the two nodes with the lowest frequencies
        HuffmanNode* left = pq.removeMin();
        HuffmanNode* right = pq.removeMin();

        // Create a new internal node with the combined frequency of the two nodes
        int combinedFrequency = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFrequency, left, right);

        // Insert the new internal node back into the priority queue
        pq.insert(newNode);
    }

    // The remaining node in the priority queue is the root of the Huffman tree
    root = pq.removeMin();
}
