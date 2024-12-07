//
// Created by hp on 11/23/2024.
//

#include "priority_queue.h"
#include "HuffmanTree.h"
#include "HuffmanNode.h"
using namespace std;

// Constructor: Initializes an empty priority queue (heap)
priority_queue::priority_queue() {}

// Destructor: Cleans up the heap and deletes all nodes
priority_queue::~priority_queue() {
    // Iterate through all nodes in the heap and delete them to free memory
    for (auto node : heap) {
        delete node;
    }
}

// Returns the index of the parent node of a given index i
int priority_queue::parent(int i) {
  return (i - 1) / 2;  // Parent index formula for a binary heap
}

// Returns the index of the left child node of a given index i
int priority_queue::left(int i) {
  return 2 * i + 1;  // Left child index formula for a binary heap
}

// Returns the index of the right child node of a given index i
int priority_queue::right(int i) {
  return 2 * i + 2;  // Right child index formula for a binary heap
}

// Moves the element at index i up the heap to maintain the heap property
void priority_queue::heapifyUp(int i) {
    while (i > 0 && heap[i]->freq < heap[parent(i)]->freq) {
        // Swap with parent if current node frequency is smaller
        swap(heap[i], heap[parent(i)]);
        i = parent(i);  // Move i to parent index
    }
}

// Moves the element at index i down the heap to maintain the heap property
void priority_queue::heapifyDown(int i) {
    int l = left(i), r = right(i);
    int smallest = i;

    // Check if left child exists and has a smaller frequency than current node
    if (l < heap.size() && heap[l]->freq < heap[smallest]->freq) {
        smallest = l;
    }

    // Check if right child exists and has a smaller frequency than the current smallest
    if (r < heap.size() && heap[r]->freq < heap[smallest]->freq) {
        smallest = r;
    }

    // If the smallest element is not the current node, swap and heapify down further
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);  // Recursively heapify down from the new index
    }
}

// Inserts a node into the priority queue (heap) and maintains the heap property
void priority_queue::insert(HuffmanNode* n) {
    heap.push_back(n);  // Add node to the end of the heap
    heapifyUp(heap.size() - 1);  // Heapify up from the newly inserted node
}

// Removes and returns the node with the smallest frequency (root of the heap)
HuffmanNode* priority_queue::removeMin() {
    if (heap.empty()) {
        return nullptr;  // If heap is empty, return null
    }

    HuffmanNode* min = heap[0];  // The root is the smallest element
    heap[0] = heap.back();  // Replace the root with the last element in the heap
    heap.pop_back();  // Remove the last element
    heapifyDown(0);  // Heapify down from the root to maintain heap property
    return min;
}

// Returns the node with the smallest frequency without removing it
HuffmanNode* priority_queue::getMin() {
    if(heap.empty()) {
        return nullptr;  // If heap is empty, return null
    } else {
        return heap[0];  // Return the root node (smallest element)
    }
}

// Returns the number of nodes in the heap
int priority_queue::getSize() {
    return heap.size();  // Return the size of the heap
}

// Returns whether the heap is empty
bool priority_queue::isEmpty() {
    return heap.empty();  // Return true if heap is empty
}

// Builds a heap from an existing vector of nodes
void priority_queue::buildHeap(const vector<HuffmanNode*>& nodes) {
    heap = nodes;  // Initialize heap with the given vector of nodes
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);  // Heapify down from the last non-leaf node
    }
}
