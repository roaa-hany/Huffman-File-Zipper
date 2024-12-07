#include <iostream>
#include "LinkedList.h"
using namespace std;

// Constructor to initialize an empty linked list
LinkedList::LinkedList() {
    head = nullptr;
}

// Destructor to clear the list and free memory
LinkedList::~LinkedList() {
    clear();
}

// Insert a new node with the given key and value at the end of the list
void LinkedList::insert(char key, const string& value) {
    // Create a new node with the given key and value
    Node* newNode = new Node(key, value);

    // If the list is empty, make the new node the head of the list
    if (!head) {
        head = newNode;
        return;
    }

    // Otherwise, traverse to the end of the list and insert the new node
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

// Getter function to return the head node of the list
Node* LinkedList::getHead() const {
    return head;
}

// Find the value associated with the given key in the list
// Returns an empty string if the key is not found
string LinkedList::find(char key) {
    // Traverse the list to find the node with the matching key
    Node* current = head;
    while (current) {
        if (current->key == key) {
            return current->value; // Return the value if the key is found
        }
        current = current->next;
    }
    return ""; // Return empty string if key not found
}

// Clear the list and free all dynamically allocated memory
void LinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp; // Delete each node in the list to free memory
    }
    head = nullptr; // Reset the head pointer to null
}
