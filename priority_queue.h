//
// Created by hp on 11/17/2024.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "huffman.h"
#include <climits>
using namespace std;

struct element {
    int freq;
    Node* node;

    // Default Constructor
    element() : freq(0), node(nullptr) {}

    // Parameterized Constructor
    element(int f, Node* n) : freq(f), node(n) {}

    // Overload comparison operators for min-heap based on `value`
    bool operator<(const element& other) const {
        return freq < other.freq; // Min-heap: smallest value at the top
    }

    bool operator>(const element& other) const {
        return freq > other.freq;
    }
};

class priority_queue {
public:
    priority_queue(int maxSize);                  // Constructor
    ~priority_queue();                            // Destructor
    void insert(element item);             // Insert element
    element remove();                             // Remove top element
    int size();                                   //get the queue size

private:
    element* array;                                // Array of nodes and frequencies
    int maxSize;                                   // Max capacity
    int lastIndex;                                 // Last index of the heap
    element maxItem;                               // Top element of max-heap
    void upheap(int index);                        // Maintain heap property upwards
    void downheap(int index);                      // Maintain heap property downwards
};

#endif // PRIORITY_QUEUE_H
