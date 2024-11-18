#include "priority_queue.h"
#include <iostream>
using namespace std;

// Constructor for initializing elements
priority_queue::priority_queue(int size) {
    maxSize = size;
    array = new element[maxSize + 1];       // Allocate space for the heap array
    lastIndex = 0;
    maxItem.freq = INT_MAX;                 // Initialize the key with INT_MAX
    maxItem.node = nullptr;                 // Initialize the pointer to nullptr
    array[0] = maxItem;                     // Place maxItem in the first slot of the array
}

// Destructor to release dynamically allocated memory
priority_queue::~priority_queue() {
    delete[] array; // Free the allocated memory for the heap array
    array = nullptr; // Set pointer to nullptr to avoid dangling pointers
}

// Insert a key-value pair
void priority_queue::insert(element item) {

    if (lastIndex == maxSize) { // If the heap is full, readjust its size to have space for a new element
        maxSize += 1;
        array = static_cast<element*>(realloc(array, (maxSize + 1) * sizeof(element)));
    }
    array[++lastIndex] = item; // Increment the last index and insert the element at the end of the heap
    upheap(lastIndex);         // Upheap from the last element to maintain the max-heap property
}

// Remove the top element
element priority_queue::remove() {

    element temp = array[1];            // Store the top (max) element in the heap
    array[1] = array[lastIndex--];      // Replace the top element with the last one and adjust the last index
    downheap(1);                   // Downheap from the top of the heap to maintain its max property
    return temp;                        // Return the top element
}

// Upheap operation for maintaining heap property
void priority_queue::upheap(int index) {

    element temp = array[index];                    // Store the current element

    while (array[index / 2].freq < temp.freq) {     // While the current element is greater than its parent, swap them
        array[index] = array[index / 2];
        index = index / 2;
    }
    array[index] = temp;
}

// Downheap operation for maintaining heap property
void priority_queue::downheap(int index) {

    element temp = array[index];                                // Store the current element

    int i = 2 * index;                                          // Move to the left child of the element
    for (; i <= lastIndex; i *= 2) {
        if (i < lastIndex && array[i].freq < array[i + 1].freq) // If the left child is smaller than the right, move to the max (right)
            i++;
        if (temp.freq >= array[i].freq)                         // If the current element satisfies max-heap property, do nothing
            break;
        array[i / 2] = array[i];                                // If not, swap the current element with its max child
    }
    array[i / 2] = temp;
}

// Return the current size of the heap
int priority_queue::size() {
    return lastIndex;
}